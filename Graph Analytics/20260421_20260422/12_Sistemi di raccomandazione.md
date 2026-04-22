---
course: Graph Analytics
---

Un sistema di raccomandazione è un sistema che genera consigli specifici per determinati utenti in base ai loro interessi.

## Data modeling

Per modellare i dati di un sistema di raccomandazione ci sono 2 tipi di modello diversi:
- Descrittivo
	- una rappresentazione semplificata della realtà creata per uno specifico obiettivo di apprendimento. La semplificazione si basa sull'assunzione di cosa sia rilevante e cosa non
- Predittivo
	- una formula per stimare il valore di interesse sconosciuto. Questa formula può essere matematica, una query ad una struttura dati, o ogni combinazione di questi.

L'utilizzo di un recommendation system può avere diversi obiettivi ed utilità:
- Aumento del numero di item venduti
- Vendita di item diversi tra loro
- Incremento della soddisfazione dell'utente
- Incremento della lealtà dell'utente
- Migliore comprensione di cosa l'utente voglia

## Content-based Recommendation Systems (CBRSs)

I CBRS si basano sulla costruzione di profili per i vari item ed utenti tramite l'uso di item ed user descriptions così da suggerire items simili a quelli che l'utente target ha apprezzato in passato.
Questo tipo di sistema viene definito anche come **semantic-aware CBRS**.

Un CBRS si basa su 3 parti principali:
- Item analyzer
	- Estrae features e metadati dagli item
- User profile builder
	- Fa inferenza sugli interessi dell'utente basandosi sugli item che ha precedentemente apprezzato
- Recommendation engine
	- Esegue matching tra preferenze degli utenti ed item features
	- Calcola un **relevance score**
	- Esegue ranking degli item, per ottenere una classifica di raccomandazione.
![[Pasted image 20260422105503.png]]

Per costruire lo user profile abbiamo 2 modi diversi
- Feedback esplicito (chiediamo agli utenti)
- Feedback implicito (osserviamo il comportamento)

L'uso di user profiles ha diverse limitazioni:
- Overspecialization
	- Gli utenti ricevono items **troppo simili** a quelli che hanno già apprezzato, causando poca diversità nelle raccomandazioni
- Feature dependency
	- La performance dipende dalla qualità delle item features
- Ignora patterns di collaborazione tra utenti
- Cold start
	- Nuovi items non possono essere raccomandati finché le loro features non sono disponibili ed imparate
- Difficoltà ad imparare deep semantics o contesto

## Collaborative Filtering

Alla base di un recommendation system basato su collaborative filtering si trova solitamente una **matrice di raccomandazione**, una matrice contenente i punteggi di ogni item per ogni utente.

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

Esistono 2 tipi diversi di collaborative filtering:
- Memory based
	- Raccomanda un item guardando i neighbors (utenti o items simili) e usando le loro preferenze per fare le predizioni
- Model based
	- Approccio che non usa la matrice user-item a prediction time ma impara un modello offline che cattura le preferenze degli utenti e le caratteristiche degli items

### Memory based collaborative filtering

Un sistema memory based può usare diversi approcci:
- Item based
	- Cerca items simili
	- Controlla come l'utente li ha recensiti
	- Usa quelle recensioni per stimare quella nuova
- User based
	- Trova utenti simili al corrente
	- Controlla cosa gli utenti simili abbiano apprezzato
	- Raccomanda gli items che l'utente corrente non ha ancora visto
