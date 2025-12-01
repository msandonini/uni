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

YOLOv11 contiene i seguenti modelli:
- Detection (COCO)
- Segmentation (COCO)
- Classification (ImageNet)
- Pose (COCO)
- Oriented Bounding Box (DOTAv1)

YOLO si basa sulla metrica [[mAP (Mean Average Precision)]], a sua volta basata su:
- [[IoU (Intersection over Union)]]
	- Misura l'overlap della bounding box predetta rispetto alla ground truth
$$
\text{IoU} = \frac{\text{Area of overlap}}{\text{Area of union}}
$$
- Precision
	- Misura il numero di veri positivi rispetto alla somma di veri e falsi positivi
$$
\text{Precision} = \frac{\text{TP}}{\text{TP} + \text{FP}}
$$
- Recall
$$
\text{Recall} = \frac{\text{TP}}{\text{TP} + \text{FN}}
$$

La [[AP (Average Precision)]] è una metrica che calcola un'area più bilanciata sotto la curva precision-recall
$$
\text{mAP} = \frac{1}{n} \sum_{k = 1}^{k = n} \text{AP}_{k}
$$
Nel caso di YOLO viene mostrata la COCO mAP, ovvero la mAP ottenuta con il dataset COCO variando la soglia tra 0.5 e 0.95.

Essendo allenato su COCO, YOLO può riconoscere 80 classi diverse.

---

###

