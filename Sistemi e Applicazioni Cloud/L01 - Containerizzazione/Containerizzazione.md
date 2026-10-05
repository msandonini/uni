---
date:
  - 2026/10/05
---
# Containerizzazione

Container: unità auto-contenuta di dimensioni standard, modulare, facile da trasportare.

Un processo contiene una parte statica ed una parte dinamica:
- Statica:
	- Lista di istruzioni (il programma)
	- Dati statici (file, configurazioni, ...)
- Dinamica:
	- Registri
	- Memoria
	- Risorse allocate

Ciò che permette ai processi di funzionare sono le librerie, che a loro volta possono essere linkate staticamente o dinamicamente:
- Linking statico
	- Librerie linkate a compile time
	- I simboli sono risolti dal linker
		- File `.o`: oggetti creati dal compilatore
		- File `.a`: librerie
	- Più safe in quanto le librerie sono incluse nell'eseguibile, ma l'eseguibile pesa di più in quanto la stessa libreria non può essere condivisa tra più programmi, e in caso di scoperta di falle di sicurezza devo aggiornare manualmente (io sviluppatore) la dipendenza
- Linking dinamico
	- Librerie linkate a compile time e bindate al runtime
	- I simboli sono risolti dal linker
		- File `.a`: stubs di librerie
		- File `.so`: shared objects
	- Il codice delle librerie viene caricato e boundato dinamicamente agli stubs:
		- `ld.so`: linker dinamico
	- I file `.so` possono essere condivisi da diversi eseguibili

Quando pacchettizzo un eseguibile solitamente il pacchetto finale contiene dei metadati contenente informazioni sulle dipendenze.
Da ciò derivano problemi di complessità nel dependency graph e di conflitti di dipendenze.

Per ridurre problemi di conflitti delle dipendenze senza gli svantaggi dello static linking, quello che posso fare è pacchettizzare le applicazioni in un container.

Un container può essere paragonato ad una VM, ma con alcune differenze

| Container                 | VM                       |
| ------------------------- | ------------------------ |
| Astrazione dell'OS        | Astrazione dell'HW       |
| Eseguito sullo stesso OS  | Eseguito su OS diversi   |
| Basso utilizzo di risorse | Alto utilizzo di risorse |
| Basso overhead            | Alto overhead            |

## Principi di containerizzazione

