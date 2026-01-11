---
tags:
  - big_data
---


%% 2025/11/10 %%

slide 2 pipeline

tante figure professionali incaricate di ogni operazione della pipeline:
- **Data engineer** e **data labler**: etichettamento dei dati. Va poi analizzato che il dato sia di qualità e anche accessibile in poco tempo (una
  predizione che arriva dopo il fenomeno non ha senso).
- data analyst
- devops che fa funzionare l'algoritmo
- di nuovo data engineering e labler per la raccolta continua dei dati

> [!NOTE] Data Leak
> Dati che arrivano dal futuro e al momento della previsione non lo dovrei avere.
> Alcune variabili non le ho al momento della previsione, ma nel dataset di training invece ho tutto collegato, anche dati che sono successivi.

non sempre il machine learning è importante.
Per alcuni casi il machine learning non ha senso:
- Se ci sono delle regole banali e ben definite allora non ha senso usare un'inferenza dai dati.
- Se il problema cambia frequentemente non si può dover riallenare il modello troppo spesso.

Il machine learning non va usato se si vuole fornire spiegazioni delle previsioni.
Alcuni modelli sono spiegabili ma comunque non approfonditamente.

slide 6 quando non usare machine learning

i progetti di machine learning molto spesso falliscono
la maggior parte dei progetti di machine learning falliscono e non vanno in produzione
va fatto attenzione a capire quando usare il machine learning

in condizioni operative il modello di machine learning spesso ha performance diverse.
questo perchè i dati di training non rappresentano spesso la realtà

slide 8

il machine learning operativo studia anche perchè i progetti di ml falliscono

ci sono 3 livelli di cambiamento nel machine learning:
- cambiamento dei dati (il mondo reale cambia)
- cambiamento del modello
- ... (slide 11)

i modelli calano di prestazioni nel tempo

slide 12

machine learning operativo = standardizzazione di un approccio di machine learning

rischi se non si tiene conto dell'operatività del progetto

5 fasi del machine learning operativo:
- slide 16

se si mette un modello in produzione ci si aspetta che si abbia un effetto sull'ambiente.
Se nel modello non si considera questa cosa allora si ha un feedback loop che porta a degli errori esponenziali.

%% 2025/11/12 %%

In ambiente di produzione, è necessario sviluppare delle pipeline che permettano di generare dati su cui allenare un modello, monitorare le performance del modello, e raccogliere i dati di produzione per generare nuovi dataset.

In produzione il ML può essere concepito con 5 elementi chiave:
- Development
- Deployment
- Monitoring
- Iteration
- Governance

## Model Development

La fase di Development si sviluppa in 2 aspetti essenziali:
- Data Engineering Pipeline: la fase di creazione di un dataset su cui allenare il modello
- Training and evaluation: tutte le fasi del progetto che prevedono il training e la valutazione del modello per la preparazione dei parametri del modello da passare al modello in produzione. Si divide in 3 fasi:
	- Model training: la parte più computazionalmente onerosa della fase
	- Model evaluation
	- Model testing

Un modello deve possedere 2 proprietà fondamentali:
- Reproducibility: la proprietà del modello di essere riprodotto
- Responsible AI / Explainability: la proprietà del modello di spiegare perché ha risposto in tale modo ad un determinato input, così da semplificare il debugging del modello stesso e i valori a cui prestare particolare attenzione, così da prevenire risultati non intesi

Alcune tecniche di explainability consistono in:
- Partial dependence plot: crea un plot che mostra l'impatto di ogni feature sul risultato
- Subpopulation analyses: controlla il comportamento del modello su sottoinsiemi del dataset
- Individual predictions

### Data Engineering Pipeline

La Data Engineering Pipeline è composta da diverse operazioni:
- Data Ingestion
	- Crea un dataset unendo diversi frameworks e formati
	- Può contenere dati sintetici o arricchiti
- Exploration & Validation
	- Si esegue profilazione dei dati (valori medi, mini, massimi, ecc...)
	- Si esegue validazione dei dati per trovare eventuali problemi nel dataset
- Data Wrangling (Cleaning)
	- Si riformattano gli attributi e si correggono gli errori
- Data Labeling
- Data Splitting
	- Si divide il dataset in set di training, validation, e test

Questo processo è molto lento e consuma molto tempo, ma è necessario per il corretto funzionamento del modello

#### Data Ingestion

- Data sources identification
- Space estimation
- Obtaining data
- Back up data
- ...

Domande che ci dobbiamo porre riguardo il dataset ottenuto sono riguardanti le dimensioni del dataset, se è utilizzabile (controlliamo valori nulli, duplicati, outdated), e se i dati sono comprensibili

Le principali cose che dobbiamo controllare in un dataset sono le seguenti:
- Dimensioni
- Utilizzabilità
- Comprensibilità
- Affidabilità
	- Feedback loop: proprietà del modello di ottenere dati da sé stesso. È soggetto a problemi di auto-amplificazione
	- Data leakage: introduzione involontaria nel dataset di informazioni che non sarebbero dovute essere state fornite al modello

