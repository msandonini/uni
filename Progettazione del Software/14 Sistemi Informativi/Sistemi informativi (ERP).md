---
tags:
  - progettazione_software
  - erp
aliases:
  - ERP
---
I produttori più noti sono:
- SAP
- ORACLE
- MS
	- AX
	- DX

In Italia, per le medie imprese, i più diffusi sono:
- Teamsystem
- Zucchetti

Ad un'azienda non interessano i semplici dati ma le informazioni, ovvero dati associati al loro contesto, di conseguenza le strategie che ne supportano la gestione sono passate da essere uno strumento accessorio ad essere uno strumento strategico.
Questi strumenti che ne supportano la gestione svolgono 2 funzioni principali:
- *Sistema organizzativo*
	- Insieme di risorse e regole per lo svolgimento coordinato delle attività al fine del perseguimento degli scopi
- *Sistema informativo (SI)*
	- Componente di un'organizzazione che gestisce (acquisisce, elabora, conserva, produce, scambia) le informazioni di interesse
	- Parte del sistema organizzativo
	- Indipendente dall'automatizzazione

Se il sistema presenta delle funzioni di automatizzazione, quella parte di sistema prende il nome di *Sistema informatico*, e funziona solitamente tramite l'uso di Digital Twin.

La gestione dell'informazione implica diverse attività:
- Creare informazioni
- Acquisire informazioni
- Elaborare informazioni
- Archiviare informazioni
- Distribuire e scambiare informazioni
- Presentare informazioni

La gestione dell'informazione può essere di 3 tipi:
- Implicita
	- L'informazione è gestita da un dipendente
- Esplicita non supportata da ICT
	- Informazione accessibile tramite documenti cartacei
- Esplicita supportata da ICT
	- Informazione accessibile tramite sistema informativo

Il sistema informativo produce informazioni sulla base di eventi, dividendo dunque i ruoli in:
- Generatori di eventi
- Utilizzatori

Gli eventi si basano su diverse componenti:
- Dati
	- Rappresentano una descrizione degli eventi
	- Una figura preposta deve identificare quali dati tenere e quali no
- Principi
	- Modalità di raccolta, elaborazione, distribuzione dei dati
	- Si sta man mano virando su sistemi sempre meno invasivi per l'uomo (virando dunque nel mondo [[IoT]])
- Procedure
	- Specifiche in funzione del processo realizzato
	- Indipendenti dagli strumenti impiegati
- Persone + ICT
	- Ruoli e tecnologie usate per attuare il sistema informativo
- Macchine + Utenti
	- Destinatari delle informazioni, siano essi interni o esterni

Progettazione ed utilizzo di un sistema informativo  richiedono principalmente 3 classi di competenze:
- Organizzazione
- Tecnologia
- Management

Storicamente, un'organizzazione è rappresentata tramite:
- Funzioni
- Processi
- Piramide di Anthony
L'obiettivo finale di sistema informatico è rappresentare fedelmente l'organizzazione in cui viene utilizzata

### Rappresentazione per funzioni

Un sistema informatico basato su rappresentazione per funzioni è caratterizzato da tanti blocchi, uno per ogni funzione, che organizza dati in silos quasi indipendenti tra loro
La rappresentazione per funzioni è considerata ormai obsoleta, ed è caratterizzata da diversi vantaggi e svantaggi:
- Vantaggi
	- Sistemi informatici specializzati per funzioni
	- Alta efficienza "locale"
- Svantaggi
	- Scarsa integrazione e conseguente scarsa capacità di rispondere in tempi brevi alle esigenze del mercato
	- Possibilità di ridondanza o inconsistenza dei dati
	- Impossibilità di modellare relazioni inter-organizzative

### Rappresentazione per processi

La rappresentazione moderna è quella per processi, che pone l'enfasi sulla creazione del valori tramite processi che coinvolgono più funzioni, causando:
- maggiore enfasi sul coordinamento
- passaggio da obiettivi locali a obiettivo globale
In questo tipo di rappresentazione è più difficile scomporre l'organizzazione in processi

La rappresentazione per processi presenta diversi vantaggi e svantaggi:
- Vantaggi
	- Esplicitazione dei flussi informativi dell'organizzazione
	- Favorito lo sviluppo di sottosistemi orientati al supporto di interfacce di comunicazione tra le funzioni coinvolte
- Svantaggi
	- Difficoltà nell'identificazione dei processi
	- Possibile impatto organizzativo

### Rappresentazione di Anthony

La rappresentazione di Anthony è nata per classificare le attività svolte nell'organizzazione (e non la struttura).
Questa rappresentazione può essere considerata come un'integrazione alla rappresentazione per processi, che pone enfasi sulle attività e aggiunge proprietà specifiche ai processi stessi.
La rappresentazione di Anthony si basa sul principio che attività dello stesso livello impiegano informazioni dello stesso tipo

## Processi

### Checklist

La [[American Productivity and Quality Center (APQC)]] checklist divide i 12 processi principali in 70 sottoprocessi. I 12 principali sono:
- Comprensione dei mercati e dei consumatori
- Sviluppo della vision e della strategia
- Sviluppo prodotti e servizi
- Marketing e vendite
- Produzione e consegna prodotti
- Fatturazione e servizi al cliente
- Sviluppo e gestione delle risorse umane
- Gestione dell'informazione
- Gestione delle risorse fisiche e finanziarie
- Realizzazione di programmi per la tutela ambientale
- Gestione relazioni esterne
- Gestione del cambiamento

Questa checklist garantisce il vantaggio della semplicità, tuttavia è poco funzionale per settori poco regolamentati o poco omogenei, e richiede un'approfondita analisi dell'organizzazione

## Categorie di sistemi informatici

- EDP (Electronic Data Processing)
	- Gestione amministrativa
		- TPS (Transaction Processing Systems)
- [[#Sistemi operativi di gestione|MIS]] (Management Information Systems)
	- Gestione della produzione e della logistica
		- MRP
		- SCM 
		- ERP
	- Gestione della conoscenza
		- KMS
		- CAD
		- CAE
		- CAM
- EIS (Executive Information Systems)
	- Sistemi a supporto delle decisioni
		- DSS
		- ESS
	- Sistemi per la gestione del rapporto con i clienti
		- CRM

### Sistemi operativi di gestione


