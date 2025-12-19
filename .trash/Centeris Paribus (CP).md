---
tags:
  - big_data
  - explainable_ai
aliases:
  - CP
  - Centeris Paribus
---
I plot [[Centeris Paribus (CP)]] visualizzano come cambiando una singola feature cambia la predizione per uno specifico data point lasciando costanti tutte le altre features

Questo metodo funziona in maniera molto semplice:
- Si selezionano un data point da osservare e una feature di interesse
- Si cambia sistematicamente il valore della feature all'interno del suo range
- Si plotta la previsione del modello per ogni valore
- La curva risultante mostra quanto la predizione sia sensitiva al valore di quella specifica feature

Questo metodo ha 2 principali problemi:
- Le features vengono valutate una per volta, assume quindi che ogni feature sia scollegata da ogni altra
- Modificando i valori si vanno a creare combinazioni di valori che non rappresentano casi reali
Nonostante questi problemi il metodo funziona.
![[Plot_Centeris_Paribus.png]]
Nell'immagine viene mostrato un plot CP che mostra quanto le dimensioni del becco di un pinguino siano correlate al sesso dello stesso.