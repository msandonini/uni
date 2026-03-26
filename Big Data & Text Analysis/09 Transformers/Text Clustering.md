---
course: Big Data and Text Analysis
---
Il clustering del testo ha come obiettivo il raggruppamento di testi simili basato sul loro contenuto semantico, significato, e relazioni.
Per eseguire clustering esistono diversi metodi:
- [[#T-SNE]]
- [[#UMAP]]
- [[HDBSCAN]]
- [[#c-TF-IDF]], una versione modificata di [[Text Analysis#TF Transformation|TF-IDF]]

## T-SNE

## UMAP

[[UMAP]] più o meno fa la stessa cosa del [[#T-SNE]].
Dato in input un punto si specifica quanti punti vicini trovare (cioè si specifica un valore per definire il suo [[KNN Classifier]]).
A questo punto non usa una gaussiana ma usa una funzione esponenziale per definire la distanza, così da avere un decadimento più rapido dei testi più lontani.

## Clustering

Una volta che si è eseguita una dimensionality reduction, ottenendo dunque degli embedding in uno spazio compresso, si esegue il clustering, che può essere basato su diverse tecniche:
- 
- Density-based

## c-TF-IDF

Una tecnica TF-IDF basata sulle classi che si occupa di riconoscere parole chiave così da associarle ad ogni cluster andando a ridurre il peso su parole che appaiono più spesso in tutti i cluster.
Per incrementare le performance di questa tecnica si può aggiungere un re-ranker basato su modelli generativi così da ri-classificare le parole chiave dopo una prima classificazione (così da tenere conto non delle singole parole ma del significato delle stesse).
