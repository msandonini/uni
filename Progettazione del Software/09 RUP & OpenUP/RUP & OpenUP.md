---
course: Progettazione del Software
---
%% 2025/11/14 %%

## Rational Unified Process (RUP)

La prima metodologia utilizzata nella gestione del ciclo di vita del software era *Waterfall*, in cui il progetto era diviso in fasi sequenziali rigide in cui poteva essere studiata una fase sola per volta.
Come risposta alle varie problematiche di Waterfall, a metà degli anni 90 è stata creata la metodologia *Rational Unified Process (RUP)*, che è sostanzialmente la sintesi di tutti i metodi che hanno portato alla definizione dell'*UML* (gli autori sono gli stessi).

RUP utilizza fasi sequenziali come Waterfall, tuttavia introducendo in ogni fase diverse discipline che potevano intervenire all'interno di ogni fase, permettendo l'analisi di discipline diverse nella stessa fase, ed implementa le best practices dell'ingegneria del software.

RUP è inoltre caratterizzata da un'iterazione, in quanto la stessa fase può essere divisa in n blocchi fissi, in cui in ogni blocco ci si concentra su una porzione dell'applicazione, ed al termine di ogni blocco quella porzione dell'applicazione è completamente sviluppata (testing incluso).
L'utilizzo del metodo iterativo permette al cliente di vedere le varie funzionalità complete dell'applicazione durante lo sviluppo della stessa, così da ridurre le problematiche relative le incomprensioni e permettere eventuali correzioni del comportamento dell'applicazione direttamente durante la fase di sviluppo del software.

Per quanto nata prima delle metodologie Agile, questa metodologia è considerata un po' un suo precursore, in quanto diverse caratteristiche di RUP si possono poi ritrovare nelle metodologie Agile

RUP si chiama così perché Rational è il nome dell'azienda che ha creato la metodologia. L'azienda è stata poi comprata da IBM.

Le 4 fasi di RUP sono:
- Inception
	- Fase di ideazione in cui si pensa all'ambito e all'architettura
	- Solitamente dura solo pochi giorni ed è caratterizzata da una sola iterazione, in quanto è pensata come fase di scrittura del contratto
	- L'obiettivo è definire cosa verrà inserito o meno nell'applicazione, e la portata del progetto (in termini di tempo e costo)
- Elaboration
	- Fase in cui si elabora l'idea e si crea l'architettura ad alto livello
	- Solitamente divisa in 1/2 iterazioni
	- L'obiettivo è specificare le caratteristiche (features) del progetto e la baseline dell'architettura, dimostrando che quest'ultima sia funzionante
- Construction
	- Fase di implementazione del software
	- Divisa in n iterazioni in base alla durata stimata dell'implementazione e alla complessità del progetto
	- L'obiettivo è realizzare il prodotto
- Transition
	- Fase di testing del software
	- Divisa solitamente in 1/2 iterazioni in base alla complessità
	- L'obiettivo è eseguire le procedure necessarie per passare il prodotto agli utenti finali

RUP è focalizzata sull'architettura, cioè si basa sull'utilizzo di architetture di riferimento già esistenti così da semplificare e velocizzare lo sviluppo
Per ogni cosa sono forniti casi d'uso UML che spiegano cosa fare per ogni fase

Vengono definite almeno 4 *milestones* nelle quali, per ogni fase, vengono definiti gli obiettivi al termine di ogni fase. Possono essere definite anche più di 4 milestones, a seconda della complessità e della portata del progetto. Le 4 milestones minime sono le seguenti:
- Obiettivo ciclo di vita (fine inception)
	- Accordo su cosa è dentro e cosa è fuori dal progetto e sulla stima dei tempi e costi del progetto
- Architettura (fine elaboration)
	- Stabilità della vision del prodotto e dell'architettura
- Capacità operativa iniziale (fine construction)
	- Maturità del prodotto per poter iniziare il rilascio
- Rilascio del prodotto (fine transition)
	- Conclusione del rilascio e accettazione del cliente

