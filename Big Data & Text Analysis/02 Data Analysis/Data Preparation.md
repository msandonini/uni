---
tags:
  - big_data
  - data_preparation
  - discretization
---
%% 2025/10/01 %%

Per la preparazione dei dati esistono 2 principale tecniche:
- Tecniche *scheme-dependent*
	- Usati per dataset con poche colonne
	- Basate sull'analisi dei singoli attributi e dei raggruppamenti tra essi per selezionare quelli con la migliore accuratezza
- Tecniche *scheme-independent*
	- Basate sull'analisi delle caratteristiche generali dei dati e su quanto il dataset sia correlato ai risultati di training

In `sklearn` è possibile applicare la feature selection tramite la classe `SequentialFeatureSelection`, che testa tutte le opzioni sequenzialmente specificando la direzione da seguire (`forward` o `backward`)

## Attribute discretization

Ci sono 2 tecniche:
- *Equal frequency building*, basata sull'utilizzo dei quantili per dividere in gruppi di dimensioni simili
- Raggruppamento uniforme, basata sulla divisione in gruppi per dati simili (es. fasce d'età)

In `sklearn`, la classe che permette di discretizzare è `KBinsDiscretizer`

### Proiezioni

Le proiezioni sono semplici trasformazioni (es. aggiunta di rumore) eseguite per migliorare le prestazioni del modello (ridurre overfitting, ...)

### Sampling

Con sampling si intendono 2 principali tecniche
- Riduzione del numero di righe per l'analisi
- Duplicazione di righe per aumentare il numero di dati in dataset piccoli

### Cleansing
Il processo di cleansing è quello che si occupa di gestire i valori mancanti, le anomalie, ed eventuali outliers

---

# Overfitting

Tutti gli algoritmi di machine learning, in particolare quelli più complessi, hanno il problema dell'overfitting (in quanto basati sul dataset di training)

## Overfitting linear function

Algoritmi diversi saranno più o meno proni ad overfittare; ad esempio, una logistic regression sarà molto più prona all'overfitting rispetto ad una SVM.
Una funzione lineare può essere resa più complessa considerando il cubo o il quadrato del dataset di partenza (o comunque una sua trasformazione), ed applicandola poi a quest'ultimo.

## Learning curves

Modelli diversi avranno curve di apprendimento diverse.
Solitamente un modello di ML è più prono a saturazione rispetto ad uno di DL.
La scelta del modello da utilizzare va quindi eseguita in base alla dimensione del dataset comparata con le curve di apprendimento del modello in analisi.

## Training & Testing

Nella scelta di Training e Testing sets non basta scegliere casualmente ma, dopo lo shuffling del dataset, bisogna accertarsi che i dati siano effettivamente randomizzati, così da non avere dei dati di tipo diverso in training e testing (ad esempio, la scelta di set random potrebbe inserire quasi tutti i sample con il campo *"sesso"* assegnato a *"M"* in training e quelli assegnati ad *"F"* in testing).

**N.B.**: è importante dividere il dataset in 3 parti:
- Training
- Validation
- Testing
In questo modo non si overfittano i parametri della validazione sui dati di test.

Altro metodo per validare è l'utilizzo di una *$K$-Fold cross validation*, una tecnica che divide il dataset in $K$ gruppi, e per ognuno di questi $K$ gruppi avviene un training sugli altri dati, utilizzando come test il gruppo corrente, salvando per ogni ciclo il valore di accuracy.
Una volta calcolata l'accuratezza per ogni fold, si controllano media, mediana, e distribuzione, così da controllare che i dati siano ben distribuiti.
Il $K$-Fold, solitamente, è più stabile rispetto alla divisione in 3.