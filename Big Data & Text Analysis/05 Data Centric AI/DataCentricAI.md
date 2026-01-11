---
tags:
  - big_data
---
%% 2025/11/10 %%

# Data-Centric AI
Tradizionalmente, il mondo dell'IA si è sempre diviso in due fazioni:
- **Model-Centric AI**: che sostiene che il modello sia più importante dei dati
- **Data-Centric AI**: che sostiene che il dato sia più importante del modello

Entrambi gli approcci sono ugualmente giusti.
Nel machine learning servono sia il modello che i dati.

Se il modello è molto performante ma i dati sono sporchi, allora ci sono problemi.
Se i dati sono puliti e ottimali ma il modello non è adatto, allora ci sono ugualmente problemi.

Assumendo di avere modelli molto buoni e performanti, la Data-Centric AI si concentra sui dati.

Con "Data-Centric AI" si fa riferimento a quelle operazioni per estrarre e mantenere dati per sistemi di machine learning e AI.
Le performance del sistema di machine learning o AI dipendono non solo dal modello, ma anche dai dati.

> [!NOTE] Garbage In Garbage Out
> Secondo l'approccio data centrico, se in input si hanno dati non adeguatamente trattati o di scarsa qualità, il modello avrà scarse performance.

Nella Data-Centric AI ci si concentra su 3 aspetti:
- **Training data development**: estrazione / sviluppo dei dati di training
- **Inference data development**: estrazione / sviluppo dei dati usati per testing del modello
- **Data mantainance**: mantenimento e continua estrazione dei dati

Mettere in produzione un modello di ML comporta un riallenamento periodico. Questo poichè i dati cambiano, perchè il mondo si evolve.
Non si può quindi avere un solo allenamento prima di mettere in produzione il modello, poichè a lungo andare questo calerà di prestazioni.

## Training Data Development
Come prima cosa, nel machine learning va sviluppata una pipeline per estrarre i dati di training.

Questa pipeline si compone dei seguenti 5 passaggi:
- Data **collection**
- Data **labeling**
- Data **preparation**
- Data **reduction**
- Data **augmentation**

### Data Collection
È il processo messo in atto per estrarre dei dati da una o più sorgenti, focalizzato sull'estrazione di dati di qualità.

La valutazione delle sorgenti dei dati (e quindi della qualità dei dati) può avvenire in due modi:
- Grazie alla valutazione di un esperto del dominio
- Procedendo per tentativi

Nel processo di data collection si possono usare dataset già esistenti o si può creare dei dataset da zero.
La creazione di un dataset dal nulla, però, è un processo time consuming, e va quindi calcolato un ritardo nella messa in produzione del modello.

All'interno del processo sono presenti due sotto-operazioni:
- Data **discovery**: identificazione di dataset utili
- Data **integration**: combinazione di dataset diversi in un unico dataset unificato
- Raw data **synthesis**: creazione di una rappresentazione sintetica dei fenomeni interessati

> [!TIP] Distanza di Dataset
> Esistono delle misure che permettono di capire la distanza tra due dataset.
> Queste possono essere usate per:
> - Capire se il dataset è di qualità (attraverso il confronto con dataset di qualità)
> - Capire se i dati sono ripetuti da più sorgenti

> [!NOTE] Altre Sfide della Data Collection
> Sono inoltre sempre da considerare anche altri aspetti nella data collection.
> Ad esempio, vanno considerati aspetti di tipo etico e sul trattamento corretto dei dati sensibili.

#### Data Discovery
È effettuata principalmente interrogando grandi repository di dati ed utilizzando metriche per il calcolo della distanza tra dataset (per capire se il
dataset trovato è di qualità).

#### Data Integration
Si possono voler raccogliere dati da fonti diverse e integrarle in un unico dataset.
Per farlo, deve essere effettuata un'operazione di **merging** dei dataset.

Si può effettuare questa operazione di unione:
- Basandosi su **attributi** (ad esempio usando la data di raccolta del sample)
- Basandosi su specifiche **regole**

