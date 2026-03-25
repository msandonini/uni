---
course: Graph Analytics
---
L'obiettivo del personalized page rank è di creare un ranking specifico inerente un topic di interesse dell'utente.

L'utente può saltare da un nodo ad un altro di un insieme fino a raggiungere qualsiasi nodo della rete, con la meccanica di teleport che permette di saltare in una pagina casuale dell'insieme iniziale di nodi così da evitare dead-ends e spider-traps.
Di conseguenza il random walk non è più il solito ma viene modificato, così da implementare la teleport con la probabilità aumentata di ritorno al set di topic di interesse.

Anche con questa modifica, rimane comunque (come con il page rank normale) un modello della navigazione di un utente nel web.
