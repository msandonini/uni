## Centeris Paribus (CP)

I plot [[Centeris Paribus (CP)]] visualizzano come cambiando una singola feature cambia la predizione per uno specifico data point lasciando costanti tutte le altre features

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

## Individual Conditional Expectation (ICE)


Una variazione del [[CP]] è l'[[Individual Conditional Expectation (ICE)]].
Questo metodo funziona circa come il CP, ma invece di concentrarsi sul singolo data point si concentra sull'intero dataset:
![[Plot_Individual_Conditional_Expectation.png]]

Il problema dell'ICE è che queste variazioni riguardano punti di partenza diversi, e presentano dunque degli offsets. Questo problema rende difficile capire la forma delle curve tra istanze diverse

Questo problema trova soluzione nell'uso dei *c-ICE* (Centered ICE), che rimuovono gli offset ancorando tutte le curve ad un punto di riferimento comune:
![[Centered_ICE.png]]

Una possibile evoluzione di questo metodo, che è un metodo globale, è il [[Partial Dependency Plot (PDP)]], nel quale per ogni valore dell'asse orizzontale viene calcolata la media, ottenendo dunque una curva che mostra la varianza

## Local Surrogate methods

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
