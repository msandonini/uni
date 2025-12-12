---
tags:
  - deep_learning
  - continual_learning
---
A Continual Learning classification problem is split in $T$ tasks

## Elastic Weight Consolidation

$$
\mathcal{L}(\theta) = \mathcal{L}_{B}(\theta) + \sum_{i} \frac{\lambda}{2} F_{i} - (\theta_{i} - \theta^{\star}_{A, i})^{2}
$$

- $\theta_{i} - \theta^{\star}_{A, i}$ is the distance between parameters in the space
- $F_{i}$ is an estimate of how much each parameter is important for preserving the performance in task $A$
- $\lambda$ is an hyper-parameter

The idea is to modulate the distance according to the importance


