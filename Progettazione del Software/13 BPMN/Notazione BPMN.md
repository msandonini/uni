## Attività

Un'attività è un lavoro che viene svolto all'interno del processo.
Le attività possono essere:
- Semplici, anche chiamate *Task*s
- Composte, anche chiamate *Sub-process*.
Ogni attività può essere svolta una volta o avere dei loop definiti.

Le attività vengono rappresentate tramite rettangoli con angoli arrotondati.

### Tasks

Un Task è un'attività semplice, non scomponibile ulteriormente

### Sub-process

Un Sub-Process è un'attivita complessa, rappresentata mediante ulteriori sub-processes e task.

Un Sub-Process può essere di 2 tipi:
- Embedded
- Independent (riutilizzabili)
	- Lo stesso processo diventa un sotto-processo di diverse attività differenti

## Eventi

Un evento rappresenta qualcosa che accade all'interno del processo, e che influenza il normale flusso dello stesso.
Ogni evento è rappresentato con un cerchio.
Ogni processo inizia con un evento "Start" ed un evento "End".

### Start events

Per ogni evento possono essere rappresentate delle circostanze che indicano le condizioni che fanno iniziare il processo. È possibile che, per uno stesso processo, ci siano più eventi di "Start".

Diversi tipi di start events:
- None
- Message
- Timer
- Rule
- Link
- Multiple

### Intermediate events

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

### End events

Gli eventi di fine sono eventi che avvengono alla fine di un processo

Diversi tipi di eventi intermedi:
- None
- Message
- Error
- Compensation
- Link
- Terminate
- Multiple

## Gateways

I Gateways sono elementi che controllano il flusso delle attività.
Sono rappresentati tramite rombi.

Ci sono diversi tipi di Gateway:
- Exclusive (Data-Based)
- Inclusive
- Complex
- Parallel

### Exclusive Gateways

Gli Exclusive Gateways sono dei punti all'interno del processo dove la sequenza delle attività può prendere 2 o più percorsi alternativi.
La scelta del percorso da seguire è basata su una decisione in funzione di eventi o dati.
Nell'esecuzione del processo deve essere sempre possibile scegliere un percorso tra tutti (niente ambiguità).

### Inclusive Gateways

Gli Inclusive Gateways sono dei punti dove è possibile scegliere più percorsi (almeno 1, ma senza un limite massimo).