Esistono anche milestones secondarie, ovvero delle milestones intermedie poste alla fine delle iterazioni di ogni fase.
Un'iterazione non è un punto in cui si controlla lo stato di avanzamento del progetto, bensì è una sequenza di attività basate su un piano di sviluppo e dei criteri di valutazione che risultano in una nuova versione eseguibile, in cui al termine dell'iterazione bisogna aver concluso quanto previsto, come fosse un mini-progetto.
Un'iterazione ha una durata fissa e costante (*time-boxed*), di conseguenza il numero di iterazioni per ogni fase dipende dalla durata delle fasi, e quindi da quando si riesce a superare le rispettive milestone.
L'ammontare dei requisiti da sviluppare in un'iterazione cambia nel tempo, iniziando più cautamente ed aumentando con l'esperienza del team ed il grado di maturazione del sistema
Al termine di ogni iterazione si analizzano i feedback dal test dell'iterazione. Tali feedback vengono valutati rispetto gli obiettivi generali di progetto, e date le richieste di cambiamento viene aggiornato il piano di progetto e definito il piano dell'iterazione successiva.

### Fase di Ideazione

L'obiettivo principale è l'accordo tra tutte le parti interessate (*stakeholder*) su:
- Obiettivi del progetto
- Budget
- Tempi

I risultati attesi per questa fase sono:
- Un *documento di visione*
- Studio degli *use cases*
- Studio economico con tempi, costi, rischi, e criteri di successo
- Un piano di progetto

Le milestones per questa fase sono:
- Gli stakeholders sono d'accordo sull'ambito e sulla portata del sistema, cosa è dentro e fuori dallo stesso, e sulla stima di tempi e costi
- La comprensione dei requisiti è presentata dal modello dei casi d'uso, con la specifica dei casi d'uso principali a livello di sommario (*outline*)
- Viene valutata la credibilità delle stime di costo e tempo, e le priorità assegnata

### Fase di Elaborazione

L'obiettivo principale è definire convalidare, e creare una baseline dell'architettura eseguibile, aggiornando la baseline del dpocumento di visione, e dimostrare che l'architettura identificat supporterà la visione di progetto con tempi e costi ragionevoli

I risultati attesi per questa fase è la descrizione dell'architettura software validata dall'esecuzione del software realizzato, tramite:
- Modello dei casi d'uso che si ritiene abbastanza completa (all'80%)
- I requisiti supplementari descritti e compresi
- Lista dei rischi e piano di sviluppo

In questo caso la milestone è l'architettura, dunque:
- Si valuta la stabilità della vision del prodotto e dell'architettura
- L'architettura eseguibile deve dimostrare che l'architettura sarò in grado di supportare le funzionalità del sistema ed esibire un comportamento corretto in termini di prestazioni, scalabilità e costi
- Pianifiche e stime su cui tutti gli stakeholder si trovano ragionevolmente d'accordo
- Gli stakeholder accettano la visione del prodotto ed il piano di progetto, inclusi i livelli di spesa

> [!NOTE] Architettura eseguibile
> Implementazione parziale del sistema che include le componenti più significative dell'architettura

### Fase di costruzione

L'obiettivo principale è il completamento di versioni eseguibili del software, raggiungendo una qualità adeguata il più rapidamente e realisticamente possibile, gestendo e controllando risorse, tempi, e costo di sviluppo

I risultati attesi sono:
- Software integrato su tutte le piattaforme stabilite
- Descrizione del sistema ed eventuali manuali utente

In questo caso la milestone è la capacita operativa iniziale, ovvero:
- Maturità del prodotto per poter iniziare il rilascio
	- Per progetti su commessa il cliente deve dirmi che le principali funzionalità sono state tutte definite e funzionanti, accettando il prodotto
	- Per progetti venduti sul mercato, deve essere pronta la beta
- Le parti interessate sono pronte alla transizione verso la comunità degli utenti

### Fase di transizione

L'obiettivo principale è la preparazione per la messa in esercizio del sistema, facendo in modo che gli utenti non siano solo in grado di utilizzare il sistema ma assicurandosi che l'intera comunità degli utenti conosca il nuovo sistema e ne apprezzi il valore (non ci sia dunque resistenza al cambiamento)

I risultati attesi di questa fase sono:
- Prontezza per l'entrata in esercizio ufficialmente
- Compimento di eventuali migrazioni dei dati
- Avviamento delle attività di marketing

La milestone per questa fase è il rilascio del prodotto, che avviene quando il sistema p pronto per la messa in esercizio e il cliente accetta il prodotto

