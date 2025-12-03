%% N.B. Il prof ha raccolto le pere ma in miniera non ci è mai andato %%

L'input di un [[Transformer]] è composto da un embedding che rappresenta i token contestualmente alla posizione nella frase.

Il blocco di un transformer funziona tramite un meccanismo di self-attention, che permette al modello di differenziare l'importanza di ogni token all'interno della frase.

Un sistema basato su [[Causal self-attention]] (anche chiamata [[Backward looking self-attention]]) funziona determinando il valore di attention della parola attuale indipendentemente dal valore di attention delle precedenti, così che i valori di attention diversi possano essere calcolati in parallelo.
