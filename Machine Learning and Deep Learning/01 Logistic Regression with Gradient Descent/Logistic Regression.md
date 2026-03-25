---
course: Machine Learning and Deep Learning
---
*Logistic Regression* is a **probabilistic discriminative classifier**.

In the **binary case**, it directly models the posterior probability as:
$$
P(Y=0 | x) = \frac{e^{w^{T} x + b}}{1 + e^{w^{T} x + b}}
$$
$$
P(Y=1|x) = \frac{1}{1 + e^{w^{T} x + b}}
$$

By computing the decision boundary the classifier is proven **linear**:
$$
\log P(Y=0|x) - \log P(Y=1|x) = w^T x + b
$$
The classification function is $f_{LR}(x)=\arg \max_{c \in \gamma} P(Y=c|x)$

## Multiclass Logistic Regression

LR can also be extended to the multiclass case with K classes.

$$
P(Y=c|x) = \frac{\exp(w^T_{c} x + b_{c})}{1 + \sum_{l=1}^{k-1} \exp (w^T_{l} x + b_{l})}
$$
$$
P(Y=K|x) = \frac{1}{{1 + \sum_{l=1}^{k-1} \exp (w^T_{l} x + b_{l})}}
$$
The classification function is still $f_{LR}(x)=\arg \max_{c \in \gamma} P(Y=c|x)$

## Learning

The logistic regression parameters $\theta = (w_{c}, b_{c}), c \in \gamma$ are selected to optimize the conditional logarithmic likelihood of the tables given a dataset $D = \{ (x_{i}, y_{i}), i = 1 : n \}$:
$$
\theta_{*} = \arg \max_{\theta} \mathcal{L}(\theta, D) = \arg \max_{\theta} \sum_{i=1}^n \log P(Y=y_{i}|X=x_{i})
$$
However, the function $\mathcal{L} (\theta | D)$ can not be maximized analytically. Learning the model parameters requires numerical optimization methods.

We need to learn a function that maps X to Y such that it works well on the training set. To do so, we need to learn the parameters **w** of a parametric function that maps X to Y such that **some error** is **as low as possible** on the training set.

The function for classification has the following form:
$F(X_{i}, w) = \sigma(w^T \cdot X_{i}), \text{where } \sigma(x) = \frac{1}{1 + e^{-x}} = \frac{e^x}{1 + e^x}$
