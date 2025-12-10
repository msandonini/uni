---
tags:
  - progettazione_software
  - bpmn
  - esempi
  - esercizi
---
### Processo rimborso spese

![[BPMN_esempio_rimborso_spese.png]]

### Servizio clienti banca (2 versioni)

![[Banca.drawio.png]]

## Fast Food

- Dopo 30 minuti dalla cottura il cibo non può essere più venduto
	- Grossa quantità di cibo cucinato che deve essere buttato via
- Lunghe code alle casse di clienti che devono ordinare, pagare e prendere il cibo

Situazione As-Is:
- La cucina prepara dei lotti delle diverse tipologie di cibo e le mette a disposizione per la vendita
- Il cliente va alla cassa, ordina, paga ed attende la preparazione del vassoio da parte del cassiere
- Il cassiere, una volta ricevuto il pagamento, prende il cibo dalla cucina, verifica la sua validità (30 minuti), e prepara il vassoio da dare al cliente
- Se manca qualche tipologia di cibo (oppure è scaduto), attende la preparazione del cibo, bloccando la cassa

Cambiamento:
- Si ritiene che se la cucina varia la sua lavorazione da “lotti” a “just in time”, la quantità di cibo gettato diminuisce
- Si ritiene che se il cassiere non rimane bloccato dall'attesa della preparazione del cibo le code alla cassa diminuiscono

Situazione To-Be:
- Vengono introdotte due tipologie di cassa:
	- Automatica, in cui il cliente su una stazione di lavoro apposita, ordina il cibo, lo paga, e riceve uno scontrino con un numero. 
		- In questo caso ha uno sconto del 5%.
	- Assistita, in cui un operatore riceve l’ordine, il pagamento e consegna al cliente uno scontrino con un numero. In questo caso non c’è sconto
- La cucina riceve gli ordini e provvede alla cottura
- I vassoi con il cibo vengono ritirati da una fila diversa, dove un addetto prepara i vassoi, ed una volta pronti, chiama il numero dello scontrino
- Il cliente, quando il suo numero viene chiamato, va a ritirare il vassoio

Risparmio:
- Con la situazione To Be, il fast food spera di risparmiare 500€ a settimana sul cibo scaduto da buttare
- Si ritiene di poter utilizzare con più efficienza il personale, risparmiando 30.000€ anno di stipendi

Esercizio:
- Modellare i processi dello scenario To Be con la metodologia [[Notazione BPMN|BPMN]] (cliente e fast food su pool diversi)
- Eseguire la Gap Analysis tra lo scenario As Is e lo scenario To Be
- Definire, sulla base dei risultati della Gap Analysis, le necessità del nuovo sistema informatico
- Definire i criteri di convenienza di questo intervento di cambiamento e di introduzione di un sistema informatico
- Ipotizzare un diagramma di [[Gantt]] con il piano di progetto
- Definire il piano di change management

![[Fast food - pool.drawio.png]]

![[Fast food - subprocesses.drawio.png]]

## Pacchetto Viaggio

Modellare utilizzando BPMN il seguente processo di prenotazione di un pacchetto viaggio.
Il processo inizia quando l’utente, impiegato della società TalDeiTali s.r.l., accede al sito di prenotazioni on line della società PalmaViaggi s.r.l. e indica le date del suo viaggio. La società, ricevute le date, ricerca nel suo database tutte le possibili soluzioni di viaggio e le propone al cliente che ne seleziona una. Selezionato il viaggio, la società propone una lista di hotel eventualmente prenotabili nella città di arrivo. 
Il cliente può decidere se prenotare o meno uno degli hotel proposti. Terminata questa fase, la PalmaViaggi invia un riepilogo delle prenotazioni e si procede al pagamento.
Questo viene effettuato dalla parte amministrativa della società TalDeiTali. Ricevuto il pagamento, la PalmaViaggi procede a finalizzare le due prenotazioni di volo e hotel.
Le prenotazioni sono svolte in maniera contemporanea (la prenotazione dell’hotel deve essere effettuata solo nel caso in cui quest’ultimo è stato selezionato). Finalizzate le prenotazioni, la PalmaViaggi invia conferma dell’itinerario.
Il processo deve rispettare il seguente vincolo temporale: dal momento in cui la PalmaViaggi inizia la procedura di prenotazione del pacchetto viaggio (ricezione delle date del viaggio), il processo di prenotazione deve concludersi entro 15 minuti. In caso contrario, la PalmaViaggi cancella il processo e notifica la cancellazione della procedura di prenotazione.