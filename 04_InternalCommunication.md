# Internal Vehicle Communication Protocols
k-line is not used anymore se non per qualche veicolo prodotto in india
quindi non lo facciamo --> skippare le slide

the only reason why k-line makes sense deals with the obd connector
il connettore obd ha dei pin per la k-line

---

slide 15 LIN
lin è stato creato per essere più economico di can (anche se è comunque difficile, perchè can è molto economico)

sviluppato in 1999
seconda versione in 2003

seconda versione backwards compatible
seconda versione ha un sacco di estensioni

si hanno in automotive molti lin components

specifica gli stessi layer iso osi di can bus --> application + data link + physical
same layers --> from an architectural point of view it is the same of can

alla fine usa una serial line communication --> è un protocollo uart alla fine

lin usa master slave concept --> deterministic e centralized --> una entità centrale master dice se si può trasmettere o no
can invece usa carrier sense multiple access --> diverso --> random and collision free

lin ha self synchronization
non ha nessun oscillatore al quarzo --> fatto per ridurre prezzo (oscillatore costa molto in una scheda)
si deve quindi rilassare la sincronizzazione, visto che non si ha un clock

on the other side, at least one node must add the clock
tipicamente quel nodo è un nodo del can bus --> quindi lin è usato come una subnetwork di un nodo can nel 99% dei casi
il nodo can a cui è attaccata la subnetwork lin è il master della rete lin

bidirectional over just a single wire
up to 20 kb/s --> 2 order of magnitude slower than can --> per il fatto che i nodi non hanno clock e si deve fare sincronizzazione in modo strano
con una velocità bassa di comunicazione è difficile perdere il clock --> per quello si ha bassa velocità di comunicazione

si ha start bit + data + stop bit

---

message oriented --> si ha una schedule codificata nel master che dice chi parla e quando
!= can bus --> event oriented (si fa carrier sense e si prova a comunicare quando si ha una informazione)

master ha una schedule
tale schedule dà più o meno importanza ai nodi lin del sistema
--> nodi con più importanza sono nodi con più tempo per trasmettere

schedule è statica e encoded to the master
no flexible medium access

the schedule is the only thing you can play with (in lin)

con la schedule si sa quindi quando un nodo potrebbe iniziare a trasmettere e finisce la trasmissione
tecnicamente lo sa solo chi sa la schedule --> master
quindi da un punto di vista delle deadline lin va molto bene --> lin va bene per sistemi deadline compliant

per il fatto della schedule, lin è time deterministic

la schedule può anche essere cambiata a runtime
questo perchè gli slave non sanno niente, e sono svegliati dal master --> se il master non li sveglia gli slave non si accorgono di niente

however, the price of this knowledge is the slowness of the communication

---

error detection slide 17
è un checksum --> molto rudimentale e facilmente aggirabile
no correzione degli errori --> solo detection

---

slide 18
al giorno d'oggi in una macchina ci sono più nodi lin che nodi can
perchè lin network è ottima per alcuni domini e molto economica --> ad esempio lin ottimo per dominio di comfort (finestrini, regolazione
specchietti, climatizzazione)

lin va bene per i domini per cui non serve a una beata minchia la velocità di comunicazione
quindi sicuramente non sono domini safety critical

---

slide 19 lin frame
molto diverso da can frame --> pochi blocchi (solamente 5)

blocco break è inutile --> è solo una sequenza di bit 0 (dominanti) --> serve solo per cominciare una comunicazione

poi si ha blocco sync --> sequenza di 010101 --> usiamo NRZ e ci servono transition per acquisire un clock
esiste un chipset che prende un clock e continua a ripeterlo internamente nel circuito di un nodo LIN --> è come se dopo il blocco sync si avesse
un clock

initial part of the message (header) is only in charge of the master --> è solo il master che la manda
una volta che si ha finito l'header un nodo LIN legge e scrive sul bus

dopo header si ha messaggio
intero frame più corto di un frame can

---

## identification of the slave node
nell'header si ha un identifier --> che il master usa per identificare il nodo slave che deve comunicare in quel momento
identifier fatto da 6 bit di id del nodo slave + 2 bit di parità che proteggono l'id

i 2 bit di parità ci sono perchè è importante capire chi deve comunicare in modo corretto
se si hanno più nodi che pensano di dover parlare si ha mega casino atomico
si deve quindi essere sicuri che solamente uno specifico nodo trasmette alla volta

no multiple access (come era per CAN in cui più nodi potevano iniziare a comunicare insieme) --> un master dice ad un nodo solo di comunicare
unico modo in cui si potrebbe avere multiple access è se due nodi pensano di essere stati svegliati dal master per comunicare (che non deve
succedere)

