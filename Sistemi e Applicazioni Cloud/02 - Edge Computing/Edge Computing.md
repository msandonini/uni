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

>[!Info] MCC & MEC
>MCC (Mobile Cloud Computing) e MEC (Mobile Edge Computing) sono dei paradigmi utilizzati per ridurre la latenza e migliorare la capacità delle applicazioni mobili

Nel 2009/10 è emerso il paradigma MCC che integra il cloud computing con i dispositivi mobili, così da migliorare le loro prestazioni e capacità. Per fare ciò viene eseguito l'offloading verso il cloud delle parti più pesanti delle applicazioni. Un grosso problema del MCC è la latenza.
Per ridurre questo problema è stato introdotto il Cloudlet Computing.

>[!Info] Cloudlet
>Una cloudlet è un piccolo datacenter di scala ridotta allocata all'edge delle reti, così da offrire risorse computazionali per applicazioni mobili che richiedono bassa latenza ed elevata potenza computazionale

Un'altra alternativa per migliorare il contesto delle cloud applications su dispositivi mobili è il MEC (Mobile Edge Computing, nel tempo si è evoluto per avere come target dispositivi di ogni tipo, quindi ad oggi ha preso l'acronimo di Multi-access Edge Computing).
Questa alternativa alle cloudlets è stata creata dagli operatori RAN (Radio Access Network, sono gli operatori mobili) come standard per introdurre delle base stations ad alte performance considerate come base stations per l'edge computing.
Nel 2018 il sistema MEC è diventato la tecnologia abilitante per il 5G.

Ogni server MEC è composto da una MEC hosting infrastructure e da una MEC application platform, la quale permette l'hosting di diverse applicazioni ed è composta da:
- application virtualization manager
- application platform services
