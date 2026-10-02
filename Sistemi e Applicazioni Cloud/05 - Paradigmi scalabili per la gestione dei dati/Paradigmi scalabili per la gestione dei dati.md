---
date:
  - 2026/10/02
---
Uno dei meccanismi chiave della gestione e replicazione dei dati consiste nel caching.

Posso decidere di replicare completamente i server che gestiscono i dati (i DB), o posso replicare solo alcuni dati (in questo caso parliamo di cache server).
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