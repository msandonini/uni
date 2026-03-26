---
course: Machine Learning and Deep Learning
---
After local training each client $i = 1, \dots, M$ provides $\theta_{i} \in \mathbb{R}_{p}^{n}$ where $n_{p}$ is the number of parameters of the network, and $F_{i}=\in \mathbb{R}^{n_{p} x n_{p}}$ which is symmetric and positive semi-definite.
Assume a Gaussian posterior $\mathcal{N}(\theta_{i}, (F_{i}^{-1}))$ around every $\theta_{i}$. We want the parameter vector $\theta$ that maximizes the product of these $K$ independent posteriors, that is, the joint posterior distribution:
$$
\theta^{\star} = \arg \max_{\theta} \prod_{i=1}^{M} \lambda_{i} p(\theta | \theta_{i}, F_{i})
$$
which is equivalent to maximizing the sum of the logarithms of the posteriors:
$$
\theta^{\star} = \arg \max_{\theta} \sum_{i=1}^{M} \lambda_{i} \log p(\theta|\theta_{i}, F_{i})
$$
Since the posterior are modeled after a Gaussian distribution, where $F_{i}$ is its precision matrix, the objective takes the following form:
$$
\theta^{\star} = \arg \max_{\theta} \prod_{i=1}^{M} \lambda_{i} \exp \left\{  -\frac{1}{2}(\theta - \theta_{i}) F_{i}(\theta - \theta_{i}) \right\} = \sum_{i=1}^{M} \lambda_{i} \log\left(  \exp \left\{  -\frac{1}{2} (\theta - \theta_{i})^{T} F_{i}(\theta - \theta_{i})  \right\}  \right)
$$
1. Get rid of $\log$ and $\exp$. Because $\log(\cdot)$ is monotone,
$$
\theta^{\star} = \arg \max_{\theta} -\frac{1}{2} \sum_{i = 1}^{M} \lambda_{i} (\theta - \theta_{i})^{T} F_{i}(\theta - \theta_{i})
$$
Multiplying by -2 gives an equivalent minimization problem:
$$
\theta^{\star} = \arg \min_{\theta} \sum_{i=1}^{M} \lambda_{i} (\theta - \theta_{i})^{T} F_{i}(\theta - \theta_{i})
$$
2. Expand the quadratic forms
$$
\theta^{\star} = \arg \min_{\theta} \sum_{i=1}^{M} \lambda_{i} \theta^{T} F_{i}\theta - 2\lambda_{i} \theta^{T} F_{i} \theta_{i} + \lambda_{i} \theta_{i}^{T} F_{i} \theta_{i}
$$








