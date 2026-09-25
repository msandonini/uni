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
	- Trend emergente