Gli approcci basati su regole solitamente non sono scalabili, in quanto richiedono la presenza di un esperto che analizzi i dati e fornisca le regole.

Si possono quindi usare approcci di machine learning per avere regole di integrazione e scalabilità.
Sono infatti utilizzabili dei sistemi di classificazione che predicano come integrare i dati, prevedendo per ogni dato se esso corrisponde o si integra
correttamente con dati provenienti da altre fonti.

#### Raw Data Synthesis
È l'operazione di sintesi dei dati, che permette di creare rappresentazioni sintetiche di un dato fenomeno interessato.

Ad esempio, nel caso di un task di anomaly detection, vanno rappresentate nei dati molte anomalie.
Il modello deve essere allenato su dati che rappresentano le anomalie, anche se nella realtà questi sono la minoranza.

Inoltre, spesso le anomalie sono rare, e intercorre molto tempo tra un'anomalia e l'altra.
In questi casi è possibile anche generare artificialmente delle anomalie, con l'aiuto di un esperto del dominio.

### Data Labeling (Etichettamento)
Nella realtà non si raccolgono anche le etichette insieme ai dati.
C'è bisogno quindi di un esperto che effettui il data labeling per tutti i dati, sia nei task di classificazione che in quelli di regressione.

È un'operazione delicata, che richiede una approfondita conoscenza del settore per essere messa in atto.
Spesso, però, è effettuata in modo sbagliato da chi sviluppa l'algoritmo, anzichè da un esperto.

#### Etichettamento Manuale
Solitamente il data labeling è un'operazione manuale, e pertanto molto lenta e time consuming.

Per cercare di limitare l'impiego di tempo sono attuabili strategie di parallelizzazione, che dividono il carico tra più persone.
Tuttavia, rimane il problema che persone diverse potrebbero etichettare i dati in maniera diversa.

Inoltre, possono capitare errori di distrazione nel processo, essendo questo manuale.

Si cerca pertanto di applicare delle linee guida e di limitare al massimo la soggettività del processo.
Rimane però sempre da valutare le etichette assegnate.

#### Altre Tecniche di Data Labeling
Oltre all'etichettamento manuale, sono utilizzabili approcci.

Alcuni di questi sono basati sul machine learning:
- **Semi-supervised labeling**: sfruttamento di una piccola quantità di dati etichettati per allenare un modello che etichetti il resto dei dati.
- **Active learning**: sfruttamento di un modello che selezioni attivamente i dati da cui imparare (e quindi da etichettare) in modo interattivo.

Altri approcci sono basati su regole, e rientrano nella tecnica del **data programming**.
Si usano delle regole euristiche per l'etichettamento automatico dei dati, spesso basate sulla ricerca di parole chiave.
Tuttavia, possono sorgere problemi con le negazioni e dei commenti sarcastici.

Infine, si possono usare sorgenti esterne come verità, che attribuiscano il valore della label.
Una di queste sorgenti esterne può anche essere un Large Language Model. Si parla allora di **LLM as a judge**.
C'è comunque da tenere in considerazione che anche gli LLM possono commettere errori, e quindi potrebbero essere necessarie multiple
interrogazioni.

### Data Preparation
È l'insieme delle operazioni che vengono effettuate per rendere i dati adatti all'allenamento di un modello di machine learning.
È necessaria perchè i dati spesso possono essere sporchi o contenere valori nulli o duplicati.

Fa parte della data preparation:
- Trovare una giusta granularità dei sample
- Eliminare eventuali dati errati
- Trattare i dati nulli
- Gestire l'apporto che le feature danno al modello

È necessario procedere per tentativi, perchè non è detto che le tecniche usate siano le migliori per il modello.

