All'interno della Computer Vision rientrano principalmente 3 task:
- Classificazione
	- Associazione di etichette a singoli oggetti a partire da un'immagine
- Object detection
	- Localizzazione di oggetti diversi presenti in un'immagine
- Segmentazione
	- Localizzazione di oggetti diversi presenti in un'immagine più avanzata, con bounding box dalle forme più complesse

## YOLO (You Only Look Once)

Famiglia di sistemi di Computer Vision pensata per l'utilizzo in contesto real-time.
Si basa su una rete convoluzionale composta da 3 step:
- Riduzione delle dimensioni dell'immagine iniziale
- Esecuzione della rete convoluzionale
- Non-max suppression

Si distingue dai modelli precedenti in quanto analizza l'intero frame dell'immagine invece di far passare sotto-sezioni dell'immagine attraverso una moltitudine di reti, risultando più veloce.

Non è l'attuale stato dell'arte per quanto riguarda l'accuracy, ma lo è per quanto riguarda la velocità.