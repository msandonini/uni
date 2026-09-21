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

Il 5G non è la soluzione per le applicazioni latency-bound, in quanto riguarda solo l'ultimo miglio, e non l'interezza dell'infrastruttura di rete da cui dobbiamo passare