---
course: Graph Analytics
---
I Graph DBs sono schema-free, di conseguenza non si definisce nessun tipo di dato astratto per i nodi, bensì si crea un nodo, definendo a che tipo appartiene, e poi si aggiungono gli attributi senza definire uno schema, facendo si che nodi dello stesso tipo possano avere un numero diverso di attributi, o addirittura attributi totalmente differenti.
Dal momento che nodi dello stesso tipo possono non possedere gli stessi attributi e le stesse caratteristiche, si può imporre che determinati attributi siano obbligatori, mantenendo comunque la libertà di aggiungere altri attributi unici per quel nodo.

La modellazione di un Graph DB segue 4 step:
1. Comprensione del problema
	- Vengono specificati termini comuni e pattern di accesso ai dati
2. Creazione di un modello concettuale
	- Si disegna un diagramma che possa rappresentare il problema ad alto livello
3. Creazione di un modello logico dei dati 
	- Vengono definiti vertici ed edges, e vengono specificate le loro proprietà
4. Test del modello
	- Si verifica che il modello soddisfa tutte le caratteristiche del problema

Problema: la maggior parte dei graph DBs sono schema-less, per cui anche definendo un modello logico è comunque possibile aggiungere dati senza seguire il modello in questione.
Questo problema si può arginare imponendo determinati vincoli, facendo si che alla creazione di un nodo di un certo tipo certi attributi siano obbligatori, imponendo dunque che essi abbiano sempre un valore.

### 1. Comprensione del problema

Per comprendere il problema è necessario rispondere a determinate domande, definendo dunque:
- Dominio e scopo del grafo
	- Cosa deve rappresentare il sistema
- Business entity
	- Quali sono gli elementi fondamentali dell'applicazione e come si relazionano l'un l'altro
- Funzionalità
	- Come gli utenti useranno il sistema
