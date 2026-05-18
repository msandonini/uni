# Graph for Urban Mobility

la lauretta prima di iniziare la lezione ci ha già detto che non ha la versione giusta di neo4j per fare le query sulle slide (ovviamente fatte da lei
immaginiamo)

problemi e sfide in ambito mobilità (slide 4)
- il probblema di Palemmo è i' **traffico**
- inquinamento e cambiamento climatico (in alcune fasce temporali d'estate le persone fragili non si muovono)
- dipendenza dall'automobile privata
- accessibilità disomogenea (a seconda di come ci si riesce a muovere non ci si sposta ovunque)
- integrazione insufficiente di vari mezzi (trasporto multi-modale --> vado a prendere l'autobus, poi scendo e prendo la bici ...)
- sicurezza (ad esempio per i pedoni)
- ... (vedi slide 4)

quali sono i dati di mobilità?
- orari e percorsi autobus ad esempio
- ...

ci sono dati di mobilità
- statici --> con una dimensione spaziale ma che rimangono fissi nel tempo --> descrivono dove si trovano alcuni punti nello spazio
- dinamici --> con una dimensione sia spaziale che temporale

vedi slide 6 per esempi di dati statici e dinamici

dati statici comprendono i point of interest --> luoghi di interesse (negozi, servizi, chiese, ristoranti ...)
traffico medio --> non ha una dimensione temporale, perchè è il traffico **medio**
... (vedi slide 6)

matrici origine-destinazione = dati in input che descrivono gli spostamenti dei cittadini all'interno di una zona
spesso sono usati dagli uffici mobilità dei comuni
hanno un'indicazione di un punto di origine e uno di destinazione
dipendono dal tempo

una volta erano create facendo delle interviste, mentre ora sono create a partire dai sistemi di localizzazione installati dalle assicurazioni nelle
auto (in alcuni casi)

slide 7
dati spazio temporali --> serie temporali riferite ad un punto
ad esempio un sensore di traffico che conta il numero di veicoli che passano in un certo punto
alcuni distinguono anche il tipo di veicolo

oppure serie temporali riferite ad una certa zona
esempio --> traffico in una città in una certa fascia oraria

slide 10 non sono spazio-temporali ma solamente spaziali

slide 11 altro esempio
mappa dinamica dell'inquinamento al variare delle ore del giorno
inquinamento si sposta per via del vento

dati geospaziali --> slide 12-13
possono essere 2d o 3d (con anche altezza) o 4d (con anche tempo) e possono essere espliciti (conoscendo il punto) o impliciti (si sa una zona)
possono essere disposti su layer diversi --> ogni strato è un dato geospaziale

usano coordinate geospaziali
ci sono due riferimenti
- GCS --> sistema di coordinate geografiche che si riferiscono al punto della terra
- PCS --> sistema di proiezione che si usa (`chiaramente non si sa che cosa significhi sta roba perchè non lo sa neanche la prof`)

una coordinata senza proiezione corrisponde a + punti
la proiezione ci dice il sistema di riferimento

le coordinate infatti cambiano a seconda della forma che assumiamo che abbia la terra ??
la terra è un geoide (`anche se qualcuno dice che è piatta`)

la proiezione è il modo in cui rappresentiamo la superficie terrestre su un piano
slide 22 esempio per capire i modi in cui possiamo "stendere" / proiettare la superficie terrestre su un piano

ci sono due sistemi che sono usati per la proiezione della superficie terrestre
si chiamano sistemi SRS e ce ne sono vari
- WGS84 --> sistema di coordinate **geodetico** mondiale --> sistema usato da google nelle mappe
- ...

slide 25 modi di rappresentazione dei dati geospaziali
- vettori
- raster (immagini ottenute associando ad ogni pixel o gruppo di pixel una coordinata spaziale)

da una parte si ha un vettore che rappresenta qualcosa di geometrico
dall'altra si ha una "griglia" con tanti valori all'interno (`qualsiasi cosa la Po pensi che voglia dire`)

slide 26 differenza vettori / raster

il modo in cui si rappresentano i dati influenza il modo in cui li si memorizza effettivamente
raster = file tabulare in cui in alcune celle si hanno dei valori ??

slide 27
la codifica dei vettori può essere con un WKT o un WKB --> rappresentazione testuale o binaria (applicabili entrambi a qualsiasi vettore)
riquadro blu è tutto in formato testuale (WKT)

diversi database che permettono di memorizzare vettori e raster (esempio slide 28)
neo4j non nasce come db spaziale ma ci sono delle estensioni per memorizzare dati geospaziali

perchè serve memorizzare una coordinata spaziale (ad esempio di un point of interest come un negozio)?
perchè così sappiamo in che zona si trova un point of interest e cosa c'è di vicino
possiamo quindi fare intersezioni e analisi spaziali (si possono fare delle query spaziali --> "quali sono i ristoranti vicini all'università")

slide 29
r-tree --> suddivide i dati in rettangoli
gist --> alberi di ricerca generalizzati --> vedi slide

ellissi verde e gialla = oggetti gist
rettangoli = oggetti r-tree

slide 30
in neo4j si ha un plugin `spatial` per query spaziali
dati vettoriali possono già essere memorizzati in neo4j senza estensioni ma con delle limitazioni
con l'estensione si possono avere funzionalità migliorate e alcune facilitazioni --> aggiunta degli r-tree

slide 31
openstreetmap e overpass turbo spiegazione
si possono usare per lavorare con dei dati spaziali

database a grafo per dati di mobilità slide 32
- permettono di rappresentare reti di trasporto in modo scalabile e veloce
- però faticano nella gestione delle serie temporali

`secondo me in queste coordinate spaziali è ora di una pausetta`

rappresentazione della rete stradale dipende dallo scopo
la rappresentazione più comune vede gli incroci che sono nodi e le strade che sono edge (primal graph)
ma non è detto che sia sempre così

slide 36 primal graph
rappresentazione incrocio è univoca ma la rappresentazione della strada non è univoca --> una stessa via è rappresentata più volte per
connettere più incroci ??

osmnx slide 37
traduzione dei dati di openstreetmap in un grafo neo4j
inseriamo anche la geometria del nodo --> latitudine e longitudine
inseriamo status degli edge, che indica se la strada è aperta o chiusa

poi colleghiamo i punti di interesse agli incroci + vicini

slide 38

slide 39
betweenness centrality ci permette di capire quali sono gli incroci + attraversati (per cui passano + cammini minimi)
incroci + critici sono quelli che hanno una betweenness centrality maggiore
analisi "statica" della topologia --> se non si cambiano le strade non cambiano i risultati dell'analisi

slide 41
degree centrality (numero di archi incidenti su un nodo)
un incrocio ha un degree pari al numero delle strade che collegano

`c'è Peppe che si fa dei video a caso e li manda alle tipe su whatsapp`
`facendo copia e incolla dalle slide della Po la Cami ha trovato link di wikipedia e commenti di chat (slide prima della 41)`

il degree da solo non ci dice nulla, ma calcolando un weighted degree (degree pesato) possiamo estrarre altre informazioni

ad esempio supponiamo di mettere sugli archi il valore del loro traffico (come peso)
degree pesato è quindi la somma del peso di ogni arco (non del numero di archi che si hanno)

per ogni incrocio sommo tutti i valori di traffico degli edge incidenti --> quindi si possono trovare gli incroci + congestionati
questa analisi non valuta solamente la topologia ma anche la congestione della rete --> è un'analisi "dinamica", non come l'analisi della
betwenness

come si trovano gli incroci o strade principali? --> slide 44
si usa una rappresentazione diversa dal primal graph, che viene chiamato **dual graph**
i nodi sono le strade e gli edge sono i collegamenti da una strada all'altra (incroci)

slide 44 e 46 differenze primal / dual graph

slide 47-48 analisi fatte con neo4j dalla dottoranda da cui ha preso le slide
si può calcolare una degree centrality pesata dal primal graph
poi si esportano i dati in un dual graph e la degree centrality viene trasportata sugli edge
calcolando il pagerank dei nodi del dual graph si ha uno score di ogni strada

slide 49
si crea primal e dual graph di una città
il grafo è integrato anche coi point of interest

però nello stesso modo si possono rappresentare percorsi ciclabili / pedonali o del trasporto pubblico
questi grafi si possono disporre su diversi layer --> tanti grafi diversi uno sopra l'altro
si possono collegare nodi di layer diversi ed ottenere un'analisi che coinvolge più scenari

ad esempio in un nodo possono convergere + percorsi --> da un nodo posso prendere l'autobus ad esempio
questo permette di fare una multi-modal analysis --> con informazioni su + mezzi di trasporto e che permette di fare routing che coinvolge +
mezzi di trasporto