##

### Attività

Un'attività è un lavoro che viene svolto all'interno del processo.
Le attività possono essere:
- Semplici, anche chiamate *Task*s
- Composte, anche chiamate *Sub-process*.
Ogni attività può essere svolta una volta o avere dei loop definiti.

Le attività vengono rappresentate tramite rettangoli con angoli arrotondati.

#### Tasks

Un Task è un'attività semplice, non scomponibile ulteriormente

#### Sub-process

Un Sub-Process è un'attivita complessa, rappresentata mediante ulteriori sub-processes e task.

Un Sub-Process può essere di 2 tipi:
- Embedded
- Independent (riutilizzabili)
	- Lo stesso processo diventa un sotto-processo di diverse attività differenti

### Eventi

Un evento rappresenta qualcosa che accade all'interno del processo, e che influenza il normale flusso dello stesso.
Ogni evento è rappresentato con un cerchio.
Ogni processo inizia con un evento "Start" ed un evento "End".

#### Start events

Per ogni evento possono essere rappresentate delle circostanze che indicano le condizioni che fanno iniziare il processo. È possibile che, per uno stesso processo, ci siano più eventi di "Start".

Diversi tipi di start events:
- None
- Message
- Timer
- Rule
- Link
- Multiple

#### Intermediate events

Gli eventi intermedi sono eventi che avvengono dopo la partenza di un processo e prima del suo termine.
Sono inseriti all'interno del flusso del processo, o attaccati al bordo di un'attività.

Diversi tipi di eventi intermedi:
- None
- Message
- Timer
- Error
- Compensation
- Rule
- Link
- Multiple

#### End events

Gli eventi di fine sono eventi che avvengono alla fine di un processo

Diversi tipi di eventi intermedi:
- None
- Message
- Error
- Compensation
- Link
- Terminate
- Multiple

### Gateways

I Gateways sono elementi che controllano il flusso delle attività.
Sono rappresentati tramite rombi.

Ci sono diversi tipi di Gateway:
- Exclusive (Data-Based)
- Inclusive
- Complex
- Parallel

#### Exclusive Gateways

Gli Exclusive Gateways sono dei punti all'interno del processo dove la sequenza delle attività può prendere 2 o più percorsi alternativi.
La scelta del percorso da seguire è basata su una decisione in funzione di eventi o dati.
Nell'esecuzione del processo deve essere sempre possibile scegliere un percorso tra tutti (niente ambiguità).

#### Inclusive Gateways

Gli Inclusive Gateways sono dei punti dove è possibile scegliere più percorsi (almeno 1, ma senza un limite massimo).
La presenza di un Inclusive Gateway indica che in corrispondenza di ciò il flusso diventa parallelo fino ad un certo punto.

#### Complex Gateways

I Complex Gateways sono punti in cui vanno prese decisioni complesse.

#### Parallel Gateways

I Parallel Gateways sono punti del processo dove si caratterizzati da percorsi multipli paralleli. A differenza degli Inclusive Gateways non avvengono in corrispondenza di determinate condizioni.
Non sono normalmente richiesti, a meno che non serva sincronizzare i flussi paralleli.

### Connettori

Ci sono diversi tipi di connettore:
- Sequence flow, utilizzato per mostrare l'ordine in cui si svolgono le attività in un processo
- Message flow, utilizzato per mostrare il flusso di messaggi tra diversi partecipanti al processo
- Association, utilizzati per associare dati, informazioni, e Artifacts

#### Sequence flow

Un Sequence Flow **non** può attraversare il bordo di un sub-process o di un pool.
Aggiungendo un rombo all'inizio di un sequence flow è possibile aggiungere determinate condizioni. In questo caso serve avere almeno un altro connettore parallelo.

Si può indicare un connettore come default disegnando una piccola barretta all'inizio della freccia

#### Message flow

Un Message Flow viene usato per mostrare un flusso di messaggi tra i partecipanti di un processo.
Questo connettore può essere connesso con il bordo del pool o con un oggetto interno al pool stesso.
Non è possibile connettere tramite message flow oggetti interni allo stesso pool.

#### Associations

Vanno spesso a collegare attività ed artefatti.
Serve a mostrare un flusso di dati in ingresso ed uscita delle Activity.

### Data Objects

I Data Objects sono utilizzati per mostrare come dati e documenti sono usati all'interno del processo, e per definire input ed output delle attività.

### Groups

I gruppi sono usati per raggruppare un insieme di attività. Un gruppo, essendo semplicemente un raggruppamento logico, può comprendere attività da diversi pool

## Esempi

### Processo rimborso spese

![[BPMN_esempio_rimborso_spese.png]]

## Esercizi

![[Banca.drawio]]
![[Progettazione del Software/13 BPMN/Untitled Diagram.svg]]