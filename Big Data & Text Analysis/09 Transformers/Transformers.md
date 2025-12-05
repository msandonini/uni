---
tags:
  - deep_learning
  - transformers
  - big_data
---
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

$$
\begin{align}
&Q = XW^{Q} \\
&K = XW^{K} \\
&V = XW^{V} \\

&A = \text{SelfAttention}(Q, V, K)  = \text{softmax}\left( \frac{QK^{T}}{\sqrt{ d_{k} }} \right) V
\end{align}
$$

Un singolo blocco di un transformer non può imparare a catturare tutti i tipi di relazioni tra gli input. Per risolvere questo problema si usa il meccanismo di [[Multi-head attention]]
Il sistema basato sul meccanismo di [[Multi-head attention]] si chiama così perché usa $n$ attention heads diverse.

Usando il Multi-head attention block ci si è resi conto che si perdevano molte informazioni riguardanti le informazioni iniziali, quindi si è aggiunta una [[connessione residua]], ovvero l'informazione iniziale viene passata al nodo successivo insieme al multi-head

![[Transformer_multi_head_residual_connection.png]]

$$
\begin{align}
&z = \text{LayerNorm}(x + \text{SelfAttention}) \\
&y = \text{LayerNorm}(z + \text{FFN}(z))
\end{align}
$$
Ogni componente della computazione si può dividere come segue:
$$
\begin{align}
T^{1} &= \text{SelfAttention}(X) \\
T^{2} &= X + T^{1}
\end{align}
$$
Ogni $X_i$ è formato da un embedding contenente il token e la posizione.

Abbiamo 2 tecniche per inserire la posizione:
- Posizione assoluta
	- Sommo per ogni word embedding il suo position embedding, che si riferisce alla posizione della parola in tutta la frase
	- Questa posizione non viene mai usata perché ci sono meno esempi per position embeddings più grandi che per position embeddings più piccoli (non tutte le frasi sono grandi uguali, ed è più facile avere frasi corte che frasi lunghe)
- Posizione relativa
	- Mappo l'embedding nello spazio ottenendo la posizione di un embedding rispetto ad un altro (calcolo quindi la distanza tra gli embedding)

Per modellare le frasi usiamo una head chiamata [[Language modeling head]]

## LLMs

Gli LLM sono utili per task di riassunto e sentiment analysis.

### Sampling

Come generare una frase in un LLM?
Quello che devo fare è scegliere la parola più probabile nel vocabolario usando una argmax. 


Questa cosa funziona male, in quanto produce testo generico o ripetitivo, andando a perdere la diversità che caratterizza un linguaggio.
Per risolvere questo problema posso usare una tecnica di sampling contenente tutte le parole più probabili ([[top-k sampling]]).
Top-k funziona, ma ci sono tecniche migliori, come il [[top-p sampling]].

#### Temperature sampling

Viene impostato un valore di temperatura che può avere 2 valori:
- Temperatura alta
	- Flessibile, esplora più opzioni
- Temperatura bassa
	- Più concentrata, preferisce valori a probabilità più alta
In questo caso la logica del modello funziona tramite una softmax usando il valore di temperatura come divisore delle probabilità:
$$
y = \text{softmax}\left( \frac{u}{t} \right)
$$
- $t \approx 1$: la distribuzione rimane invariata
- $t < 1$: aumenta la probabilità di scegliere parole con alta probabilità
- $t \to 0$: la probabilità che venga scelta la parola con probabilità più alta tende ad 1
- $t > 1$: si appiattisce la distribuzione, quindi aumenta la diversità nel sampling

### Pre-Training

Per fare il training di un LLM, viene usata una tecnica chiamata [[teacher forcing]].

## BERT

BERT è uno dei possibili encoder usati per ottenere i token nei vari LLMs, associando alla parola il contesto della frase (ormai non viene più usato perché vecchio).
BERT funziona con un vocabolario di ingresso da 30'000 token ottenuti con WordPiece (se una parola non è nel vocabolario cerca di spezzarla in parole presenti nel vocabolario).
È trainato solo per la lingua inglese, con alcune variazioni a seconda delle lingue (ad esempio XLM-RoBERTa per il multilingual)

BERT viene allenato con 2 tecniche:
- [[MLM (Masked Language Model)]]
	- Viene selezionato il 15% delle parole:
		- L'80% lo sostituiamo con un token maschera da prevedere
		- Il 10% viene sostituito randomicamente
		- Il 10% viene lasciato com'è
- MSP
	- Vengono codificate le frasi con 2 token particolari
		- \[CLS]
		- \[SEP]
Tutti gli embedding soffrono di anisotropia, ovvero tutti gli embedding sono vicini nello spazio vettoriale, e per risolvere vanno normalizzati.
Un altro problema che noi abbiamo è che molto spesso questi embedding sottostimano il giudizio umano per quanto riguarda la similarità di parole simili (ad esempio le parole "cosa" e "oggetto", che per un umano possono essere molto simili, dal modello possono essere viste come molto diverse).

