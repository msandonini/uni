---
tags:
  - graph_analytics
---
Per calcolare il Clustering Coefficient si possono usare 2 formule distinte, a seconda se il grafo sia diretto o indiretto:
- Diretto: $C_{n} = \frac{\text{\# edges between the neighobrs of } n}{\deg(n) * (\deg(n) - 1)}$
- Indiretto: $C_{n} = \frac{2 * (\text{\# edges between the neighbors of n})}{\deg(n) * (\deg(n) - 1)}$

Il clustering coefficient dell'intero grafo si calcola come $C = \frac{1}{|N|} \sum_{n \in N} C_{n}$

Per indicare quanto fortemente è collegato un grafo si utilizza anche il **Wiener Index**:
$$
\sum_{(u, v) \in G} d(u, v)
$$
Dove $d(u, v)$ è la distanza del shortest-path.

### Misure di centralità

Le misure di centralità sono una metrica che ci indica l'importanza di un singolo nodo all'interno di una rete (quanto è rilevante).
L'importanza di un nodo dipende dal suo ruolo nel tenere il grafo connesso.
Ci sono diverse misure di centralità:
- Degree centrality: numero di nodi vicini
- Closeness centrality: reciproco della distanza totale tra un nodo e tutti gli altri nodi nella rete
	- Si calcola con la formula $C_{c}(v) = \frac{1}{\sum_{u \in V} \delta(u, v)}$
		- $\delta(u, v)$ rappresenta la distanza tra un nodo $u$ e il nodo $v$ in esame
- Betweeness centrality:
	- Si calcola con la formula $C_{B}(v) = \sum_{s\neq t\neq v \in V} \frac{\sigma_{st}(v)}{\sigma_{st}}$
		- $\sigma_{st}$ è il numero di shortest paths tra il nodo $s$ e il nodo $t$
		- $\sigma_{st}(v)$ è il numero di shortest paths tra tutte le coppie di nodi di una rete passanti da un nodo $v$
	- In alternativa, se si vuole un risultato nell'intervallo \[0-1\], si può usare la formula normalizzata $C_{B}(v) = \frac{1}{N_{\text{pairs}}} \sum_{s\neq t\neq v \in V} \frac{\sigma_{st}(v)}{\sigma_{st}}$

Esempio:
![[Pasted image 20260304104742.png]]
In questo caso abbiamo:
- Grado di $n$: 2
- Grado medio: 2
- Closeness $C_{c}(n)$: $\frac{1}{1+1+2} = 0.25$
- Shortest paths tra tutte le coppie:
	- $(1, 2) \to (1, n, 2), (1, 3, 2) \to \frac{1 (\text{che passa per } n)}{2 (\text{totali})}$
	- $(1, 3) \to (1, 3) \to \frac{0}{1}$
	- $(2, 3) \to (2, 3) \to \frac{0}{1}$
- Betweenness centrality $C_{B}(n)$: $\frac{1}{2} = 0.5$

### Generalizzazione a N parti

Dato $k$, vogliamo trovare una partizione $(S_{1}, S_{2}, \dots, S_{k})$ che minimizzi una misura di taglio.

- **K-way conductance**
	- $\phi_{k}(S_{1}, S_{2}, \dots, S_{k}) = \frac{1}{k} \sum_{i = 1}^{k} \frac{\text{cut}(S_{i}, \bar{S}_{i})}{\text{vol}(S_{i})}$
- **Normalized cut (Ncut) for $k$ parts**
	- $\text{Ncut}_{k} = \sum_{i = 1}^{k} \frac{\text{cut}(S_{i}, \bar{S}_{i})}{\text{vol}(S_{i})}$

Questa operazione è utile per eseguire operazioni di **Community detection**, definendo come **community** una porzione di grafo con alta connettività interna (queste porzioni sono chiamate anche moduli o clusters).

Algoritmi classici per il partizionamento:

| Algoritmo     | Meccanismo                                    | Scalabilità | Punti di forza                                              | Debolezze                                                        |
| ------------- | --------------------------------------------- | ----------- | ----------------------------------------------------------- | ---------------------------------------------------------------- |
| Louvain       | Ottimizza la modularità spostando i nodi      | Alta        | Molto veloce, buono per reti dense                          | Produce comunità separate, potrebbe perdersi le comunità piccole |
| Girvan-Newman | Rimuove gli archi con la più alta betweenness | Bassa       | Buono per reti piccole                                      | Molto lento su grafi di grandi dimensioni                        |
| InfoMap       | Minimizza la lunghezza delle random walks     | Medio-alta  | Cattura bene strutture complesse, lavora bene su varie reti | Meno intuitivo                                                   |

Algoritmi per comunità sovrapposte:

| Algoritmo                       | Meccanismo                                    | Scalabilità | Punti di forza                                               | Debolezze                                            |
| ------------------------------- | --------------------------------------------- | ----------- | ------------------------------------------------------------ | ---------------------------------------------------- |
| Clique Percolation (CPM)        | Usa k-cliques adiacenti per le communities    | Medio-bassa | Interpretazione teorica della sovrapposizione chiara         | Sensibile al parametro $k$, costoso su reti dense    |
| Label Propagation (COPRA, SLPA) | Le labels vengono diffuse ai vicini           | Molto alta  | Tempo simil-lineare, scala su grafi molto grandi             | COPRA sensibile alla threshold per di appartenenza   |
| Local Expansion (LFM)           | Espande da dei nodi-seme                      | Media       | Buona qualità, scopre le sovrapposizioni in maniera naturale | Dipende dai semi iniziali scelti                     |
| Fuzzy C-Means on Graphs         | Esegue soft-assignment usando dei nodi leader | Media       | Appartenenza alle communities "realistica", parallelizzabile | Necessita di misure di centralità e parameter tuning |
