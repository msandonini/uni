---
date:
  - 2026/10/02
---
Posso decidere di [[Cloud Paradigm|replicare]] completamente i server che gestiscono i dati (i DB), o posso replicare solo alcuni dati (in questo caso parliamo di cache server).
Nel caso di un cache server possiamo un meccanismo di replicazione di tipo push, dove vengono caricati sul cache server solo i dati a cui viene eseguito l'accesso più spesso.
L'alternativa è un meccanismo di pull replication, dove vengono caricati i dati quando otteniamo un cache miss (senza dunque controllare che l'accesso in questione sia una tantum).

Quando si pianifica la replicazione dobbiamo fare diverse scelte:
- Tipo di replicazione
	- Full (replico tutte le risorse)
	- Partial (replico solo una parte delle risorse)
- Policy di consistenza
	- Forte
		- Ogni aggiornamento viene propagato istantaneamente su tutti i nodi (il contenuto è sempre aggiornato su ogni server)
		- Non c'è rischio di perdere data
		- Ottimo per la high availability
		- Richiede molte risorse computazionali e di rete per trasmettere gli aggiornamenti
		- Dall'esterno ogni nodo si presenta come se fosse lo stesso
	- Assente
		- Permette inconsistenze nei dati
		- Niente overhead di sincronizzazione
		- Performance migliori
		- Maggiore scalabilità
		- Introduce rischio di perdita dati
	- Debole
		- Compromesso tra consistenza forte e assente
		- Definisce un lasso di tempo per la sincronizzazione, quindi i dati non sono costantemente aggiornati ma vengono aggiornati ogni tot tempo

## Consistenza forte

Nel caso di consistenza forte vado a definire il concetto di copia primaria / autorevole (è garantito che abbia tutti i dati aggiornati), e il sistema presenterà diverse copie primarie.
Tra le copie primarie vado a inserire dei ruoli, ovvero imposto una copia sulla quale effettivamente scrivo le modifiche, mentre sulle altre copie tengo un logging delle modifiche.

Gli esempi più calzanti di questo tipo di consistenza sono i meccanismi di disk mirroring (in particolare RAID-1)

Gestire questo tipo di consistenza a livello geografico è piuttosto complicato, in quanto si tratta di una task piuttosto complessa e con diverse alternative possibili:
- Meccanismo 2-phases commit
	- Si divide in una fase di preparazione (voting) e scrittura (write)
		- Prevede un coordinatore (master) che propaga a tutti i nodi la modifica e attende un ok (fase di voting)
		- Quando il coordinatore riceve l'ok da tutti, invia il comando di scrittura e tutti aggiornano i dati (fase di write)
		- Se in scrittura ci sono errori tutti eseguono il rollback
	- Fornisce consistenza forte
	- È un meccanismo molto costoso
		- Il rischio di rollback cresce con il numero di repliche
		- C'è uno scambio di dati incredibilmente elevato
- Meccanismi P2P (gossip protocol)
	- Si basa sulla comunicazione tra vicini
	- Ci sono almeno $N$ repliche di ogni dato (N si può configurare, se $N<1$  è high availability)
	- Un esempio di funzionamento è Cassandra:
		- Un nodo riceve una query
		- Si identificano i nodi che immagazzinano quelle repliche tramite delle DHT (Distributed Hash Table)
		- Si invia l'update ai nodi replica
		- Almeno $W$ nodi devono ritornare un `ACK` ($W$ configurabile)

Nel caso in cui i server primari falliscano, introduciamo dei server secondari per garantire availability.
I server secondari rispondono in caso di fallimento dei primari, ma possono essere anche usati per migliorare le performance di lettura, in quanto possono essere più vicini rispetto ai primari; in caso di scrittura l'operazione deve comunque essere mandata ad un primario, e verrà solo dopo sincronizzata con il secondario.
I secondari sono di base delle semplici copie di backup, e sottostanno a diverse leggi sulla permanenza dei dati (ad esempio, in Italia devono essere lontani almeno 30 km dai primari, e devono essere montati su un'infrastruttura elettrica e di rete separata per garantire l'availability).
In quanto backup, i secondari solitamente sono caratterizzati da una sincronizzazione debole

