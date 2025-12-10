---
tags:
  - big_data
  - ai
  - explainable_ai
  - local_methods
---
Una variazione del [[Centeris Paribus (CP)|CP]] è l'[[Individual Conditional Expectation (ICE)]].
Questo metodo funziona circa come il CP, ma invece di concentrarsi sul singolo data point si concentra sull'intero dataset:
![[Plot_Individual_Conditional_Expectation.png]]

Il problema dell'ICE è che queste variazioni riguardano punti di partenza diversi, e presentano dunque degli offsets. Questo problema rende difficile capire la forma delle curve tra istanze diverse

Questo problema trova soluzione nell'uso dei *c-ICE* (Centered ICE), che rimuovono gli offset ancorando tutte le curve ad un punto di riferimento comune:
![[Centered_ICE.png]]

Una possibile evoluzione di questo metodo, che è un metodo globale, è il [[Partial Dependency Plot (PDP)]], nel quale per ogni valore dell'asse orizzontale viene calcolata la media, ottenendo dunque una curva che mostra la varianza