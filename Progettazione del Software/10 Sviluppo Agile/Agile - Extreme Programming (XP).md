---
tags:
---

*Extreme Programming* è una disciplina dello sviluppo software basata su valori di semplicità, comunicazione, feedback, e coraggio.

Il team di sviluppo è solitamente costituito da meno di 10 persone, riunito nello stesso locale (si lavora tutti insieme in open space), ed è sempre presente un rappresentante del cliente.
Il team deve usare comportamenti di sviluppo semplici ma capaci di informare tutti sullo stato del progetto e di adattare i comportamenti alla situazione specifica.

XP si divide in 4 fasi:
- Exploration
	- User stories
		- Sono i requisiti ma definiti come storie dell'utente
	- Architectural spikes
		- Tutto il punto di vista è basato sull'architettura (anche il linguaggio si lega all'architettura software)
		- Viene raccontato tramite una metafora di sistema, che si occupa di spiegare all'utente l'architettura in maniera che la possa capire
- Planning
	- Release planning
	- Spike
- Iterate2release
	- Iteration
		- Ogni iterazione lavora su release precedenti e ne produce una nuova
	- Acceptance tests
		- Si eseguono finché i test non ci definiscono che l'iterazione corrente è accettabile
- Production
	- Small releases

![[XP_phases.png]]

XP si basa sui seguenti principi:
- I requisiti sono "[[#User stories]]"
- La pianificazione avviene tramite "[[#Planning game]]"
- Piccoli rilasci
- Il cliente è sempre on-site
- [[#TDD (Test Driven Development)]], quindi i test si scrivono prima del codice
- Si usa una metafora di riferimento
- [[CI (Continuous Integration)]]
- Proprietà collettiva del codice (il codice scritto da uno può essere cambiato da un altro)
- Settimana di lavoro dalla durata definita
- Uso sistematico di standard di codifica (utilizzo di linee guida nella scrittura del codice)
- Programmazione di coppia
- Refactoring
- Progettazione semplice

## User stories

Le user stories sono scritte in linguaggio naturale dai clienti tramite piccole frasi con terminologia del cliente e definiscono un requisito (no techno-syntax).
Per ogni user points sono definiti:
- Priorità
	- Definita dal cliente
- Stima dei rischi e delle risorse
	- Definita dal team di sviluppo

Le user stories sono utili per stimare i tempi/costi di un rilascio (release planning).
Le user stories possono essere arricchite da altre storie durante lo sviluppo.

### Metafora di sistema

I progettisti sviluppano una visione comune di come funzionerà il programma, detta "metafora di sistema".
Esempio: un sistema di information retrieval basato su agenti potrebbe essere spiegato con la metafora di uno sciame di api (agenti) che va a raccogliere il polline (informazioni) per portarlo all'alveare.

## Planning game

Una volta che le user stories sono definite, le storie a più alto rischio e priorità sono affrontate per prime, in incrementi "time boxed".
Il Planning Game viene rigiocato dopo ciascun incremento.

Il cliente è sempre disponibile per chiarificare le storie e per prendere rapidamente decisioni critiche.
Gli sviluppatori non devono fare ipotesi o attendere le decisioni del cliente.

La comunicazione "faccia a faccia" minimizza la possibilità di ambiguità ed equivoci

## TDD (Test Driven Development)

In fase di TDD: 
- viene scelta una user story
- vengono definiti i test
- i test vengono automatizzati (tramite uso di unit testing)
Tutto deve girare prima dell'inizio della fase successiva.

I test di accettazione sono guidati dalle user stories, scritti con il cliente, funzionano come contratto, e misurano il progresso.

I rilasci sono timeboxed (durata "breve" prefissata), minimali ma comunque utili (microincrementi) e devono essere visti come progresso dal punto di vista del cliente (mai cose come "implementare il database").
Questo è fatto così da ottenere il feedback dal cliente quanto prima e più spesso possibile (feedback).
Dopo ciascuna iterazione viene eseguito nuovamente il planning game.

### Refactoring

Con refactoring si intende il miglioramento del codice esistente senza cambiarne la funzionalità.
Il refactoring è un costo (il cliente non ne vede un risultato vero e proprio o dei cambiamenti) ma è necessario, perché le conseguenti semplificazioni del codice, la rimozione delle ridondanze, e l'aumento dell'astrazione che ne derivano permettono di sviluppare più velocemente nelle fasi successive.

### Pair programming

La pair programming è tipica di XP, e si svolge così:
- 2 progettisti lavorano allo stesso compito su un solo PC.
- Quello con il controllo viene chiamato *driver*, mentre l'altro, che si occupa solo di osservare, si chiama *navigator*.
- Il driver scrive il codice, mentre il navigator legge ciò che il driver scrive
- Ogni 2/3 giorni driver e navigator si scambiano il ruolo
- Le scelte di programmazione vengono prese insieme

#### Continuous Integration (CI)

- La coppia scrive i test ed il codice di un task (= parte di storia utente)
- La coppia esegue tutto il test di unità
- La coppia esegue l'integrazione della nuova unità con le altre
- La coppia esegue tutti i test di regressione
- La coppia passa al task successivo a mente sgombra (capita una o 2 volte al giorno)
- L'obiettivo è prevenire l'*integration hell*

## Riunione in piedi

La riunione in piedi è una sorta di tredicesimo principio, che si colloca ogni giorno a inizio giornata, e dura circa 15 minuti.
Durante la riunione in piedi il team si ritrova in piedi, disposto in cerchio, e si parla di:
- Su cosa si è lavorato il giorno prima
- Su cosa si lavorerà il giorno corrente
- Definizione delle coppie di lavoro se non sono già definite
