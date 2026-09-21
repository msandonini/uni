Tutti i sistemi "intelligenti" presentano diverse caratteristiche simili:
- Connettività
- Raccolta dati
- Processing dei dati
- Esecuzione di anomaly detection o algoritmi di AI

Ciò che differenzia l'una dall'altra sono i requisiti diversi di queste caratteristiche in base all'applicazione specifica:
- CPU-bound
	- Applicazioni computazionalmente onerose dove la potenza del processore può risultare un bottleneck
- Latency-bound
	- Applicazioni con forti necessità di bassa latenza (es. applicazioni real time)
- Larghezza di banda
	- Applicazioni con scambio di grandi quantità di dati
- Affidabilità
	- Applicazioni con determinate necessità di sicurezza, integrità, ...

In tante applicazioni le sfide principali sono 2:
- Scalabilità
	- Grandi quantità di dati da trasferire e processare
	- Sistemi distribuiti geograficamente
- Bassa latenza
	- Supporto per applicazioni real-time
Quello che mette in crisi le applicazioni cloud è il jitter, in quanto non si sa a quali datacenter si viene assegnati

Il 5G non è la soluzione per le applicazioni latency-bound, in quanto riguarda solo l'ultimo miglio, e non l'interezza dell'infrastruttura di rete da cui dobbiamo passare.
Inoltre, un grande problema è quello della sicurezza dei dati, specialmente considerando le normative sulla privacy e sulla sensibilità dei dati.
Queste problematiche ci fanno capire che il cloud non è abbastanza per molti di questi contesti intelligenti, specialmente per quanto riguarda:
- Dipendenza dalla rete (non solo dalla latenza ma anche dalla disponibilità di connessione continua)
- Mancanza di sovranità dei dati
- Problema del vendor lock-in
Per questi motivi può essere necessario portare una parte del processing dei dati più vicino ai sensori.
Questo livello a metà tra il cloud e i device è chiamato edge layer, e si occupa solitamente di:
- Data processing e riduzione dei dati
- Data caching e buffering
- Controllo della risposta
- Virtualizzazione

| Punto di ottimizzazione | Edge computing           | Cloud computing            |
| ----------------------- | ------------------------ | -------------------------- |
| Rete                    | Aggregazione dati        | Analisi dati               |
| Servizi                 | Agenti                   | Orchestrazione dei servizi |
| Applicazioni            | Micro-applicazioni       | Gestione del ciclo di vita |
| Intelligenza            | Ragionamento distribuito | Training centralizzato     |

>[!Info] Fog Computing
>Con fog layer si intende uno strato intermedio tra il cloud layer e l'edge, formato da dei piccoli datacenter, utilizzato per spostare i calcoli dal cloud più vicino all'edge


