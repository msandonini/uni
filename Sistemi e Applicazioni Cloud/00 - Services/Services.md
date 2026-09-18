<!-- Esame pratico come le esercitazioni -->

A common characteristic of robust and scalable services is that they work always, even in front of hug DDoS attacks. Some examples from 2022 are the following:
- MS Azure deflected 3.47 TB of UDP traffic
- Google absorbed 46 M requests/second
Another common trait is that they work based on many big data centers

The cloud is focused on a services ecosystem, each composed and orchestrated, and often presenting a MVC structure.
A MVC structure means that based on a request we can have different outputs in the same view, so it can be viewed as a multichannel service.

Since internet is a global network, the main issue is maintaining its scalability, which then reflects on how we need the cloud to be as much scalable as possible.

Un servizio è un sistema che fornisce continuamente le risposte alle richieste specifiche di un utente
La continuità di un servizio può essere definita in diversi modi:
- Contratto
	- Service Level Agreement (SLA)
	- Pagamenti e penalità
- Reputazione
	- La penalità è la perdita di clienti e la perdita di fiducia

In caso di servizi cloud, ci sono 2 errori critici da evitare e, quando scoperti, risolvere quanto prima:
- Bottlenecks
- Single point of failure
Questi problemi sono tutt'ora difficili da identificare e correggere

Se viene trovato un single point of failure la soluzione tipica è replicare

Quello che vogliamo ottenere dopo aver risolto questi problemi sono:
- Throughput (rateo di risposta)
- Tempo di risposta
Questi obiettivi traggono vantaggio dalla replicazione: se ho una quantità di dati molto alta processata sequenzialmente, pur aumentando il numero di core che lavorano a questo job, non riuscirò a velocizzare significativamente il rateo e il tempo di risposta, e quindi è necessario replicare, così da aumentare le capacità di calcolo e scalabilità.
Se mi trovo davanti codice che non può essere replicato o parallelizzato, in quel caso mi trovo probabilmente davanti ad un single point of failure o ad un bottleneck