Problemi comuni riguardanti i dati sono:
- Costo
	- Labelling
- Bassa qualità
- Rumore
- Bias
	- Selection bias: la tendenza ad inserire solamente parametri che sono più facili o convenienti da raccogliere
	- Self-selection bias: una forma di selection bias dove si ottengono dati da volontari
	- Omitted variable bias: non ci sono abbastanza dati per una certa variabile
	- Sampling bias: la distribuzione dei dati di training non riflette la distribuzione dei dati effettivi
	- Prejudice bias
	- Experimenter bias: la tendenza a cercare, interpretare, e favorire informazioni in una maniera che conferma un bias pregresso
	- Labeling bias

#### Exploration & Validation

- Data profiling: ottenimento di informazioni riguardanti il contenuto e la struttura del dataset
- Data validation: controllo sulla qualità dei dati usando funzioni di error detection definite dagli utenti

Le best prectices sono:
- Attribute profiling
- Label attribute identification
- Data visualization
- Correlation analysis

#### Data Wrangling

- Applicazione trasformazioni
- Gestione outlier
- Gestione missing values
- Rimozione di dati non rilevanti
- Feature engineering
- Ristrutturazione dei dati
	- Creazione di nuovi campi basandoci su valori precedentemente estratti
	- Combinazione di campi multipli in campi singoli
	- Filtraggio del dataset rimuovendo determinati campi
	- Modifica della granularità dei dataset tramite aggregazione e pivots

Lo riempimento di valori mancanti si chiama Data Imputation

Nella gestione dei valori nulli è necessario, se si esegue Data Imputation, dividere in train e test prima di riempire i valori nulli, perché altrimenti eseguo Data Leakage, in quanto se eseguo ad esempio una media per ottenere il valore da sostituire ai nulli, la media globale di tutto il dataset sarà diversa dalla media locale di solo il dataset di train

#### Data Labeling

Problema principale del Labeling è che potremmo avere la target class sbilanciata, in quanto solitamente che ci interessa è la parte più piccola dei dati (es. ci interessa se un messaggio è spam, non il contrario). Per supplire a questa cosa si utilizzano tecniche di oversampling del caso meno prevalente, oppure undersampling del caso più prevalente.

##### Oversampling
- SMOTE (Synthetic Minority Oversampling Technique)
	- Dato un sample $x_i$ della classe minoritaria, prendo i $k$ nearest neighbors
	- Denoto questo set di $k$ samples come $S_k$
	- Il sample sintetico $x_{new}$ è una copia perturbata del valore di partenza, ed è definito come $x_i + L(x_{zi} - x_{i})$, dove $x_{zi}$ è un sample della classe minoritaria scelto randomicamente in $S_k$
	- Il parametro di interposlazione $L$ è un numero nel range $[0, 1]$
- ADASYN (Adaptive Synthetic Sampling Method): ottimizzazione di SMOTE

##### Undersampling
- Può essere randomico
- Può essere basato su alcune proprietà
	- Tomek Links: proprietà basata su 2 istanze $x_{i}$ e $x_{j}$, dove $x_i$ è il nearest neighbor di $x_j$ e viceversa, ma appartengono a classi differenti. Questo significa che se si rimuove una delle 2 istanze riduco l'overfitting, in quanto sto separando maggiormente i dati tra una classe all'altra

#### Feature Engineering
Processo di creazione e selezione di feature tramite processi diversi metodi:
- Derivatives
- Enrichment
- Encoding
- Combination
### Experimentation
Gli obiettivi principali di questa fase sono determinare quanto possa essere buono e utile il modello che si sta costruendo
### Evaluation and Comparing Models

- Scelta delle metriche
- Analisi dell'errore

