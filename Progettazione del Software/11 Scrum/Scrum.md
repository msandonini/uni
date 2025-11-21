Scrum, nel rugby, è il termine che indica il pacchetto di mischia (i giocatori che si tengono stretti durante la mischia per guadagnare terreno verso la meta)

Scrum è un modello di processo per produrre software ottenendo il massimo valore utile nel minor tempo, che permette al cliente di ispezionare rapidamente e ripetutamente ogni 3-4 settimane versioni funzionanti del software.

In Scrum il cliente definisce funzioni e priorità, e il team di sviluppo decide il modo migliore di produrre le funzioni a priorità più alta.
Ogni 3-4 settimane nasce una nuova versione che viene esaminata per decidere se continuarne lo sviluppo con un altro sprint o produrne un rilascio.

Scrum si basa sulla trasparenza, e richiede che gli aspetti significativi del progetto siano **visibili** ai responsabili del risultato finale, e che tali aspetti siano definiti in modo tale che gli osservatori condividano una comune comprensione di ciò che viene visto.

Scrum è caratterizzato da diversi punti chiave:
- [[Sviluppo Agile|Metodo agile]], parzialmente pianificato
- Sviluppo agile guidato da storie e test
- Team di sviluppatori auto organizzante
- Il prodotto cresce in sprint di durata fissa
- I requisiti sono catalogati nel *product backlog*
- Per ogni sprint, ogni persona del team sceglie i requisiti da realizzare da uno *sprint backlog*
- I meetings sono caratterizzati da reviews e retrospettive, in visione di miglioramento continuo

## Sprint

Lo sprint è l'iterazione principale di Scrum, analoga alle iterazioni di [[09 RUP & OpenUP|RUP]].
Ogni sprint ha una durata costante di circa 2-4 settimane, ed include design, codifica e test.
Ogni sprint estrae funzioni "ready" dal product backlog e aggiunge codice "done" al prodotto da mostrare al cliente

## Ruoli

- Product owner
	- Rappresenta gli stakeholders (la voce del cliente)
	- Scrive il product backlog e le user stories
	- Definisce le features del prodotto
	- Decide i rilasci
	- Responsabile del valore del prodotto (ROI)
	- Mette in priorità le features rispetto al loro valore di mercato
	- Per ogni iterazione viene rivista la lista delle features e le loro priorità ove necessario
	- Accetta o rifiuta i risultati
![[Scrum_product_owner.png]]
- Scrum master
	- Rappresenta il management
	- È responsabile dei valori e pratiche Scrum
	- Facilita la corretta esecuzione del processo, ed elimina gli ostacoli
	- Supporta la cooperazione di ruoli e funzioni
	- È meglio se non è coperto dalla persona con ruolo di Product Owner
	- Non ha responsabilità di gestione del personale o di project management "tradizionale"
	- Anche se compreso nelle massimo 10 persone del team, non si occupa di sviluppo, ma si occupa di proteggerlo da interferenze esterne e si occupa del suo benessere
- Development Team
	- 3-9 membri ognuno con competenze diverse ma livello di esperienza analogo
	- Sono impegnati full-time (con alcune eccezioni, come ad esempio il database administrator che è molto costoso)
	- Il team è autoorganizzante
	- Tutti i membri del team sono nello stesso spazio di lavoro
	- Ogni modifica al team può avvenire solo tra uno sprint ed un altro (tutto il team deve seguire tutto lo sprint a cui è stato assegnato)
	- Diversi responsabili della consegna di un PSI (Potentially Shippable Increment)
![[Scrum_team_interaction.png]]

## Rituali (riunioni)

- Sprint planning meeting
	- Si definisce cosa fare (sprint backlog) e come aggiornare il product backlog
	- Sono 8 ore divise in 2 blocchi da 4
	- Analizzando il product backlog si realizza lo sprint backlog, ovvero vengono decisi gli elementi che verranno sicuramente realizzati nello sprint
		- Identificazione e stima di ciascun compito (1 - 16 ore)
		- Uso di Planning Poker
	- Si studia l'architettura di alto livello
![[Scrum_sprint_planning_meeting.png]]
- Daily Scrum / Stand-up
	- Ogni sviluppatore dice cosa ha fatto il giorno precedente, cosa pianifica per il giorno, e che impedimenti ha trovato
	- Dura 15 minuti, in piedi, e coinvolge tutto il team
- Sprint review
	- Riguarda il prodotto, concentrandosi su cosa è stato completato o non in questo sprint, e sulla demo
	- Dura al massimo 4 ore
- Sprint retrospective
	- Riguarda il processo, concentrandosi su cosa è andato bene e quali impedimenti si sono trovati
	- Dura al massimo 3 ore

