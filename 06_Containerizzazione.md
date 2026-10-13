3 elementi importanti per avere un container
- jailed process
- filesystem a livelli (aufs originale, ora overlayfs)
	- ultimo filesystem che è quello che vede il container prende il nome di "merged"
	- il container vede un merge di layer del filesystem
	- merged layer non occupa spazio ed è virtuale fino a che non avviene una write
- 3° elemento è immagine ??

slide 102
sul registry c'è una serie di immagini che si possono scaricare
di ogni immagine ci sono tante versioni
se non si specifica versione, viene scaricata la versione "latest" in automatico --> ultima versione stabile (non ultimissima versione)
senza specificare il registro si fa pull da docker hub (registro di default di docker)

quando si fa il pull si fa pull di vari layer
alla fine quei layer sono sommati (merge) e viene giù l'immagine completa

immagine = equivalente della classe
oggetto = classe istanziata
come programma e processo

volumi slide 103
meccanismo essenziale del sistema di containerizzazione

fino a che sono attivi ci si può interagire, ma quando sono spenti o si imposta la persistenza o spariscono (vengono distrutti automaticamente)
fino a che non si da permanenza dei dati, quello che si fa in un container resta dentro il container

per avere permanenza si devono montare i volumi
volumi sono quelli che danno persistenza dei dati
sono gestiti solo da docker e sono un layer overlayfs e non vengono di default raccolti dal garbage collector

docker crea un layer di overlayfs che diventa uno dei layer da usare nel merge la prossima volta

volume slide 104
può essere montato nel punto giusto del OS
si creano i punti di mounting esattamente dove se ne ha bisogno

volumi possono anche essere condivisi tra container
ad esempio quando si ha web server si possono far servire dei file statici
conviene quindi fare un volume condiviso tra più container (esempio: container del web server e container del reverse proxy)

volumi separati dalle immagini
si possono portare dei volumi da un'immagine all'altra --> poi chiaro che dipende cosa c'è nel volume, gli eseguibili generalmente non sono
condivisibili tra sistemi operativi diversi

slide 105
immagine si genera in un file che si chiama `Dockerfile`
si può usare anche altri nomi, ma lo standard è `Dockerfile`

si può partire da una immagine già fatta --> come ereditarietà di classi python
come in python si eredita sempre da object, in docker si parte sempre da un file specifico

c'è sempre from (o da altra immagine o da overlayfs base)

siccome si può partire da un file, alcuni per nascondere la costruzione dell'immagine buildano l'immagine e la convertono in un file
quindi si fa sempre from file
`cosa becera ma ok`

si definisce una sorta di script che dica come si parte da una immagine e si arriva ad un'altra immagine
tutti gli step sono definiti nello script

alla fine del file si deve avere sempre un comando
di default se un comando non tiene vivo il container, il container appena si avvia muore
comando è quello che tiene vivo il container dall'avvio

slide 107
nel dockerfile si devono usare primitive standard
- FROM --> dice da che immagine / file partire --> con `:` si specifica la versione
- ARG --> argomento (parametro del processo)
- EXPOSE --> espone porte
- RUN --> esegue comando (prima di avviare il comando interattivo per tenere vivo il container)
- COPY --> copia un file dalla macchina reale nel container

solitamente se non si specifica, le versione di default delle immagini sono basate su alpine --> più leggero di un debian

comando from slide 108
vuole immagine da usare come base --> generalmente image\[:tag\]
se non si specifica niente si va su dockerhub a prendere l'immagine --> si specifica con \<nome_registro\>/immagine\[:tag\]

comando copy slide 109
copia da una source a una destination
source è fuori dal container, destination è dentro il container

se non si vuole copiare dal sistema locale si usa parametro --from (per specificare un altro container da cui copiare)

si possono caricare anche intere cartelle e pezzi del filesystem
invece che fare una vera copia in quel caso si fa una **bind mount**

alternativa a copy = ADD
stessa sintassi ma leggermente diverso nel funzionamento
copy tiene traccia dell'eventuale cambiamento della source (tramite un hash) --> se ci sono stati cambiamenti e si richiama il build il comando
deve capire se rifare la copy o no al momento del build

ENV slide 110
definisce variabili d'ambiente --> spesso usate nei processi
equivalente di fare export
non avviene durante la build ma avviene a runtime --> non si deve settare l'ambiente al momento della build --> env si possono mettere dove si
vuole nel dockerfile

RUN slide 111
esegue il comando che permette al processo di esistere (o qualsiasi altro comando prima)
spesso i comandi hanno come punto di accesso /bin/sh -c

VOLUME slide 112
specifica che una cartella del container deve diventare un volume e quindi essere persistente

docker container inspect fa capire quali sono i volumi
generalmente i volumi hanno come nome un hash gigante

una volta che si crea il volume si crea una cartella nel fs locale
ci si può interagire con comandi shell base ma anche con docker volume ...

USER slide 113
fa uno user switch
generalmente si deve all'inizio partire come root per installare cose
poi alla fine conviene cambiare utente (anche per impedire una privilege escalation)

quindi ad una certa dopo alcuni run che vanno come root conviene fare una user

workdir slide 114
da un certo punto in poi cambia la directory da cui si lavora
di default si parte dalla root del filesystem
da quel momento in poi tutti i comandi eseguono da quella cartella di lavoro

