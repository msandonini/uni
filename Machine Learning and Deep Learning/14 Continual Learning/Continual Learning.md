---
tags:
  - deep_learning
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

![[CL_Rehearsal_Approaches.png]]

The idea is, in a subsequent task, to call both images from the same batch and images from the replay buffer, so at every training iteration we revisit past data and re-optimize it within the memory buffer.

[[#Experience replay (ER)]] is an old, simple, yet surprisingly effective baseline for CL.
- Pros:
	- Simple and straightforward
- Cons:
	- Performance proportional to memory size
	- It may clash with privacy constraints

Rehearsal approaches are simple, but they are very prone to overfitting when the memory buffer is small.
### Experience Replay (ER)

ER stores a few old training samples within a small memory buffer $\mathcal{B}$  with fixed memory capacity.

![[CL_Experience_Replay.png]]

Indicating with $l$ the cross-entropy loss between the output $f_{\theta}$ and the true labels $y$, we have that:
$$
\mathcal{L}_{ER} = \mathbb{E}_{(x, y) \sim \mathcal{D}_{t}}[l(y, f_{\theta}(x))] + \mathbb{E}_{(x, y) \sim \mathcal{B}}[l(y, f_{\theta}(x))]
$$

- $\mathbb{E}_{(x, y) \sim \mathcal{D}_{t}}[l(y, f_{\theta}(x))]$ represents the current task, being the loss on a batch from the task
- $\mathbb{E}_{(x, y) \sim \mathcal{B}}[l(y, f_{\theta}(x))]$ represents the memory buffer, being the loss on a batch sampled from the memory buffer $\mathcal{B}$

![[CL_ER_Algorithm.png]]

#### Reservoir Sampling

Reservoir sampling provides an online strategy to construct the memory buffer.
In particular, it solves the problem of keeping some limited number $M$ of $N$ total items seen before with equal probability $\frac{M}{N}$ when you don’t know what number $N$ will be in advance.

![[CL_Reservoir_Sampling_algorithm.png]]

Due to its simplicity, [[#Experience Replay (ER)|ER]] is an ideal starting point to develop a strong CL method.
However, it is affected by some key issues: 
- ER repeatedly optimizes a relatively small buffer: possible overfitting problem
- Incrementally learning a sequence of classes implicitly biases the network towards newer tasks.

The solution to this is using [[Fine Tuning#Knowledge Distillation|Knowledge Distillation]], obtaining [[#Dark Experience Replay (DER)|Dark Experience Replay]].

### Dark Experience Replay (DER)

DER is an approach relying on [[dark knowledge]] for retaining past experiences.
As ER, it maintains a buffer $\mathcal{B}$ of past network responses; then, in addition to the loss of the current task $\mathcal{L}_{t_{c}}$, DER minimizes the $L^{2}$ distances between past and current outputs for buffer datapoints:
$$
\mathcal{L}_{t_{c}} + \alpha \mathbb{E}_{(x, z) \sim \mathcal{B}} [ \lvert \lvert z -h_{\theta} \rvert  \rvert^{2}_{2}  ]
$$

$\alpha \mathbb{E}_{(x, z) \sim \mathcal{B}} [ \lvert \lvert z -h_{\theta} \rvert  \rvert^{2}_{2}  ]$ represents the function regularization, being the MSE of current responses vs those stored in the memory buffer.


![[CL_DER.png]]

The logits stored into the memory buffer are not just proxies for the ground-truth labels, but have a deeper meaning.
Logits can be considered as secondary information since, by the fact they encode visual similarities and relations between classes, they are more informative than labels, and therefore carry out more insightful signal regarding past tasks.

DER++ is a variant of DER that also asks the learner to predict the ground truth labels for past examples.

## Rehearsal-free approaches

Rehearsal-free approaches are born to try finding a solution to some core issues of replay based models:
- They need an episodic memory buffer, which requires storing raw samples or feature embeddings from past tasks
- Storage cost grows with the number of tasks
- Privacy concerns

Rehearsal free approaches aim to avoid explicit storage of past data, to gain the following benefits:
- No storage
- Simpler training pipeline
- Lower resource footprint

### Recall Prompting

### L2P

![[CL_L2P.png]]
