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
- Community
- Public
- Hybrid
![[Pasted image 20260918121723.png]]


