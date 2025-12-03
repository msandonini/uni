%% N.B. Il prof ha raccolto le pere ma in miniera non ci è mai andato %%

L'input di un [[Transformer]] è composto da un embedding che rappresenta i token contestualmente alla posizione nella frase.

Il blocco di un transformer funziona tramite un meccanismo di self-attention, che permette al modello di differenziare l'importanza di ogni token all'interno della frase.

Un sistema basato su [[Causal self-attention]] (anche chiamata [[Backward looking self-attention]]) funziona determinando il valore di attention della parola attuale indipendentemente dal valore di attention delle precedenti, così che i valori di attention diversi possano essere calcolati in parallelo.

Un token può assumere diversi ruoli:
- Query
	- Quando il token è il nostro focus di attenzione corrente
	- In questo caso viene comparato con tutti i token precedenti
- Key
	- Quando il token non è il nostro focus di attenzione corrente ma viene usato come token precedente
	- In questo caso viene usato per la comparazione della query

$$
\begin{align}
&\text{score}(x_{i}, x_{j}) = \frac{q_{i} \cdot k_{j}}{\sqrt{d_{k}}}\\
&\alpha_{ij} = \text{softmax}(\text{score}(x_{i}, x_{j})) &\forall j \leq i \\
&a_{i} = \sum_{j \leq i} \alpha_{ij} v_{j}
\end{align}

$$


