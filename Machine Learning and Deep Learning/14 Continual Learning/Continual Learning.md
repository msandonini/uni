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

## Fisher Information Matrix

There is a theoretical relation between the empirical Fisher Information Matrix (FIM) and the second derivative of the loss near a minimum.
Because of this, the FIM captures the curvature of the log likelihood function: a high Fisher information indicates that the log likelihood is sharply peaked there, so it would be inconvenient to modify the corresponding weight.

## Class Incremental Learning (Class-IL)

## Architectural Approaches

Architectural methods devote distinct sub-models / task-specific parameters for distinct tasks.

The main idea is based on adding new parameters tailored for the new tasks.
![[CL_Architectural_Approaches.png]]

## Regularization approaches

Regularization approaches add explicit regularization terms in the loss function to balance the old and new tasks.

They apply weight sharing across tasks and do not instantiate additional parameters, granting reduced memory footprint.
As an example, [[#Elastic Weight Consolidation|EWC]] already was a sort of regularization approach.
However, the auxiliary regularization objective usually requires to store a frozen copy of the old model for reference.

Depending on the target of regularization, such methods can be divided into 2 sub-directions:
- Weight regularization
	- These selectively regularize the variation of network parameters.
	- Examples of these are [[#Elastic Weight Consolidation|EWC]], [[#Synaptic Intelligence]], [[MAS]], RWalk
- Function regularization
	- These approaches target the intermediate or final output of the prediction function

![[CL_Regularization_Approaches.png]]

## Rehearsal Approaches

Rehearsal approaches store previously seen examples in a memory buffer and use them in later iterations.
[[#Experience replay (ER)]] is an old, simple, yet surprisingly effective baseline for CL.
- Pros:
	- Simple and straightforward
- Cons:
	- Performance proportional to memory size
	- It may clash with privacy constraints

![[CL_Rehearsal_Approaches.png]]

The idea is, in a subsequent task, to call both images from the same batch and images from the replay buffer, so at every training iteration we revisit past data and re-optimize it within the memory buffer.

### Experience Replay (ER)