Per confrontare diversi modelli si imposta una baseline, in base al comportamento umano, alla letteratura, e a vecchi sistemi, e si cerca analizzare il comportamento del modello profilando i vari errori (capendo dunque l'errore nelle varie condizioni di utilizzo del modello), così da capire le priorità per quanto riguarda le correzioni e i miglioramenti da eseguire.

Per poter confrontare correttamente i vari modelli serve utilizzare un sistema di Version Management per provare diverse combinazioni e fare il revert di eventuali modifiche nel caso in cui un modello passato performasse meglio di quello attuale.

### Preparazione per la produzione

Scenari diversi:
- Seamless deployment
	- Le piattaforme di development e production sono compatibili tra loro
	- Il deployment richiede pochissimi click
	- L'effort si può concentrare sulla validazione
- Reimplementation
	- Il modello potrebbe necessitare di essere riscritto da zero, anche da un team diverso o in un linguaggio differente
	- L'implementazione può impiegare molto tempo
- Caso intermedio
	- I modelli potrebbero necessitare di modifiche per adattarsi all'ambiente di production

Le performance in produzione devono tenere conto di:
- Latenza ed ambiente
- Problemi relativi al Deep Learning (costi molto alti in quanto sono modelli che necessitano di elevata potenza computazionale)
- Tecniche di ottimizzazione
	- Quantizzazione: riduco la precisione dei dati (es. float a 32 bit)
	- Pruning: rimuovo pesi o layer dalla rete
	- Distillation: modello più semplice che emula il comportamento di un modello più largo

#### Valutazione dei rischi del modello

L'obiettivo è la minimizzazione dei rischi in ambiente di produzione


## Deployment in produzione

Normalmente si utilizza l'approccio CI/CD (Continuous Integration / Continuous Deployment), che consiste nello sviluppare costantemente il modello automatizzando testing, validation, e deployment tramite diverse pipeline impostate sul VCS

Una volta che il codice e i dati sono in una repo centralizzata, un bundle del progetto può essere rilasciato

## Testing pipeline

L'obiettivo della pipeline di testing è validare le proprietà del modello così da semplificare la diagnosi in caso di fallimento del modello.
In questo caso è essenziale non limitarsi a test riguardanti solo il base case ma andare a testare anche gli edge cases, e testare sempre il tutto con dati di produzione recenti, così che i test non siano datati.

Quest pipeline assicura la robustezza e l'affidabilità del modello, oltre che la preparazione ai casi inaspettati.

3 principali approcci per caricare il modello in produzione
- Blue-green: il modello viene caricato direttamente dopo i test e viene revertato in caso di problematiche
- Shadow: tengo il modello precedente attivo e metto il nuovo modello a lavorarci in contemporanea, per poi attivare il modello nuovo in produzione solo quando mi sarò sicuro che esso è migliorativo
- Canary: attivo in produzione sul nuovo modello solo per un gruppo limitato di utenti, che aumenta pian piano nel mentre che

Gli approcci Shadow e Canary implicano la presenza di più hardware per mantenere i modelli diversi

Altra cosa molto utile in produzione è l'utilizzo di modelli di containerizzazione per il mantenimento dei modelli

## Monitoring

È necessario mantenere monitorato il modello in quanto il modello si può degradare (non rappresenta più bene la realtà).

Principali cause della degradazione sono:
- eventi improvvisi (es. guerra o Covid)
- dati che non tengono conto della stagionalità dei dati
- dati che cambiano nel tempo
- feedback loop (dati che si sono auto-amplificati nel tempo)

La verifica dell'accuratezza è molto difficile in produzione, in quanto per calcolarla è necessario avere un riferimento, che spesso non ho, o che comunque comporta un costo (monetario o di tempo che esso sia).

%% 2025/11/17 %%

Per determinare la degradazione le tecniche più efficaci sono:
- Resource monitoring: si tiene traccia dell'utilizzo di CPU, memoria, disco e rete per determinare se ci sono problemi
- Health check: Si eseguono query a intervalli fissati e si tiene il log dei risultati
- ML metrics monitoring

> [!NOTE] Drift, Decay & Staleness
> Diversi tipi di degradazione del modello, che fanno si che le performance passate di un modello ML non permangano nel tempo

### Drift

Con *data drift*, *feature drift*, *population*, *covariate shift* si intende la degradazione dovuta al fatto che nel tempo i dati di input sono cambiati e di conseguenza il modello non è più rilevante per i dati del mondo reale.

Con *concept drift* si intende la degradazione dovuta al fatto che la realtà è cambiata rispetto a quella su cui ho cambiato il modello.
Questo avviene solitamente in base a evoluzioni o cambiamenti del mondo in analisi (es. lancio di nuovi prodotti sul mercato, stagionalità, ecc...)

Il concept drift può essere *graduale* (stagionalità, come ad esempio Black Friday, cambio stagioni, ecc...) o *improvviso* (COVID-19, guerre, ecc...)

Per monitorare la degradazione dovuta al drift possiamo analizzare le seguenti metriche:
- Software (temperature, larghezza di banda, ecc...)
- Input (lunghezza o dimensioni medie, numero di missing values)
- Output (numero di out nulli, frequenza di retries degli utenti)

### Model Retraining

Aspetti chiave da considerare per decidere quanto spesso eseguire retraining del modello sono:
- Dominio
	- Domini più veloci necessitano di aggiornamenti più spesso (es. cyber security)
	- Domini più stabili avranno bisogno di meno aggiornamenti
- Costo
- Performance

Normalmente, su ognuno di questi aspetti, vengono impostati dei bound:
- Lower bound
	- Determinato dal tempo impiegato per ottenere la ground truth, ovvero dal tempo impiegato per ottenere le etichette
- Upper bound
	- Impostato da considerazioni organizzazionali e operazionali
	- Il retraining dovrebbe avvenire periodicamente (es. annualmente)
## Iteration

Fase che tiene conto del feedback loop, e cioè deve tenere conto del fatto che tramite il modello noi siamo andati ad influire sulla realtà 
## Governance

Fase che si assicura che il modello sia tracciabile, rispetti le regole, ecc...