### Business modeling

L'obiettivo del business modeling è comprendere la struttura e la dinamica dell'organizzazione a cui ver

### Requisiti di disciplina

L'obiettivo è comprendere e comunicare i requisiti di sistema, sia funzionali che non funzionali, tramite una gestione degli stessi e dei loro cambiamenti, ed offrendo supporto alla pianificazione dello sviluppo per ogni iterazione

I ruoli principali sono Architetto, Analista, Progettista di Sistema, Progettista UI, ecc...

Gli elaborati principali sono:
- Documento di visione
- Modello dei casi d'uso
- Specifiche dei casi d'uso
- Specifiche supplementari
- Attributi dei requisiti e matrici di tracciabilità
- Glossario

### Analisi e progettazione

L'obiettivo di questa disciplina èè l'ideazione di un modello dell'implementazione che realizzerà il sistema soddisfacendo requisiti e bisogno degli stakeholders

I ruoli principali sono Architetto, Progettista Software, e Progettista Database

### Implementazione

L'obiettivo è l'implementazione di classi e oggetti, unit testing, e integrazione di quanto sviluppato in un sistema eseguibile

I ruoli principali sono Sviluppatore e Sistemista d'integrazione
Gli elaborati principali sono Componenti software (Sorgenti, Eseguibili, DLL) e Piano di integrazione


### Test

L'obiettivo è la verifica della corretta implementazione dei requisiti, dell'integrazione delle componenti, e dell'identificazione e risoluzione di eventuali difetti

I ruoli sono Progettista Test e Tecnico dei Test, Tecnico Test prestazionali, Tecnico Test sistema, che tuttavia stanno perdendo importanza a favore dello unit testing

---

%% 2025/11/19 %%

### Utilizzo

RUP non è un processo, bensì un framework di processo dal quale istanziare il proprio processo di sviluppo software, che dovrebbe essere personalizzato con un'attività di tailoring da ogni organizzazione in base alle esigenze.

IBM Rational Method Composer è lo strumento che permette quest'attività di tailoring.

#### Documento di visione
Il documento riassume velocemente il progetto, descrivendo:
- Scopo
- Obiettivi
- Requisiti
- Vincoli
- Architettura
- Gestione licenze
- Riassunto funzionalità

#### Casi d'Uso
Il documento dei casi d'uso contiene, per ogni caso d'uso:
- Breve descrizione
- Priorità
- Livello funzionale
- Attori
- Scenario principale
- Scenari alternativi
- Punti di diramazione
- Eventuali informazioni aggiuntive

#### Documento dei requisisti non funzionali
Riguarda tutto ciò che non è legato al singolo modulo da sviluppare, è diviso in varie sezioni:
- Storia delle versioni (opzionale)
- Funzionalità trasversali
	- Sicurezza: specifica i requisiti di sicurezza dell'applicativo
	- Logging
- Usabilità e Accessibilità: definisce come l'applicativo deve essere accessibile
- Affidabilità
- Prestazioni: definisce quali sono le prestazioni richieste dal modulo
- Adattabilità e Configurabilità
	- Adattabilità: adattabilità della logica applicativa a sistemi sia in linea che fuori
	- Configurabilità
	- Internazionalizzazione
- Regole di funzionamento del dominio
- Informazioni sui domini collegati
- Vincoli tecnologici
- Scelte architetturali e implementative
- Interfacce verso altri sistemi

### Evoluzione del RUP

Negli anni RUP si è evoluto in 3 direzioni:
- Influenzando la standardizzazione di OMG del metaprocesso SPEM
	- Dal quale sono nati [[OpenUP]] ed [[Eclipse Open Framework (EOF)]]
- In un prodotto per la definizione di processi di sviluppo
	- [[IBM Rational Method Composer]]
- Facendo da padre putativo a vari altri metodi di sviluppo
	- Evoluzioni ed adattamenti di processi, partiche, e tecniche emergenti, come per esempio il movimento di "[[Sviluppo Agile|Sviluppo Agile]]"
	- Esempi sono [[Unified Process (UP)]], [[Agile Modeling (AM)]], [[Disciplined Agile Delivery (DAD)]], ed [[Enterprise Unified Process (EUP)]]

