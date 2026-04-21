---
course: Graph Analytics
---

Un sistema di raccomandazione è un sistema che genera consigli specifici per determinati utenti in base ai loro interessi.

Alla base di un recommendation system si trova solitamente una **matrice di raccomandazione**, una matrice contenente i punteggi di ogni item per ogni utente.

Nella raccomandazione per similarità, solitamente il punteggio di un item si ottiene tramite la cosine similarity tra i 2 vettori degli items, così da definire quali items sono simili tra loro:
$$
\text{sim} (\vec{a}, \vec{b}) = \cos(\vec{a}, \vec{b}) = \frac{\vec{a}\cdot\vec{b}}{|\vec{a}| \times |\vec{b}|}
$$
Siccome la similarità è simmetrica il calcolo si può ridurre della metà.

La rappresentazione della similarity matrix si può eseguire tramite l'utilizzo di un grafo bipartito.
In un dataset User-Item la probabilità di ortogonalità è piuttosto alta, quindi il numero di calcoli inutili è a sua volta piuttosto alto. Usando una rappresentazione a grafo è semplice trovare tutti gli items che hanno almeno uno user in comune, quindi la similarità si può calcolare tra solo l'item corrente e quelli che si sovrappongono, riducendo dunque il numero di calcoli

Una rete Bayesiana è un grafo diretto in cui ogni nodo è annotato con informazioni probabilistiche quantitative (come ad esempio "50%", "0.5", ecc...)
Una rete Bayesiana rappresenta un mix tra teoria della probabilità e teoria dei grafi, in cui le dipendenze tra variabili sono espresse graficamente.

Definiamo dinamica una rete bayesiana che mette in relazione delle variabili in time steps adiacenti.

La versione più semplice di una DBN (Dynamic Bayesian Network) che può essere usata per predire una posizione è una [catena di Markov](https://en.wikipedia.org/wiki/Markov_chain).

Il modello di previsione può cambiare a seconda del contesto (es. a seconda dell'ora a cui controllo). In questo caso, si può usare un modello esteso basato su una catena di Markov contestuale (CMC - Contextual Markov Chain), nella quale la probabilità che il soggetto sia in un determinato luogo dipende anche dal tempo specificato.
![[Pasted image 20260421125534.png]]
