---
tags:
  - big_data
  - ai
  - explainable_ai
  - decision_tree
  - intrinsic_models
  - machine_learning
---
La spiegazione del decision tree è piuttosto facile, in quanto l'algoritmo del modello si limita a seguire un certo percorso in base all'input, e basta di conseguenza analizzare il percorso scelto per spiegare la decisione.
$$
\hat{y} = \hat{f}(x) = \sum_{m=1}^M c_{m} I \{x \in \mathbb{R}_{m}\}
$$
Per determinare l'importanza si attraversano tutti i nodi attraversati nel processo di decisione, e si misura quanto ognuno di essi abbia diminuito la varianza o l'indice Gini rispetto al precedente, scalando tutti i valori delle importanze a 100.