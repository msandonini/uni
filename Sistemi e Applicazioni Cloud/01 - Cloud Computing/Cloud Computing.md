Il cloud può essere visto come una sorta di utility

Uno dei primi grossi effort per trasformare la capacità di calcolo della singola macchina in una capacità distribuita è stato il grid computing, con la divisione in organizzazioni virtuali.
Questo tipo di sistema è molto complesso, ed è pensato principalmente per il parallel computing, con un focus sui batch jobs, andando molto bene su jobs pesanti e continui schedulabili con ritardo, con il problema che i workloads reali sono variabili, e mostrano pattern quotidiani, settimanali, e stagionali.
Il problema di avere un sistema basato su batch jobs deriva dalla distribuzione delle risorse: come quantifico quanti nodi mi devo procurare? Devo regolarmi sul picco di utilizzo o sulla media? Il mese scorso ho fatto questo, ma questo mese aumenterà o calerà l'utilizzo?

L'idea base del Cloud Computing è di fornire qualcosa come servizio: Everything as a Service

In Cloud Computing ci sono diversi tipi di paradigma:
- Software as a Service
	- Software hostati in cloud e offerti come servizio
	- Esempi: Gmail, Salesforce
- Platform as a Service
	- API offerte come servizio
	- Esempi: Heroku, GAE, AWS
- Infrastructure as a Service
	- Macchine virtuali con determinate risorse allocate offerte come servizio
	- Necessita di un amministratore di sistema
	- Esempi: EC2, GCP
Nel calcolo dei costi bisogna tenere conto di cosa viene gestito:
- SaaS
	- Viene offerto un software già fatto
- PaaS
	- Vengono offerti runtime predefiniti dal provider sui quali sviluppare la propria app
- IaaS
	- Completo controllo
	- Completa responsabilità

Ad oggi la distinzione inizia a diventare non più così chiara, in quanto il paradigma PaaS si sta fondendo agli altri 2:
- SaaS+PaaS:
	- Offerto il software con la possibilità di aggiungere plugin tramite API, personalizzazioni, e integrazioni con altri servizi
- PaaS+IaaS:
	- Contesti con container, dove l'immagine è tua ma non è l'immagine del sistema operativo, quindi hai il controllo dei container ma non del sistema infrastrutturale (niente controllo sul sistema di base della macchina virtuale)

Esiste anche un'altra famiglia di paradigmi, legata al modello di deployment:
- Private
	- Azienda che è provider e utente dei suoi servizi cloud
- Community
	- Insieme di aziende che si associano per condividere servizi cloud
- Public
	- Azienda che è provider di servizi cloud per altre aziende
- Hybrid
	- Struttura cloud locale integrata con un cloud esterno
	- Esempio: database locale per dati sensibili e altri dati tenuti su un servizio esterno
	- Utile per mantenere dei dati o delle specifiche funzioni localmente facendo comunque offloading dei calcoli ad esterni
![[Pasted image 20260918121723.png]]

In un ambito di offerta servizi, ci sono diversi step possibili per la scalabilità:
- Step 1: servizio hostato localmente su un server bare-metal
	- Non posso hostare diverse applicazioni perché potrebbero avere dipendenze in conflitto tra loro
	- I server sono tipicamente sotto-utilizzati
	- La gestione è complessa
- Step 2: servizio hostato su una macchina virtuale che gira sul server
	- In questo caso è già un caso di paradigma IaaS
	- I costi per l'utente in questo caso, rimangono gli stessi sia che le risorse vengano utilizzate al massimo sia che rimangano idle per la maggior parte del tempo
![[Pasted image 20260918122845.png]]
- Step 3: granularizzazione delle applicazioni
	- Rendo le applicazioni granularizzate, così da calcolare i costi per l'utente in base all'utilizzo delle risorse
	- Sistema elastico (dal punto di vista dell'utente)
	- Sistema molto complesso e costoso (dal punto di vista del provider)

Definizione di cloud da parte del NIST: un modello che fornisce una serie di risorse computazionali ubique, convenienti, ed on-demand che può essere configurata e rilasciata in tempi brevi con gestione ed interazione con il provider minimi

![[Pasted image 20260918123724.png]]
