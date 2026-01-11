---
tags:
  - big_data
  - explainable_ai
  - machine_learning
---

$$
y = \beta_{0} + \beta_{1}x_{1} + \dots + \beta_{p} x_{p} + \epsilon
$$
Un modello di regressione predice il target come una somma pesata delle feature di input

$\epsilon$ è l'errore, cioè la differenza tra [] e l'*encoding model*

Nella regressione lineare è semplice determinare l'errore perché è una semplice somma di pesi, e ha le seguenti proprietà:
- Linearità: fa si che la stima sia semplice e facilmente interpretabile
- Feature numeriche
- Feature binarie
- Feature categoriche: l'interpretazione dipende dal metodo di encoding
- Intercept ($\beta_{0}$): rappresenta l'outcome predetto quando tutte le features sono 0 e le features categoriche sono al livello di riferimento

$$
t_{\hat{\beta_{j}}} = \frac{\hat{\beta_{j}}}{\text{SE}(\hat{\beta_{j}})}
$$
$$
\text{SE}_{b_{i}} = \sqrt{ \sigma^{2} \cdot (X^T X)^{-1}_{ii} }
$$

Un effect plot mostra la combinazione di come la combinazione $\text{pesi} \times \text{feature value}$ influenzi le predizioni

$$
\text{effect}_{j}^{(i)} = w_{j} x_{j}^{(i)}
$$
Per le feature categoriche gli effetti possono essere riassunti in un singolo *boxplot*, mentre i plot dei pesi mostrano una riga per categoria