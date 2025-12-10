---
tags:
  - big_data
  - ai
  - explainable_ai
  - local_methods
---



















### Local Interpretable Model-Agnostic Explanations (LIME)

I modelli surrogati locali sono modelli interpretabili usati per spiegare predizioni individuali di modelli di machine learning black box.

L'idea di questo metodo è quella di costruire un modello lineare guardando gli intorni di un singolo punto, così da identificare l'andamento del modello nell'intorno del punto selezionato.
Per fare ciò LIME genera un nuovo dataset contenente esempi perturbati e le relative predizioni fatte dal modello black box. Una volta generato il dataset LIME si occupa di allenare un modello interpretabile dove ogni sample è pesato in base alla prossimità all'istanza di interesse (più un sample è lontano da quello in analisi, meno esso influenzerà il modello di interpretazione).

L'accuratezza di questo modello si chiama *local fidelity*, in quanto non rappresenta l'intero modello ma solo un locale dello stesso.

$$
\text{explanation}(x) = \arg \min_{g \in G} L(f, g, \pi_{x}) + \Omega(g)
$$
Questo errore è ottimizzato minimizzando la loss e tenendo conto della prossimità $\pi_{x}$ (che indica quanto è largo il neighborhood attorno all'istanza $x$). Il valore $\Omega(g)$ indica la complessità del modello, ed è preferibile tenerlo più basso possibile.

La maniera in cui LIME genera le variazioni sui dati dipende dal tipo di dato analizzato:
- Testi ed immagini vengono perturbati accendendo o spegnendo componenti individuali
	- Testi: vengono incluse o escluse parole
	- Immagini: vengono attivati o mascherati super-pixel (gruppi di pixel vicini)
- Dati tabulari vengono perturbati andando a perturbare singolarmente ogni feature. Le nuove features sono ottenute dalla distribuzione con valore medio e deviazione standard delle features originali, partendo dai samples attorno al centro dei dati di training, e non attorno all'istanza di interesse:
![[LIME_Tabular_Data.png]]

Per definire il neighborhood LIME usa un *exponential smoothing kernel*, così da definire la prossimità.
- $\pi_{x}=\exp\left( -\frac{D(x, z)^{2}}{\sigma^{2}} \right)$ viene definito sulla distanza $D$
- La dimensione del kernel $\sigma$ controlla quanto i punti più lontani possono influenzare il modello locale:
	- Dimensione piccola: influenzano solo i punti più vicini
	- Dimensione più grande: influenzano anche i punti più lontani
Il problema in questo caso è che i risultati possono cambiare drammaticamente in base alla dimensione del kernel:
![[LIME_Kernel_Size.png]]

### Spiegazioni Contrafattuali Locali

Una spiegazione contrafattuale descrive la situazione causale nella forma "Se $X$ non fosse accaduto, $Y$ non sarebbe accaduto".
Questo tipo di spiegazioni necessita di immaginare una realtà ipotetica che contraddice i fatti osservati, da cui il nome di modello "contrafattuale".


Le spiegazioni contrafattuali soffrono dell'[Effetto Rashomon](https://it.wikipedia.org/wiki/Effetto_Rashomon):
- Ogni spiegazione di un certo outcome può essere diversa dalla precedente
- Una spiegazione potrebbe dire di cambiare la feature A, mentre un'altra di lasciare A uguale e cambiare la feature B

Le spiegazioni contrafattuali possono essere ottimizzate tramite il metodo [[Wachter, Mittelstadt & Russel]]

#### Metodo Wachter, Mittelstadt & Russel (2018)

La proposta è di minimizzare la loss:
$$
L(x', xy') = (\hat{f}(x') - y')^{2} + \lambda \cdot d(x, x')
$$
- $\hat{f}(x')$: il modello predice per la contraffazione $x'$
- $y'$: il risultato atteso definito dall'utente
- $d(x, x')$: la distanza tra l'istanza originale $x$ e la contraffazione $x'$
- $\lambda$: parametro di bilanciamento tra similarità ed accuratezza
	- Un valore minore dà più peso al termine della predizione, mentre un valore maggiore dà più peso al termine della distanza

La distanza $d(x,x')$ viene calcolata tramite la [[distanza pesata di Manhattan]]:
$$
d(x, x') = \sum_{j} \frac{|x_{j} - x_{j}'|}{MAD_{j}}
$$
- $MAD_{j} = \text{median}(|x_{j}-\text{median}(x_{j})|)$
	- Il *MAD scaling* si assicura che tutte le features siano su una scala comparabile
- La distanza di Manhattan è più resistente agli outliers rispetto alla distanza euclidea

#### Shapley Values

Per spiegare la predizione assumiamo che ogni feature dell'istanza sia un "giocatore" in un gioco dove la predizione è il payout.
- Lo "Shapley Value", coniato da Shapley (1953) è un metodo per assegnare payouts ai vari giocatori in base al loro contributo al payout totale

Nel caso degli Shapley Values:
- Il "gioco" è la task di predizione per una singola istanza del dataset
- Il "guadagno" è la predizione effettiva meno la predizione media per tutte le istanze
- I "giocatori" sono i valori delle features dell'istanza che collaborano per ottenere il guadagno

Lo Shapley Value è il contributo marginale medio e pesato di una feature rispetto a tutte le possibili combinazioni (quanto avere un determinato valore in una feature influisce sulla predizione totale rispetto a tutti gli insiemi di elementi possibili).
Si dice che è pesato perché le varie combinazioni hanno tutte una importanza diversa tra loro.

Per simulare che una feature non esista faccio n predizioni prendendo un valore a caso della feature da eliminare, così che analizzando la combinazione con n valori diversi e facendo la media delle predizioni quella specifica feature perda di importanza.

Lo Shapley Value permette di ottenere una distribuzione "giusta", tuttavia dobbiamo definire formalmente cosa intendiamo con "distribuzione giusta".
Per poter dare la definizione bisogna innanzitutto definire la notazione:
- $N$ è l'insieme contenente i giocatori
- $S$ è un sottoinsieme di $N$ ($S \subseteq N$)
- $i$ è un elemento di $N$
- $v$ è la value function che mappa sottoinsiemi di giocatori $S$ a u numero reale
	- $v(S)$ è il guadagno della coalizione
- Quando un giocatore $i$ viene unito ad un insieme di giocatori $S$, il contributo marginale del giocatore $i$ a $S$ risulta $V(S \cup \{ i \}) - v(S)$

Basandosi su questa notazione, per definire il significato di distribuzione giusta sono state proposte 4 proprietà:
- Efficienza
$$
v(N) = \sum_{i \in N} \phi_{i} (N, v)
$$
- Simmetria
$$
\forall S \subseteq N \setminus \{i, j\}: v(S \cup \{j\}) \to \phi_{i} (N, v) = \phi_{j} (N, v)
$$
- Linearità
$$
\phi_{i} (N, v_{1}) + \phi_{i} (N, v_{2}) = \phi_{i} (N v_{1} + v_{2})
$$
- Dummy player
$$
\forall S \subseteq N \setminus \{i\}: v(S \cup \{j\}) = v(S) \to \phi_{i} (N, v) = 0
$$

Dati un set di giocatori $N$ e una value function $v$, lo Shapley Value del giocatore $i$ è data da:
$$
\phi_{i} (N, v) = \frac{1}{N!} \sum_{S \subseteq N \setminus \{i\}} |S|! ( |N| - |S| - 1 )! [v(S \cup \{i\}) - v(S)]
$$

##### SHAP

%% Non chiesta all'esame %%