## Scalabilità dello storage

La scalabilità di un DBMS relazionale è molto limitata (massimo 10 nodi), di conseguenza in ambito cloud vengono utilizzati DBMS non relazionali (es. MongoDB, CouchDB, ElasticSearch, Neo4j, OrientDB, BigTable, Velocity, Redis, Cassandra, ...), in quanto pensati per essere scalabili e distribuiti su larga scala.
In cambio di questa semplificazione della scalabilità paghiamo un prezzo in consistenza transazionale.
In questo caso esistono 2 principali famiglie di database:
- ACID: Atomicity, Consistency, Isolation, Durability
	- Usato nei sistemi RDBMS
- BASE: Basic Availability, Soft-state, Eventual consistency
	- Usato nei sistemi NoSQL
	- Basic Availability significa che utilizza replicazione per ridurre il rischio di data unavailability e la partizione dei server, così da rendere il sistema sempre raggiungibile
	- Soft-state significa che i dati possono essere inconsistenti, ed i servizi si devono adattare
	- Eventual consistency significa che ad un certo punto nel tempo i dati verranno sincronizzati e saranno dunque consistenti (ma non c'è garanzia di quando questo succederà)

In ambito cloud solitamente si sceglie di usare sistemi NoSQL, in quanto possono operare con molti di operazioni e di dati immensi.
Questi sistemi necessitano di strategie di sincronizzazione e di strutture dati distribuite.

Di base quando dobbiamo realizzare un sistema distribuito ci basiamo sulle proprietà CAP (Consistency / Availability / Partition-tolerance):
- Consistency: ogni lettura ritorna i dati dall'ultima scrittura
- Availability: ogni richiesta ritorna una risposta di mancanza di errore
- Partition-tolerance: il sistema lavora anche in caso di partizioni di rete (messaggi persi o in ritardo)
Il CAP theorem ci dice che possiamo scegliere solo 2 delle 3 proprietà

## Replicazione geografica

La continua crescita dell'utilizzo di sistemi autonomi implica che è impossibile aumentare il numero di server primari a causa dei problemi di gestione, di conseguenza dobbiamo accrescere il numero di server secondari (così da migliorare le performance).
Un altro modo che abbiamo per incrementare le performance è implementare meccanismi di caching, che possono operare a diversi livelli:
- Hardware (memoria o disco)
- OS (OS buffer cache del file system)
- Software (es. data pools nei DBMS)

Su scala globale, l'ottimizzazione della replicazione rende necessari dei principi di caching:
- Località spaziale
	- Se un utente accede a dei dati, è più probabile che acceda a dati vicini rispetto che a dati geograficamente più lontani
- Località temporale
	- Se un utente / applicazione accede a dei dati, è più probabile che vi acceda di nuovo in un intervallo di tempo breve rispetto che ad uno più lungo
- Effettività
	- Cache hit
		- Il client trova le risorse richieste nel server cache
	- Cache miss
		- Il client non trova le risorse richieste nel server cache
	- Cache hit rate
		- $\frac{N_{\text{hit}}(t)}{N_{\text{miss}}(t)}$

Ci sono 2 meccanismi principali di caching
- Pull
	- Contenuti caricati dal server primario quando un consumer lo richiede, e non c'è una copia valida nel secondario
	- Utilizzato da proxy servers e sistemi di proxy servers cooperativi (ISP)
- Push
	- Contenuti che vengono richiesti con maggiore probabilità e vengono pre-caricati sui server secondari
	- Utilizzato da reverse proxies e CDN

<!-- Slides from 48 to 82 -->

Recentemente l'implementazione delle CDN è piuttosto opaca (è difficile capire come operino), ma comunque alcuni principi di funzionamento sono comuni e riconoscibili:
- URL-rewriting
	- Determinati URL sono sostituiti e fanno riferimento direttamente alla CDN (questa gestione degli URL non avviene tramite un DNS primario ma da dei server della CDN)
	- Gli embedded objects della pagina vengono recuperati dalla CDN
- DNS outsourcing
	- Il DNS originale ritorna un canonical name di un DNS della CDN che ha la risoluzione giusta
Ad oggi il leader nel settore delle CDN è Akamai


