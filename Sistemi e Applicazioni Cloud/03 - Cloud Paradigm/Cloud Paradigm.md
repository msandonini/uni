---
date: 2026/09/25
---
Lo scaling (passare da una VM a molte o viceversa) può avvenire in brevissimi lassi di tempo.
Per permettere questo scaling, e per ridurre i possibili problemi, facciamo uso di 2 tecniche:
- Replicazione
- Orchestrazione (autonoma)

Determinati paradigmi di programmazione non possono essere applicati al cloud a causa dei vari point of failures di quest'ultimo:
- Processi
	- Sincronizzazione su larga scala
- Dati
	- Consistenza
	- Immagazzinamento e processing
		- Immagazzinamento difficile da parallelizzare
- Comunicazione
	- Sincronia
	- All-to-all

Le applicazioni cloud hanno diversi punti qualificanti:
- Scalabilità + elasticità
- Disponibilità
In questa maniera le applicazioni si possono adattare a dei carichi di lavoro fluttuanti, e permettere un failure handling decente.
Per implementare ciò, quello che solitamente si fa è astrarre il software dall'hardware e astrarre i business services dal software.
Per quest'ultimo punto dobbiamo comportarci in maniera agnostica rispetto ad hardware, piattaforma, e software, ma non possiamo essere agnostici per quanto riguarda i business processes (l'utente non si preoccupa di librerie e framework, ma si preoccupa di costi e usabilità)

Quando si va a realizzare un servizio e a metterlo in produzione dobbiamo scegliere quale approccio utilizzare per implementarlo:
- Servizio monolitico
	- Singolo software
	- Difficile e costoso da replicare
	- Approccio old school
- SOA (Service Oriented Architecture)
	- Funziona tramite protocolli SOA
	- XML-based
	- Tipicamente scritto in Java
	- Potrebbe essere non efficiente
- Micro-servizi
	- Servizi molto piccoli
	- Facili da comporre
	- Facili da replicare
	- Approccio molto comune
- Architettura serverless
	- Evoluzione dei micro-servizi
	- Si isola ancora di più dall'hardware
	- Tenta di raggiungere un approccio stateless (per mantenere memoria ha bisogno di servizi di persistenza dedicati)
	- Trend emergente
![[Pasted image 20260925103306.png]]

Anche per quanto riguarda il processing dei dati bisogna scegliere l'approccio corretto per la task:
- Batch processing
	- Task pesanti delay-tolerant
	- Vengono eseguite off-line
- Real-time processing
	- Può processare i flussi di dati nel mentre che arrivano

Nella maggior parte dei casi a prevalere sono architetture ibride, in cui le nuove tecnologie non sostituiscono le precedenti ma vi si aggiungono, in quanto se qualcosa già funziona non ha senso sostituirla solo perché è uscita una nuova architettura.

## Modelli pre-SOA

Prima dei sistemi SOA veniva scritto codice che funzionasse come wrapper delle invocazioni. Per fare ciò venivano scritti degli stub in linguaggio IDL (Interface Definition Language) usati per per fare marshaling/unmarshaling dei parametri e nascondere determinati aspetti dell'interazione.
![[Pasted image 20260925104531.png]]
Questo processo si chiama Remote Procedure Call (RPC).

Le RPC hanno alcune limitazioni date dal loro approccio:
- Client-Server
- Messaggi sincroni
- Coupling delle componenti molto stretto
Approcci diversi si concentrano su interazioni asincrone, ideali per un coupling molto meno stretto tra le componenti, ed utilizzando code di messaggi

## Modelli SOA

I modelli SOA si applicano in 3 possibili scenari:
- SOA for intra-company apps
- SOA for inter-company apps, Business-to-business (B2B)
- SOA for inter-company apps, Openly usable

Una SOA è composta da diversi ingredienti:
- Servizi
- Tecnologie abilitanti
- Policies e governance SOA
- Metriche SOA
- Modelli organizzativi e comportamentali
Per poter funzionare, le SOA necessitano del supporto per:
- Service discovery
- Service negotiation
- Service composition
- Service adaptation
- Service invocation
- Service monitoring
- Data and process mediation
In sostanza, le SOA hanno un bias vers service provider più che sul cliente

Per favorire lo sviluppo di web services tramite modelli SOA, SOAP (Service Oriented Architecture Protocol) è stato creato, come core messaging technology basata su HTTP o HTTPS e scambiando dati in XML.
I servizi vengono dfiniti in WSDL (Web Service Definition Language), uno standard descrittivo basato su XML, e la registrazione dei servizi avviene tramite UDDI (Universal Description, Discovery and Integration)

SOAP ha diverse limitazioni:
- XML è lento (i parser SAX non sono abbastanza per risolvere)
- HTTP è usato come se fosse TCP (senza il codice di risposta)
A causa di queste limitazioni si è passati ad un approccio RESTful, utilizzando JSON al posto di XML

## Microservizi

Lo stile architetturale a microservizi consiste nello sviluppo di una singola applicazione come suite di task di business molto piccole implementate come servizi.
Ogni microservizio viene eseguito tramite il suo processo dedicato, comunicando tramite meccanismi leggeri (API HTTP), e possono essere scritti in linguaggi di programmazione diversi.
Questo stile architetturale ha bisogno di orchestrazione.

Questa architettura permette continuous delivery e deployment di applicazioni molto larghe e complesse, in quanto hanno migliore testabilità, miglior deployability, e se ne può organizzare il ciclo di sviluppo attorno a team diversi ed indipendenti

## Architettura REST

REST è un approccio leggero sia lato client che lato server, dove le risorse incapsulano le entità.
Le risorse sono identificate tramite URI, e sono fornite come rappresentazioni, mentre ogni azione è mappata su degli specifici messaggi.
Le principali caratteristiche sono le seguenti:
- modello client-server
- operazioni stateless
- risultati con possibilità di caching
- sistema stratificato
- interfaccia unificata
- nessun limite esplicito sui messaggi
- diverse azioni possibili su paradigma CRUD (Create, retrieve, update, delete):
	- GET: Retrieve/Read
	- POST: Create
	- PUT: Update
	- DELETE: Delete
	- HEAD: Check (controlla se una risorsa esiste)
	- OPTIONS: Describe (descrive i possibili verbi HTTP utilizzabili)
- le risorse possono essere restituite in diverse rappresentazioni, ma JSON è la preferita.

## Event Driven Architectures

Una EDA supporta la generazione e la gestione di notifiche di eventi, e rappresenta un'architettura real-time molto flessibile, in quanto gli elementi che generano eventi non hanno bisogno di sapere le componenti del ricevitore, funziona tramite tempi di risposta non deterministici, ed è veloce ad adattarsi ai cambiamenti

Un evento può essere sostanzialmente qualsiasi cosa, e ogni nuovo evento causa la creazione di un messaggio con un determinato topic, al che ogni altro sistema interessato al topic viene notificato.

Esempi di EDA sono i protocolli pub/sub:
- AMQP
- MQTT
- Kafka

### Kafka

Kafka in realtà è sostanzialmente un database reso protocollo, pensato per la scalabilità e la fault tolerance, difatto di base è pensato per essere un'architettura distribuita geograficamente
