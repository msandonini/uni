---
date:
  - 2026/10/05
---
Container: unità auto-contenuta di dimensioni standard, modulare, facile da trasportare.

Un processo contiene una parte statica ed una parte dinamica:
- Statica:
	- Lista di istruzioni (il programma)
	- Dati statici (file, configurazioni, ...)
- Dinamica:
	- Registri
	- Memoria
	- Risorse allocate

Ciò che permette ai processi di funzionare sono le librerie, che a loro volta possono essere linkate staticamente o dinamicamente:
- Linking statico
	- Librerie linkate a compile time
	- I simboli sono risolti dal linker
		- File `.o`: oggetti creati dal compilatore
		- File `.a`: librerie
	- Più safe in quanto le librerie sono incluse nell'eseguibile, ma l'eseguibile pesa di più in quanto la stessa libreria non può essere condivisa tra più programmi
- Linking dinamico
	- Librerie linkate a compile time e bindate al runtime
	- I simboli sono risolti dal linker
		- File `.a`: stubs di librerie
		- File `.so`: shared objects
	- Il codice delle librerie viene caricato e boundato dinamicamente agli stubs:
		- `ld.so`: linker dinamico
	- I file `.so` possono essere condivisi da diversi eseguibili