Il concetto di container è nato alla fine degli anni 70, e si basa su conocetti introdotti da diverse tecnologie e loro evoluzioni negli anni:
- [[#`chroot`]] (1979): system call che permette ad un processo e ai suoi figli di posizionarsi in un file system di root diverso.
	- Permette una sorta di segregazione dell'accesso dei file ad una base per processo
	- Primo esempio di **process isolation**
		- Sistema usato da BSD che permette di creare environment (jail nel caso di BSD) diversi ognuno isolato dagli altri e con configurazioni diverse tra l'uno e l'altro
- VServer (2001)
	- Introduzione su Linux delle Jail come contesto di sicurezza
- OpenVZ (2005)
- LXC (2008)
	- Uso di `cgroups` (control groups)
		- Permette la limitazione delle risorse
	- Uso di [[#namespaces]] Linux (prima soluzione di containerizzazione completa su Linux)
		- Permette la creazione di nuovi spazi di redirezionamento IP
- Warden (2011)
	- Introduce il concetto di container runtime
- Docker (2013)
	- Inizialmente basato su LXC
	- Rilascia `containerd` come standard open
	- Inserisce il concetto di immagine e orchestrazione
- Podman
	- Drop in replacement per Docker
	- Attualmente il più utilizzato
	- Differisce da Docker solo per l'unpriviledge container (i container podman sono unpriviledged e non hanno dietro un daemon che ne ascolta le chiamate)

Grazie ai container, nel 2010, sono nati diversi movimenti e sistemi:
- DevOps come evoluzione del movimento Agile
- Sistemi di orchestrazione
	- Docker-swarm
	- Kubernetes

### `chroot`

Chiamata di sistema che permette di spostarsi in un container.
Non è nato per questioni di sicurezza ma ai fini dell'installazione di sistemi operativi, di fatto si può tranquillamente uscire dal chroot in maniera semplicissima.

### namespaces

Sistema che permette la creazione di layer di astrazione.
Un processo in un namespace si comporta come se avesse un'istanza isolata della risorsa.
Diversi gruppi di processi hanno diverse visioni del sistema.
System calls come `setns()` permettono ad un processo di unirsi ad un sistema.

- Mount namespace (`mnt`)
	- Usato per creare file system separati
	- Come `chroot` ma più flessibile e sicuro
- Network (`net`)
	- Usato per virtualizzare lo stack di rete
- User ID (`user`)
- Control group (`cgroup`)
	- Può separare l'accesso alle risorse
	- Critico per performance isolation (es. per limitare l'efficacia dei DoS)

### DevOps

Deriva da 2 parole (development ed operation), in quanto tenta di unire 2 mondi dell'informatica diverso e spesso in conflitto tra loro.

L'idea principale del DevOps è di coordinare un po' di più il team di development e quello di operation per tentare di accorciare un ciclo di sviluppo lungo e semplificare il tutto.
Per fare ciò la metodologia di sviluppo consiste in "sprint" di 2/4 settimane con liste di features più piccole e test automatizzati, e per fare ciò introduce alcune task di operation nel development e alcune task di development nell'operation.
L'obiettivo finale della metodologia DevOps è quello di introdurre migliorare la proprietà di velocity (velocità di deployment e scalabilità) migliorando sicurezza e collaborazione tra i team.
Uno dei concetti che salta fuori dal DevOps è quello di CI/CD (Continuous Integration / Continuous Deoployment), che porta ad un aumento della velocità di deployment, e di conseguenza porta ad un'architettura a microservizi.

Le best practices del DevOps sono:
- IaC (Infrastructure as a code)
	- Tecnologia basata sulla definizione dell'infrastruttura usando file di configurazione che definiscono ogni parte dell'infrastruttura
		- Numero di repliche di cui fare il deployment
		- Numero di connessioni di rete
		- Routing e NAT
		- Policies e ACLs
	- Es. Terraform
- Monitoring e logging
	- Insieme di tecniche che permettono l'observability (analisi dei log così da poter fare post-mortem analysis)
- Communication e collaboration

Il discorso tecnico dietro il DevOps è quello di utilizzare testing automatici per valutare il comportamento delle nuove features (critico nel regression testing), in sostanza il concetto è quello di fallire spesso e presto, così da avere più tempo per fixare il problemi (come nei razzi).

Gli elementi tecnici che permettono di arrivare al DevOps consistono nell'automatizzazione di build, test, integration, delivery e deployment.
Questa automatizzazione prevede che la Continuous Integration gestisce la codebase testando il codice e passando i risultati alla Continuous Delivery, che dopo il testing genera un report che viene inviato al product owner così che la build venga approvata, e poi in seguito il Deployment automatizzato.
Tutto ciò porta ad un sistema nel quale non c'è necessita di approvazione della build.

## Benefici della containerizzazione

I container offrono diversi benefici:
- portability
- supporto all'approccio DevOps
- velocità di startup
	- utilizza come host il sistema operativo (a basso livello la chiamata usata è una `clone()`)
- alta efficienza
	- overhead e footprint ridotti
- isolamento
	- isolati sia dal punto di vista di failure che di troubleshooting e performance (quest'ultimo a seconda di come sono configurati i cgroups)
	- utilizza sia i cgroups che SELinux 
- gestione automatica tramite orchestratori
- sicurezza
	- grazie all'isolamento riusciamo a fare fault isolation ma riusciamo anche ad evitare che determinati attacchi si possano propagare al sistema



