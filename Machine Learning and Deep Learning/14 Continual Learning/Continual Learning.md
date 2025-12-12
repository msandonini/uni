---
tags:
  - deep_learning
  - continual_learning
  - ewc
  - fim
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

## Fisher Information Matrix

There is a theoretical relation between the empirical Fisher Information Matrix (FIM) and the second derivative of the loss near a minimum.
Because of this, the FIM captures the curvature of the log likelihood function: a high Fisher information indicates that the log likelihood is sharply peaked there, so it would be inconvenient to modify the corresponding weight.


