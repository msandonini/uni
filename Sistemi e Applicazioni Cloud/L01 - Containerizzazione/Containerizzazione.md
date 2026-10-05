---
date:
  - 2026/10/05
---
# Containerizzazione

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
	- Più safe in quanto le librerie sono incluse nell'eseguibile, ma l'eseguibile pesa di più in quanto la stessa libreria non può essere condivisa tra più programmi, e in caso di scoperta di falle di sicurezza devo aggiornare manualmente (io sviluppatore) la dipendenza
- Linking dinamico
	- Librerie linkate a compile time e bindate al runtime
	- I simboli sono risolti dal linker
		- File `.a`: stubs di librerie
		- File `.so`: shared objects
	- Il codice delle librerie viene caricato e boundato dinamicamente agli stubs:
		- `ld.so`: linker dinamico
	- I file `.so` possono essere condivisi da diversi eseguibili

Quando pacchettizzo un eseguibile solitamente il pacchetto finale contiene dei metadati contenente informazioni sulle dipendenze.
Da ciò derivano problemi di complessità nel dependency graph e di conflitti di dipendenze.

Per ridurre problemi di conflitti delle dipendenze senza gli svantaggi dello static linking, quello che posso fare è pacchettizzare le applicazioni in un container.

Un container può essere paragonato ad una VM, ma con alcune differenze

| Container                 | VM                       |
| ------------------------- | ------------------------ |
| Astrazione dell'OS        | Astrazione dell'HW       |
| Eseguito sullo stesso OS  | Eseguito su OS diversi   |
| Basso utilizzo di risorse | Alto utilizzo di risorse |
| Basso overhead            | Alto overhead            |

## Principi di containerizzazione

Il concetto di container è nato alla fine degli anni 70, e si basa su conocetti introdotti da diverse tecnologie e loro evoluzioni negli anni:
- `chroot` (1979): system call che permette ad un processo e ai suoi figli di posizionarsi in un file system di root diverso.
	- Permette una sorta di segregazione dell'accesso dei file ad una base per processo
	- Primo esempio di **process isolation**
		- Sistema usato da BSD che permette di creare environment (jail nel caso di BSD) diversi ognuno isolato dagli altri e con configurazioni diverse tra l'uno e l'altro
- VServer (2001)
	- Introduzione su Linux delle Jail come contesto di sicurezza
- OpenVZ (2005)
- LXC (2008)
	- uso di `cgroups` e namespaces Linux (prima soluzione di containerizzazione completa su Linux)