#### Data Cleaning
È il processo che si occupa di eliminazione di dati errati e trattamento dei valori nulli.
Tramite la data cleaning si deve eliminare gli errori del dataset, cercando di non introdurne di nuovi (causati da un'errata pulizia).

#### Feature Extraction
Consiste nell'estrazione e nel mantenimento solamente delle feature veramente utili al modello e al task.

A volte si conosce il fenomeno da rappresentare e il processo è semplice.
Altre volte, invece, si può procedere per tentativi o usare un'accurata analisi dei dati.

Nel deep learning la feature extraction non è molto importante, poichè i modelli comprendono già autonomamente quali feature siano importanti
e quali no. Il deep learning, pertanto, comprende anche una parte di **representation learning**.

---

#### feature transformation
standardizzazione, normalizzazione ... (preprocessing)

### Data Reduction
Serve a ridurre la dimensione del dataset, sia per quanto riguarda il numero di colonne che per quanto riguarda il numero di righe.
feature reduction e sample reduction

se una colonna contiene valori costanti allora non porta informazione al modello.
si elimina la colonna quindi

si possono usare tecniche statistiche o che si basano sull'esperimento.

Si possono usare tecniche di dimensionality reduction, come la PCA, LDA e autoencoders.

note
autoencoders (registrazione, slide e internet)

Tuttavia, si perde l'informazione originale: le feature non rappresentano più il fenomeno originale. Si perde della conoscenza.
Non si sa più come mai si ha una certa predizione. Non si sa quali sono i dati che portano ad una certa predizione.

Alcune volte la spiegazione è importante, quindi non si possono usare tecniche di dimensionality reduction.

Si può voler ridurre anche il numero di sample.
Questo è importante per eliminare le ripetizioni ad esempio, o per non rappresentare sempre lo stesso caso (non anomalia ad esempio).

Non sempre il dataset rappresenta la realtà.
Alcune volte il dataset rappresenta i dati che sono più facilmente collezionabili.
Va fatto in modo che il dataset rappresenti il contesto di applicazione del modello.

## Data Augmentation
Serve ad aumentare le righe creando variazioni dei dati.
Questo potrebbe essere utile per aumentare la rappresentazione di classi sotto-rappresentate.

Si può dover bilanciare un dataset sbilanciato.

## Inferenza
Vanno sviluppati dei metodi per il testing del modello.

I dati devono essere tali da poter valutare il modello nel modo corretto e nel task considerato.
Il dataset di testing può non rappresentare una categoria di dati, e questo è un problema.

### In-Distribution Evaluation
Valuto come si comporta il modello con il test set in ogni caso della distribuzione (dati su maschi o femmine o su modena o su un'altra città).
Va verificato ogni caso e ogni dettaglio.

slide 29

Si può fare con data slicing: vedere come il modello si comporta in sotto-popolazioni del dataset.
Serve una conoscenza del dominio per trovare la sotto-popolazione su cui testare il modello.

Si possono usare approcci controfattuali: variazione dei parametri in input per capire i margini della predizione del modello (quando il modello
cambia decisione).
Si discutono poi i risultati con un esperto per vedere se il comportamento del modello coincide con la realtà.

### Out-Of-Distribution
Va capito come il modello è in grado di generalizzare.
Alcuni casi particolari potrebbero mettere il modello in difficoltà ad esempio.

Si vuole verificare come si comporta il modello in scenari inattesi o non previsti.

si può fare con una adversarial (approccio)
Variare i dati come controfattuale ma per generare esempi che il modello non conosce.

distribution shift evaluation
testing su distribuzione diversa da quella di allenamento del modello

### Prompt Engineering
Si vogliono costruire dei prompt per valutare il modello.
Si devono progettare delle interrogazioni che valutino il modello in tutti i casi.

## Data Maintenance
slide 35 tipo di operazioni

è importante anche la performance temporale, oltre a quelle sulla qualità delle previsioni.

data understanding
vanno capiti i dati per capire quali rappresentano al meglio il fenomeno.
data visualization, summary, ...
tecniche che cercano di spiegare i modelli

due cose:
- visualizzare i dati aggregati per capire cosa si sta rappresentando (grafici e tecniche visuali)
- data valuation

data valuation
capire l'importanza di ogni singolo componente del dataset

data quality assurance
tecniche che permettono di capire se i dati raccolti sono importanti alle predizioni future.
non serve raccogliere continuamente dati relativi sempre allo stesso fenomeno.

non tutti i dati ha senso aggiornarli, perchè non cambiano.