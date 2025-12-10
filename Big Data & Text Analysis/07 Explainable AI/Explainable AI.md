---
tags:
  - big_data
  - ai
  - explainable_ai
---


%% 2025/11/17 %%

Con *interpretabilità* si intende il grado con cui un umano può capire la causa di una decisione e predire il risultato di un modello.
Quanto più è alta l'interpretabilità, più risulta facile capire perché il modello ha dato un certo risultato (*explainability*)

L'interpretabilità è importante per garantire determinati comportamenti e prevenire

- Giustezza del modello, assicurando che le predizioni siano unbiased e che il modello non discrimini contro gruppi sotto-rappresentati
- Privacy, assicurando che informazioni sensibili non vengano fornite in output
- ...

L'interpretabilità può essere di 2 tipi:
- Intrinseca, proprietà del modello stesso quando esso è facilmente spiegabile. Questi modelli sono:
	- [[xAI - Decision Tree|Decision Tree]]
	- [[xAI - Regressione Lineare|Sistemi Lineari]]
	- [[xAI - Logistic Regression|Logistic regression]] (sempre un sistema lineare, per quanto messo in una sigmoide)
- [[Explainable AI  - Modelli Post-Hoc|Post hoc]], data dall'allenamento di un modello lineare surrogato che simula quello più complesso per renderlo spiegabile

Proprietà delle spiegazioni:
- Accuratezza: quanto bene la spiegazione predice dati non visti
- Fedeltà: quanto le predizioni coincidono
- Consistenza / Stabilità: come al variare dei parametri le spiegazioni rimangono uguali o cambiano
- Comprensibilità: quanto la spiegazione è facilmente comprensibile dall'uomo
- Grado di importanza
- Rappresentatività

Un modello di spiegazione può produrre dei dati, o delle istanze che spiegano quei dati. In questo caso si chiama *modello contra-fattuale* (un esempio di questo è un modello che dica "con queste condizioni ho questo output, ma cambiando questo singolo valore ne fornisco un altro")

L'interpretazione può essere 
- [[Explainable AI - Metodi Locali Model-Agnostic|Locale]] (spiega solo una caratteristica)
- [[Explainable AI - Metodi Globali Model-Agnostic|Globale]] (spiega l'intero modello)
	- spiega la correlazione tra le features
