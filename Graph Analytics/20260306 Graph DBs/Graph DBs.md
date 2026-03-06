Nei graph db, entities e relationships hanno la stessa importanza.

- Sicurezza e privacy:
	- I graph DBs necessitano di implementazioni di accesso più strette .
- Integrità dei dati
	- I graph DBs semplificano le modalità in cui le informazioni si relazionano tra loro, andando però a creare delle problematiche relative possibili duplicazioni dei dati.

Esistono diverse tipologie di Graph DBs:
- Property Graph Database
	- Il più comune
	- Le proprietà sono assegnate sia ai nodi che ai rami
- Resource Description Framework (RDF) Graph Database:
	- Usa il modello RDF per rappresentare i dati come triple consistenti di soggetto, predicato, e oggetto
- Ibridi Property-Graph/Triplestore:
	- Un ibrido tra Property Graph e RDF Graph

Ci sono diversi metodi per interagire con un Graph DB:
- Neo4j
	- Graph DBMS
- Apache TinkerPop
	- Framework che fornisce API per interfacciarsi con DBMS esterni
- NetworkX
	- Libreria Python che permette di manipolare reti tramite i dati in memoria

Come per interagirci, anche per interrogare un Graph DB ci sono diversi metodi:
- GraphQL
	- Linguaggio dichiarativo per APIs che può essere applicato a diversi sistemi (non solo database a grafo ma anche relazionali e a documenti)
	- Linguaggio molto flessibile ed adattabile a tipi differenti di applicazioni e che presenta molte features avanzate
- Cypher
	- Linguaggio dichiarativo pensato specificamente per Neo4j
	- Sintassi semplice ed espressiva ottimizzata per lo storage di Neo4j
- Gremlin
	- Linguaggio dichiarativo funzionale per eseguire graph traversal
	- Parte del framework TinkerPop

Nonostante i Graph DBs non siano nati con uno standard, viene solitamente utilizzato GraphQL come tale.

>[!NOTE] Standard lezioni
> A lezione useremo Neo4j -(con Cypher) e NetworkX

