---
tags:
  - progettazione_software
---



%% 2025/10/31 - Recap lezione precedente %%

Un secondo elemento da prendere in considerazione è la corrispondenza tra il progetto che esaminiamo in progetto slim (termini di Putnam) e in [[Cocomo]]

Definiamo la Manpower buildup come $D_0$
- $D_{0} = 7.5$ - Progetto Real-Time con molte interfacce, molte interazioni esterne, in ambiente nuovo senza esperienza del team
- $D_0 = 15$ - Software con alcune interfacce, alcune interazioni esterne, e progetti interagenti tra loro
- $D_0 = 30$ - Software sequenziale con pochi rischi, o Real-Time easy
- $D_0 = 60$ - Software sequenziale con pochi rischi, team di sviluppo con esperienza

Nel caso il $D_0$ non sia perfettamente corrispondente a uno dei valori prestabiliti lo approssimiamo al più vicino (es. $D_0 = 10$ viene approssimato a $7.5$).

##### Equazione del software
$$
K_{d} = \frac{1}{6}\left( \frac{S}{E} \right)^3 (t_{d}^{-4})
$$
$$
\log K_{d} = \log\left[ \frac{1}{6} \left( \frac{S}{E} \right)^3 \right] - 4 \log(t_{d})
$$
##### Scelta di E
- Livello 1 - $E = 600$
- Livello 5 - $E = 9600$

Una volta nota la planning zone bisognerà rilasciare, uno alla volta, i vincoli, così da studiare cosa succede agli altri parametri