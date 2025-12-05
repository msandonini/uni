---
tags:
  - big_data
  - frequent_items
  - hashing
---
%% 2025/10/08 %%

Con *Frequent Itemset* si intende un set di elementi che appare in più *baskets*, ovvero che appare in diversi gruppi di dati

Cercare i frequent itemsets si rivela utile in scenari di mercato o nell'associazione di parole (ad esempio per imparare il contesto della frase o per identificare documenti simili).
Nella ricerca dei frequent itemsets è essenziale estrarre le *regole di associazione*, ovvero quelle regole che definiscono se in corrispondenza di un insieme di elemento $i$ sarà presente anche un elemento $j$.
Detto ciò, come possiamo capire se è la presenza di $i$ ad implicare $j$ o viceversa? Per farlo usiamo una metrica chiamata *confidenza*:

$$
\text{conf}(i \to j) = \frac{\text{support}(I, j)}{\text{support}(I)}
$$
- Dal momento che $(I, j)$ è un subset di $(I)$, il valore è tra 0 e 1
- Un valore di confidenza è più alto quanto più è importante la regola
- A volte, le regole estratte sono così ovvie che non è necessario segnarle (come ad esempio se un item è in ogni basket). In questi casi definiamo una nuova metrica chiamata *interesse* per escluderle:

$$
\text{Interest}(I \to j) = \left| \text{conf}(I \to j) - \Pr[j] \right|
$$
Trovare i frequent items è più difficile rispetto a trovare le regole di associazione, dal momento che per trovare le regole è necessario un semplice ciclo `for`, mentre per trovare i frequent items devo immagazzinare ogni elemento in memoria, e potrei quindi finirla durante l'esecuzione.
- Non è più difficile da un punto di vista del codice, bensì da un punto di vista hardware.
- Per ridurre il problema relativo all'esaurimento della memoria, solitamente ci si ferma a contare solo le tuple o le triplette.
- Una possibile ottimizzazione è quella di non contare le tuple o le triplette contenenti elementi non frequenti, in quanto se un elemento non è frequente certamente non può essere frequente un suo sottoinsieme

Per poter risparmiare ancora più memoria sono ci sono diversi metodi:
- Metodo della matrice triangolare: invece di salvare i dati in un dizionario li salviamo in un array uni-dimensionale che rappresenta una matrice triangolare.
	- Salviamo in $a[k]$ il contatore per la coppia $\{i, j\}$, con $1 \leq i < j \leq n$:
$$
k = (i-1)\left( n - \frac{i}{2} \right) + j - i
$$
- I contatori vengono salvati come triplette $[i, j, c]$
	- Questa tecnica sembra più costosa, tuttavia è utile in caso ci sia un grande numero di tuple il cui contatore è pari a 0

## Algoritmo A-Priori

Questo algoritmo è molto costoso temporalmente, in quanto viene applicato una volta per ogni cardinalità che voglio trovare

![[Algoritmo a priori]]

---

# Hashing

%% 2025/10/15 %%
%% TODO: Includere disegni, esercizi, e diagrammi dal tablet %%

## Hashing universali

Come accelerare questa tecnica?
Invece che fare tutte le permutazioni si può permutare un sottoinsieme.
- Caso fortunato: il sottoinsieme è abbastanza grande da far si che non ci siano dei vuoti
- Anche con dei vuoti, l'unico problema è se ce n'è più di uno per riga

### LSH (Locality Sensitive Hashing)

Tecnica di hashing che riduce il numero di operazioni, si basa sulla costruzione di insiemi di documenti candidati ad essere simili

%% TODO %%

Questa tecnica è valida ad una condizione: 2 documenti finiscono nello stesso bucket solo se sono completamente identici, ma se sono uguali "solo" al 95% potrebbero finire in bucket diversi.
Questo comporta che questa tecnica abbia un alto tasso di falsi negativi

*N.B.*: lo stesso documento potrebbe finire in più bucket diversi, così che sia più semplice per un documento finire con i simili ma non uguali.

%% TODO %%

Dividendo in diverse bande ci sono più confronti e più falsi positivi (questi ultimi non sono un problema dal momento che posso eseguire nuovamente il confronto), e si riducono i falsi negativi.

- La probabilità che nella stessa banda tutte le right siano uguali tra loro è $s^r$
- La probabilità che nella stessa banda ci sia almeno una riga diversa è $1 - s^r$