### parity check
scritto a slide 20 e che coinvolge degli operatori xor
facilmente ricordabile con blocchi tetris (vedi foto)

---

slide 21 lin message
non si ha un control block --> si sa la lunghezza del messaggio perchè identifier porta anche informazione in qualche modo del tipo di messaggio
(e un tipo di messaggio ha una lunghezza definita)

comunque tipicamente nelle implementazioni reali si ha lunghezza di un messaggio di 8 byte

checksum alla fine del messaggio
è un checksum 256 bit
si possono scambiare bit in colonna o addirittura byte per fregare il checksum

cercare checksum come viene fatto
esempio di checksum computation slide 23 e successive

slide 33 checksum con + di 2 byte
arrivati a bit d1 si ha 1 con carry 1
arrivati a bit d2 si ha 0 con un carry su d3 e un carry su d4
arrivati a d4 si ha 110 --> risultato 0 e due carry ??

---

slide 26 deployment
lin è una subnetwork di can
lin è usato per dominio body and comfort

`è chiaramente un maggiolino della volkswagen`

dal lato destro si ha comando del lato sinistro dal punto di vista dei finestrini
si ha nodo lin che manda messaggio al master (can)
nodo can manda messaggio in broadcast, che viene ricevuto da un altro nodo can che è master della seconda subnetwork lin

si ha encapsulation
8 byte di payload can e 8 byte di messaggio lin --> si può incapsulare un messaggio LIN nel payload CAN

---

slide 36
header può essere trasmesso solamente dal master

the ID triggers the slave, but also triggers a specific action that the slave has to do
it could also be that the master triggers a slave to listen (and not to talk)
può anche essere che il master triggeri tutti gli slave in una singola volta

potential frame type triggered with the ID sono indicati a slide 37
un solo frame type user defined
un frame type riservato per il futuro

descrizione frame types slide 38
- unconditional --> master dice ad uno slave di dire qualcosa e slave comunica
- event trigger --> master sveglia tutti sperando che solo un nodo comunichi (e divisione dei byte del messaggio tra i nodi slave)
- sporadic --> broadcast del master --> master sveglia tutti per leggere
- diagnostic generalmente non usato
- user defined
- riservato

---

slide 39 differenze tra CAN e LIN
stiamo considerando una versione molto lenta di can bus nella slide

LIN usa 40 volt
CAN potrebbe avere (raramente) cavi shielded --> generalmente sono solo twisted

---

## FlexRay
slide 43

ray = name of a fish
manta / razza

se una parte del nome è il nome di un pesce, le altre lettere saranno di sicuro importanti

flex --> strano, visto che è il protocollo meno flessibile che si possa immaginare
è come una read only memory

`il prof dice che il nome del protocollo è stato inventato da un coglione ubriaco`
comunque protocollo molto importante

flexray is time deterministic
il consorzio di creazione di flexray è composto da partner slide 43
marche di lusso (tranne bosch praticamente)

nxp e freescale sono aziende di semiconduttori --> servono chip
automotive partners --> si vuole che flexray sia applicato in dominio automotive

---

deve essere più veloce di can e anche più affidabile
being more reliable than can is difficult

flexray usa ridondanza di nodi e linee (per essere più robusto di can)
e quindi costa anche di più di can

usato per drive/brake/steer by wire
cose che non erano normali qualche anno fa --> si aveva tutto meccanico

ora molto comune avere drive by wire --> acceleratore elettronico `(cioè se volessimo essere precisi abbiamo un acceleratore che è una`
`sorta di potenziometro e una farfalla elettronica che controlla flusso d'aria e un controllo della quantità di carburante`
`iniettato fatto elettronicamente)`

by wire = electronic inputs
no feedback (feedback simulato da dei motori elettrici)

non si ha garanzia che i comandi dati dal guidatore siano effettivamente inviati e eseguiti
che è una garanzia che si vorrebbe avere quando si guida una macchina --> ma non la si ottiene sicuramente con CAN bus che ha problema della
starvation (se bus è busy e per questioni di arbitration)

in più can non è deterministico per il bit stuffing --> si potrebbe avere fisicamente un numero di bit maggiore o minore sul bus (per il bit stuffing)

---

is the human the source of information or is an algorithm?
un algoritmo può fare sensing e attuazione

esempio --> mantenimento attivo di corsia --> overrule the driver to avoid crossing the other lane
the car can actuate (not just notify)

se si ha sistema che ha attuazione sicuramente si ha flexray
se si ha solamente una segnalazione sonora per il guidatore si ha un altro protocollo