slide 115
expose espone porte
docker si ricorda a runtime (non a build dell'immagine) si deve eseguire un comando per esporre delle porte
comando è firewalldir --> fa in modo che una porta esista e sia aperta a livello di sistema

CMD slide 116
è il comando che viene eseguito per fare lo startup
non viene eseguito alla costruzione
è quello che vine eseguito per tenere vivo il container --> cuore del run --> come una init in una classe
la init viene eseguita solamente alla creazione di un oggetto (come prima cosa generalmente)

entrypoint
in alcuni container altamente specializzati si vuole che i comandi siano limitati alla specializzazione
o alcuni comandi hanno sempre bisogno di un contesto prima

ad esempio container git serve per creare comandi git --> punto di ingresso conviene che sia git
qualsiasi comando che si passa è un subcommand di git

entrypoint di default dei container base è /bin/sh --> che è motivo del fatto che si possa eseguire un comando (es: LS) alla creazione di un
container --> docker ... ubuntu ls --> prima parte /bin/sh e poi parte ls

---

orchestrazione slide 118
i container sono non molto più utili che avere tanti script che automatizzano delle operazioni (es: avvio di un web server)

orchestrazione risolve questo problema
si passa da una logica imperativa con uno script a una logica dichiarativa --> si dichiara semplicemente come si vuole il sistema

docker all'inizio lo faceva con uno script sh enorme docker compose
script creato dalla community ed enorme
quello script interpretava uno yaml e trasformava le cose dello yaml in comandi

ora è così popolare che docker lo ha integrato
ora docker ha subcommand compose

serve per avviare più container e orchestrarli insieme
docker compose fa cose slide 120

docker compose è una versione ristretta di docker swarm

slide 121
nel docker compose si ha un file e una command line interface

nel compose file si dichiarano servizi, volumi, immagini, networking, cose come una startup sequence
eventualmente si possono anche definire dei test per verificare lo stato di salute dei container

slide 122 compose file
version ora non esiste (deprecato)
services definisce quali sono i container da avviare

primitive fondamentali sono
- build --> specifica servizi da costruire da dockerfile
- up --> crea e avvia
- down porta giù tutto senza uccidere volumi --> -v per eliminare i volumi
- ps dice quali container sono attivi
- logs dà i log del servizio
- exec è comando di debug

---

docker compose rimane modo avanzato per rendere veloci delle cose fatte con degli script
orchestrazione pura avviene con docker swarm o kubernetes

comunque non sempre utile avere orchestrazione
spesso anche difficile, quindi non conviene se non è utile

swarm non è morto ed è ideale per piccole e medie aziende
swarm è pensato per piccoli carichi on premise (dentro nell'azienda) e applicazioni non critiche

velocity = somma di velocità e stabilità
si vuole aumentare velocità senza compromettere stabilità

in swarm e kubernetes le cose sono immutabili
se cambia qualcosa è perchè è cambiata la dichiarazione
ottica dichiarativa --> si dichiara come si vuole il servizio e non si fanno i comandi a mano
si dichiara tutto in un file yaml

orchestratore valuta qual è l'actual state e come è diverso dalle cose dichiarate
allora poi fa i task che permettono di arrivare dall'actual state allo stato dichiarato

architettura decoupled
se sono amministratore di sistema, mi fido di cosa deve andare su --> gestisco sistema, non applicazione
logica dichiarativa permette di separarsi dal discorso dello sviluppo dell'applicazione --> un po' il contrario di devops
astrazione da quello che si ha sotto

e comunque anche il sysadmin non gestisce kubernetes
si ha un gestore che sistema l'hardware del cluster, che è ancora diverso dal sysadmin
kubectl è applicativo da pc per gestire un cluster kubernetes --> quello usato del sysadmin (che non gestisce hardware)

task = minima unità deployabile in swarm --> in kubernetes è un pod
loadbalancing si fa con swarm service e routing mesh (su swarm) o service su kubernetes
... (vedi tabella differenze tra swarm e kubernetes slide)

routing funziona a livello 7 qui negli orchestratori
non è un discorso di ip e invio della richiesta ad un nodo
è un discorso di passare informazioni a diversi container / applicazioni

elementi kubernetes
- pod --> minimal deployable unit --> singolo container o unione di più container che devono stare insieme
- servizio = sovrastruttura del pod --> prende un pod e aggiunge cose (come naming, discovery e un po' di load balancing)
- replicaset --> elemento che definisce regole dell'applicativo (come regole di ridondanza, scalability, update ...)
- ingress --> load balancer di ingresso a kubernetes --> permette di fare magia di accedere ad un server qualsiasi per load balancing

namespace e contexts servono per gestire i tantissimi servizi generati da kubernetes

ogni container è dentro ad un suo cgroup
cgroup sono quelli che permettono di gestire risorse assegnate ad un processo --> serve per evitare deadlock o problemi di consumo eccessivo
di risorse

pods sono diversi dal servizio --> pod potrebbe essere un'unione di due container che devono stare insieme
pod manifest vedi slide
metadati riguardano la gestione del pod ma non la creazione in sè
spec definisce le specifiche del pod --> quali container avviare

quando si avvia un pod va poi trovato --> si trova con delle label

deployment con kubernetes slide --> con replicaset
si ha rollback e si possono usare strategie di deployment (e a/b test ad esempio)

---

swarm permette di fare cose molto simili
strategie molto simili anche

unica cosa particolare è un file che contiene un task (equivalente del pod)
task è un singolo container (non potenzialmente più di uno ??)

service discovery di swarm è diversa da kubernetes
tutto è gestito via internal dns --> non serve mettere un ingress

load balancer permette di fare meno che ingress di kubernetes
