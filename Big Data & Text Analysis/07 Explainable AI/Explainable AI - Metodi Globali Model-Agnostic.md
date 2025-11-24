## PDP (Partial Dependency Plot)

Il Partial Dependency Plot (PDP / PD Plot) mostra l'effetto marginale che una o 2 features hanno sulla predizione restituita da un modello ML.

$$
\hat{f}_{S} x_{S} = \frac{1}{N} \sum_{i=1}^{n} \hat{f} (x_{S}, x_{C}^{(i)})
$$

## PFI (Permutation Feature Importance)

La PFI misura l'aumento nell'errore di predizione del modello dopo aver permutato i valori di determinate features (scambio, sulla stessa colonna, il valore di righe a caso).
Questo errore non viene calcolato sul training ma sul test, così da non valutare il modello overfittato.

## LOCO (Leave-One-Covariate-Out)

La LOCO ha lo stesso obiettivo della [[#PFI (Permutation Feature Importance)|PFI]], ma si basa sulla rimozione della feature da analizzare.