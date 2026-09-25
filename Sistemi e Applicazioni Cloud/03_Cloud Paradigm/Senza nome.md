Lo scaling (passare da una VM a molte o viceversa) può avvenire in brevissimi lassi di tempo.
Per permettere questo scaling, e per ridurre i possibili problemi, facciamo uso di 2 tecniche:
- Replicazione
- Orchestrazione (autonoma)

Determinati paradigmi di programmazione non possono essere applicati al cloud a causa dei vari point of failures di quest'ultimo:
- Processi
	- Sincronizzazione su larga scala
- Dati
	- Consistenza
	- Immagazzinamento e processing
- Comunicazione
	- Sincronia
	- All-to-all

