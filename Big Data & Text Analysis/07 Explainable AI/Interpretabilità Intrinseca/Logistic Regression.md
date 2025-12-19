---
tags:
  - big_data
  - explainable_ai
  - logreg
  - deep_learning
---

L'interpretazione della [[0_Logistic Regression with Gradient Descent|Logistic Regression]] viene costruita in base al rapporto chiamato *odds*, ovvero la proprietà dell'evento divisa il suo opposto:
$$
\begin{align}

\ln\left( \frac{\mathbb{P}(Y = 1)}{1 - \mathbb{P}(Y=1)} \right) &= \ln\left( \frac{\mathbb{P}(Y=1)}{\mathbb{P}(Y=0)} \right) &= \beta_{0} + \beta_{1} x_{1} + \dots + \beta_{p} x_{p} \\
\frac{\mathbb{P}(Y = 1)}{1 - \mathbb{P}(Y=1)} &= \text{odds} &= \exp(\beta_{0} + \beta_{1} x_{1} + \dots + \beta_{p} x_{p}) \\
\frac{\text{odds}_{x_{j} + 1}}{\text{odds}_{x_{j}}} &= \frac{\exp(\beta_{0} + b_{1} x_{1} + \dots + \beta_{j} + (x_{j}+1) + \dots + \beta_{p} x_{p})}{\exp(\beta_{0} + \beta_{1} x_{1} + \dots + \beta_{j} x_{j} + \dots + \beta_{p} x_{p})} \\
\frac{\exp(a)}{\exp(b)} &= \exp(a - b) \\
\frac{\text{odds}_{x_{j} + 1}}{\text{odds}_{x_{j}}} &= \exp(\beta_{j}(x_{j} + 1) - \beta_{j} x_{j})

\end{align}
$$
In sostanza abbiamo una feature con la sua importanza. Aumentiamo la feature di un grado (aumentandone quindi la probabilità), e osserviamo la variazione nel suo peso, capendo dunque la sua importanza.
