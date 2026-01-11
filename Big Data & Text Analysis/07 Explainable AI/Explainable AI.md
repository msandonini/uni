---
tags:
  - big_data
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
	- [[#Decision Tree]]
	- [[#Regressione lineare]]
	- [[#Logistic Regression]] (sempre un sistema lineare, per quanto messo in una sigmoide)
- [[Explainable AI  - Modelli Post-Hoc|Post hoc]], data dall'allenamento di un modello lineare surrogato che simula quello più complesso per renderlo spiegabile

Proprietà delle spiegazioni:
- Accuratezza: quanto bene la spiegazione predice dati non visti
- Fedeltà: quanto le predizioni coincidono
- Consistenza / Stabilità: come al variare dei parametri le spiegazioni rimangono uguali o cambiano
- Comprensibilità: quanto la spiegazione è facilmente comprensibile dall'uomo
- Grado di importanza
- Rappresentatività

Un modello di spiegazione può produrre dei dati, o delle istanze che spiegano quei dati. In questo caso si chiama *modello contra-fattuale* (un esempio di questo è un modello che dica "con queste condizioni ho questo output, ma cambiando questo singolo valore ne fornisco un altro")

L'interpretazione può essere:
- [[#Metodi Locali Model-Agnostic|Locale]] (spiega solo una caratteristica)
- [[#Metodi Globali Model-Agnostic|Globale]] (spiega l'intero modello)
	- spiega la correlazione tra le features


## Metodi intrinseci

### Decision Tree

La spiegazione del decision tree è piuttosto facile, in quanto l'algoritmo del modello si limita a seguire un certo percorso in base all'input, e basta di conseguenza analizzare il percorso scelto per spiegare la decisione.
$$
\hat{y} = \hat{f}(x) = \sum_{m=1}^M c_{m} I \{x \in \mathbb{R}_{m}\}
$$
Per determinare l'importanza si attraversano tutti i nodi attraversati nel processo di decisione, e si misura quanto ognuno di essi abbia diminuito la varianza o l'indice Gini rispetto al precedente, scalando tutti i valori delle importanze a 100.

### Regressione lineare

$$
y = \beta_{0} + \beta_{1}x_{1} + \dots + \beta_{p} x_{p} + \epsilon
$$
Un modello di regressione predice il target come una somma pesata delle feature di input

$\epsilon$ è l'errore, cioè la differenza tra [] e l'*encoding model*

Nella regressione lineare è semplice determinare l'errore perché è una semplice somma di pesi, e ha le seguenti proprietà:
- Linearità: fa si che la stima sia semplice e facilmente interpretabile
- Feature numeriche
- Feature binarie
- Feature categoriche: l'interpretazione dipende dal metodo di encoding
- Intercept ($\beta_{0}$): rappresenta l'outcome predetto quando tutte le features sono 0 e le features categoriche sono al livello di riferimento

$$
t_{\hat{\beta_{j}}} = \frac{\hat{\beta_{j}}}{\text{SE}(\hat{\beta_{j}})}
$$
$$
\text{SE}_{b_{i}} = \sqrt{ \sigma^{2} \cdot (X^T X)^{-1}_{ii} }
$$

Un effect plot mostra la combinazione di come la combinazione $\text{pesi} \times \text{feature value}$ influenzi le predizioni

$$
\text{effect}_{j}^{(i)} = w_{j} x_{j}^{(i)}
$$
Per le feature categoriche gli effetti possono essere riassunti in un singolo *boxplot*, mentre i plot dei pesi mostrano una riga per categoria

### Logistic Regression

L'interpretazione della [[0_Logistic Regression with Gradient Descent|Logistic Regression]] viene costruita in base al rapporto chiamato *odds*, ovvero la proprietà dell'evento divisa il suo opposto:
$$
\begin{align}

\ln\left( \frac{\mathbb{P}(Y = 1)}{1 - \mathbb{P}(Y=1)} \right) &= \ln\left( \frac{\mathbb{P}(Y=1)}{\mathbb{P}(Y=0)} \right) &= \beta_{0} + \beta_{1} x_{1} + \dots + \beta_{p} x_{p} \\
\frac{\mathbb{P}(Y = 1)}{1 - \mathbb{P}(Y=1)} &= \text{odds} &= \exp(\beta_{0} + \beta_{1} x_{1} + \dots + \beta_{p} x_{p}) \\
\frac{\text{odds}_{x_{j} + 1}}{\text{odds}_{x_{j}}} &= \frac{\exp(\beta_{0} + b_{1} x_{1} + \dots + \beta_{j} + (x_{j}+1) + \dots + \beta_{p} x_{p})}{\exp(\beta_{0} + \beta_{1} x_{1} + \dots + \beta_{j} x_{j} + \dots + \beta_{p} x_{p})} \\
\frac{\exp(a)}{\exp(b)} &= \exp(a - b) \\
\frac{\text{odds}_{x_{j} + 1}}{\text{odds}_{x_{j}}} &= \exp(\beta_{j}(x_{j} + 1) - \beta_{j} x_{j})

\end{align}
$$
In sostanza abbiamo una feature con la sua importanza. Aumentiamo la feature di un grado (aumentandone quindi la probabilità), e osserviamo la variazione nel suo peso, capendo dunque la sua importanza.


## Metodi Locali Model-Agnostic

- [[Centeris Paribus (CP)]]
- [[Individual Conditional Expectation (ICE)]]
- [[Local Surrogate Methods]]

### Centeris Paribus (CP)

I plot Centeris Paribus (CP) visualizzano come cambiando una singola feature cambia la predizione per uno specifico data point lasciando costanti tutte le altre features

Questo metodo funziona in maniera molto semplice:
- Si selezionano un data point da osservare e una feature di interesse
- Si cambia sistematicamente il valore della feature all'interno del suo range
- Si plotta la previsione del modello per ogni valore
- La curva risultante mostra quanto la predizione sia sensitiva al valore di quella specifica feature

Questo metodo ha 2 principali problemi:
- Le features vengono valutate una per volta, assume quindi che ogni feature sia scollegata da ogni altra
- Modificando i valori si vanno a creare combinazioni di valori che non rappresentano casi reali
Nonostante questi problemi il metodo funziona.
![[Plot_Centeris_Paribus.png]]
Nell'immagine viene mostrato un plot CP che mostra quanto le dimensioni del becco di un pinguino siano correlate al sesso dello stesso.

### Individual Conditional Expectation (ICE)

Una variazione del [[Centeris Paribus (CP)|CP]] è l'[[Individual Conditional Expectation (ICE)]].
Questo metodo funziona circa come il CP, ma invece di concentrarsi sul singolo data point si concentra sull'intero dataset:
![[Plot_Individual_Conditional_Expectation.png]]

Il problema dell'ICE è che queste variazioni riguardano punti di partenza diversi, e presentano dunque degli offsets. Questo problema rende difficile capire la forma delle curve tra istanze diverse

Questo problema trova soluzione nell'uso dei *c-ICE* (Centered ICE), che rimuovono gli offset ancorando tutte le curve ad un punto di riferimento comune:
![[Centered_ICE.png]]

Una possibile evoluzione di questo metodo, che è un metodo globale, è il [[Partial Dependency Plot (PDP)]], nel quale per ogni valore dell'asse orizzontale viene calcolata la media, ottenendo dunque una curva che mostra la varianza

### Local Surrogate Methods

#### Local Interpretable Model-Agnostic Explanations (LIME)

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

#### Spiegazioni Contrafattuali Locali

Una spiegazione contrafattuale descrive la situazione causale nella forma "Se $X$ non fosse accaduto, $Y$ non sarebbe accaduto".
Questo tipo di spiegazioni necessita di immaginare una realtà ipotetica che contraddice i fatti osservati, da cui il nome di modello "contrafattuale".


Le spiegazioni contrafattuali soffrono dell'[Effetto Rashomon](https://it.wikipedia.org/wiki/Effetto_Rashomon):
- Ogni spiegazione di un certo outcome può essere diversa dalla precedente
- Una spiegazione potrebbe dire di cambiare la feature A, mentre un'altra di lasciare A uguale e cambiare la feature B

Le spiegazioni contrafattuali possono essere ottimizzate tramite il metodo [[Wachter, Mittelstadt & Russel]]

##### Metodo Wachter, Mittelstadt & Russel (2018)

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

##### Shapley Values

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

###### SHAP

%% Non chiesta all'esame %%

## Metodi Globali Model-Agnostic

### PDP (Partial Dependency Plot)

Il Partial Dependency Plot (PDP / PD Plot) mostra l'effetto marginale che una o 2 features hanno sulla predizione restituita da un modello ML.

$$
\hat{f}_{S} x_{S} = \frac{1}{N} \sum_{i=1}^{n} \hat{f} (x_{S}, x_{C}^{(i)})
$$

### PFI (Permutation Feature Importance)

La PFI misura l'aumento nell'errore di predizione del modello dopo aver permutato i valori di determinate features (scambio, sulla stessa colonna, il valore di righe a caso).
Questo errore non viene calcolato sul training ma sul test, così da non valutare il modello overfittato.

### LOCO (Leave-One-Covariate-Out)

La LOCO ha lo stesso obiettivo della [[#PFI (Permutation Feature Importance)|PFI]], ma si basa sulla rimozione della feature da analizzare.
