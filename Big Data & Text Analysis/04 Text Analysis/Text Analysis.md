%% 2025/10/15 %%

Data una collezione di documenti il compito principale della Text Analysis è trovare una serie di parole chiave che permettano di collegare la query di un utente al documento che necessita

Ci sono principalmente 2 tecniche per eseguire analisi del testo:
- Pull
	- L'utente prende l'iniziativa per trovare informazioni
	- È la tecnica usata dai *search engine*
- Push
	- Il sistema prende l'iniziativa per consigliare informazioni rilevanti all'utente
	- È la tecnica usata dai *recommendation systems*

Dato un vocabolario $V = { w_1, \dots, w_N }$:
  - Una query $q = q_1, q_2, \dots, q_m$ è una sequenza do parole, dove $q_i \in V$
  - Un documento $d = d_{i,1}, d_{i,2}, \dots, d_{i,s}$ è una sequenza di parole, dove $d_{i,j} \in V$

Noi vogliamo trovare $R(q) \subset C$ che sono rilevanti per la query $q$ dell'utente.

La stessa query, data da una persona diversa, può fornire un $R(q)$ diverso, che varia in base da chi ha fatto la query e da chi l'ha eseguita. Di conseguenza, il meglio che si può fare a computer è trovare un risultato $R'(q)$ che sia un'approssimazione di $R(q)$

Per risolvere questo problema abbiamo 2 tecniche:
- Document selection: tecnica che, data una query, restituisce 1 se un documento è rilevante per una query, 0 altrimenti
	- $f(q,d) = [0, 1]$
	- Questa tecnica è una possibilità che si può fare ma che non viene normalmente fatta
- Document ranking: tecnica che associa a ogni documento un numero reale tra 0 e 1 e propone solamente i documenti che superano un determinato valore di *cutoff*
	- $f(q,d) \in \mathbb{R}$
	- Questa è la tecnica che viene solitamente utilizzata

Storicamente i sistemi di text retrieval si possono classificare in 2 modi:
- Basati sulla similarità: un documento è tanto più rilevante quanto più il documento e la query sono simili
	- Funzione di similarità piuttosto complessa in quanto una query sarà di poche parole, mentre un documento ne contiene molte di più
- Basati sulla probabilità: considera i documenti e le query come simili basandosi sulla probabilità che una variabile randomica R sia più vicina a 0 o a 1
	- Funzione basata su language models

Entrambe le tecniche considerano il documento come una bag of words

Una forma comune di retrieval function è elencare quante occorrenze di ogni parola ci sono

Altra forma di retrieval function è la Document Frequency, una funzione basata sul calcolo della frequenza con cui ogni parola compare rispetto alla dimensione del documento, che va dunque a dare maggiore importanza a parole che compaiono meno volte perché discriminano di più. Le parole con frequenza più alta che vengono ignorate vengono chiamate stop-word (parole che non vengono nemmeno indicizzate perché poco importanti). Queste tecniche vengono chiamate *TFIDF* (Term Frequency - Inverse Document Frequency)

## Vector space models

Il *Vector Space (VS) model* è un modello di text retrieval basato sulla rappresentazione di ogni documento e ogni query come se fosse all'interno di uno spazio vettoriale.

Se io rappresento i documenti come vettori e una query come un singolo vettore, a questo punto la rilevanza sarà data da quanto il vettore della query è vicina al vettore di un documento specifico.

Come convertire un documento in un vettore?
- L'idea è quella di prendere tutte le parole di un vocabolario, e costruire uno spazio vettoriale n-dimensionale dove n è il numero di parole del dizionario, con ogni parola associata a un determinato asse dello spazio.

Per capire la similarità tra query e documento quello che si può guardare è la similarità del coseno, comparando il coseno della query rispetto al vettore del documento.

Come rappresentare un documento in uno spazio vettoriale?

Caso più semplice: spazio booleano. Se una parola compare, metto il vettore a 1, altrimenti metto un vettore con modulo 0

$$
\text{Sim}(q, d) = q d = x_1 y_1, ..., x_N y_N = \sum_{i=1}^N x_i y_i
$$

Miglioramento del VSM: aggiungere una conta della frequenza delle parole tramite TF (Term Frequency).

Altro miglioramento: conta della frequenza tramite TF-IDF.

DF = Numero di documenti che contengono quella parola
IDF = Inverso del numero di documenti che contengono la parola = $\frac{M + 1}{\text{df}(w)}$

$$
f(q, D_1) = \text{TF} * \text{DF} = \text{TF} * \text{IDF}
$$

## Normalizzazioni

### TF Transformation

Se invece di usare la TF usiamo il logaritmo della TF ($y = \log(1 + x)$) andiamo a calmierare il numero di occorrenze, andando a ridurre il problema per il quale una parola ripetuta spesso guadagna molta importanza

### BM25 Transformation

$$
y = \frac{(k+1) x}{x + k}
$$
### Document Length Normalization

#### Pivoted Length Normalization

$$
\text{normalizer} = 1 - b + b \frac{|d|}{\text{av dl}}
$$
