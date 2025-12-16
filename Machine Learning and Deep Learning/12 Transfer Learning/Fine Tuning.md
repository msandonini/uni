---
tags:
  - deep_learning
  - fine_tuning
  - transfer_learning
  - ensemble
---
Question: why is it now rare to train a NN from scratch, but instead everyone relies on fine-tuning of pre-trained models?
- Performance
	- Fine tuning often outperforms training from scratch, especially in data-scarce scenarios
- Computational constraints
	- Training a NN from scratch, especially with lots of training data, is very computationally difficult
- Data availability
	- Large-scale datasets required for training from scratch are not always easily accessible, and not always a dataset will be big enough to grant better performances than the previous model

![[fine_tuning_effectiveness.png]]

As seen in the image below, if we have big datasets training from scratch is still better than fine tuning, but basically in low data regimes we get better performances with fine tuning:
![[fine_tuning_low_data_regime.png]]

Also, as shown in the image below, fine-tuned models are characterized from a faster performance convergence:
![[fine_tuning_convergence.png]]

So, why did fine tuning become so popular?
Basically, because of [Hugging Face](huggingface.co), which provides pre-trained weights that can be fine tuned to be adapted to new tasks with minimal additional training. This avoids the massive computational cost of training from scratch.

Even with fine-tuning there are different ways to perform it

## Freezing layers
Earlier layers often capture low-level features (e.g. edges, textures, etc...) that can be reused (so they can be frozen in order to fine-tune only the later layers)

Freezing layers do grant different pros:
- Reduces computation, since less memory and gradient FLOPs need to be used
- Preserves generalization given by the low-level features learned in the source task, reducing the risk of overfitting
- Grants faster convergence, since I need to train less (and so I get faster training times)
- Grants stability, since it prevents hurting the earlier more generic representations
![[fine_tuning_freeze.png]]

- Linear Probing (last layer only)
	- Fast layer adaptation
	- Low risk of overfitting
	- Limited flexibility
- Last N layers
	- Compromise between adaptation capacity and risk of overfitting
- All layers
	- Maximum flexibility
	- High computational costs
	- High risk of overfitting
Linear probing is often used in the literature as a quick tool to assess how good the features of a frozen backbone are for a downstream task.

## Learning Rate Strategies

During fine tuning I can use 3 different strategies to decide the learning rate:
- Uniform learning rate: apply same learning rate to all trainable layers
	- Pros: simple and easy to implement
	- Cons: can be sub-optimal, since some layers can be over-updated while others could be under-updated
- Layer specific learning rate: use larger LR for the last (task-specific) layers and smaller LR for earlier layers
	- Helps adapt high-level features quickly while preserving low-level representations.
	- Also known as *Slow Learner*
- Warmup schedules: gradually increase LR during initial iterations to avoid disrupting pre-trained weights
	- useful when updating al layers

## LP-FT

An alternative strategy is the LP-FT (Linear Probing + Fine Tuning):
1. Freeze the pre-trained backbone and train only a linear classifier (Linear Probing)
2. Fine tune the whole network starting from the adapted classifier

This strategy works since when training the linear classifier I assume the features space is already optimized, and so by freezing the classifier I obtain just light-adaptations.

## BatchNorm

In some settings, while the weights of the network are kept frozen, the [[BatchNorm]] statistics are updated to match the target domain, so only the running mean and variance of BatchNorm layers are updated, while the learnable parameters $\gamma$ (scale) and $\beta$ (shift) can remain fixed or be updated. This is equivalent to running one epoch with [[SGD]] and $\text{lr} = 0$.
This approach is widely applied in domain adaptation to align source and target features distributions.

## Limitations

Some limitation of fine-tuning are: 
- Architectural rigidity
- Dependence on external data
- Inherited biases
An example of inherited bias can be seen in the image below, where the models are very biased toward textures:
![[fine_tuning_bias_texture.png]]
Another limitation of fine tuning is the Model Storage since we need to store a full copy of the fine-tuned model for each downstream task

# Teacher-Student techniques

In high-data regime, the more layers we have, the more complex patterns and abstractions the network can learn, generally leading to better performance.

## Deep Ensembles
An idea to improve the learning is to apply [[Bagging]], so to create Deep Ensembles:
- Train multiple independent models with different random initializations and data shuffling
- Each model converges to a different local minimum, all consistent with the data

## Knowledge Distillation
Deep Ensembles rely on redundancy of representations to improve performance and robustness, but they are hard to deploy in production due to their high computational and memory requirements.
To solve this problem we can train a very large and complex model to simplify learning, and then distill its knowledge into a smaller efficient one.

With knowledge distillation we train a smaller student to mimic the output distribution of a larger teacher model.
![[fine_tuning_teacher_student.png]]
With this strategy the teacher produces logits $z_{i}$ for each class $i$, and then apply a softmax with temperature $T>1$:
$$
p_{i}^{(T)} = \frac{\exp\left( \frac{z_{i}}{T} \right)}{\sum_{j} \exp\left( \frac{z_{j}}{T} \right)}
$$

The training procedure of knowledge distillation is the following:
1. Make a forward pass with the teacher to obtain teacher logits $z_t$.
2. Make a forward pass with the student to obtain student logits $z_s$.
3. Update student parameters to minimize the following mixed loss function combining:
	- Fidelity to true labels: cross-entropy with $y$.
	- Fidelity to teacher outputs: cross-entropy with softened teacher probabilities.
$$
\mathcal{L}_{\text{student}} = \alpha \cdot \mathcal{L}_{\text{CE}}(y, \sigma(z_{s})) + (1 - \alpha) \cdot T^{2} \cdot \mathcal{L}_{\text{CE}} \left( \sigma\left( \frac{z_{t}}{T} \right), \sigma \left( \frac{z_{s}}{T} \right) \right)
$$
Empirically, incorporating soft targets typically improves performance over relying solely on hard (one-hot) labels. This is so effective because of [[dark knowledge]] (information contained in the relative probabilities of the non-argmax classes), which is secondary information which can help the student to learn richer decision boundaries than one-hot labels allow, and also acts as some guidelines, preventing the student from overfitting.

Application of Knowledge Distillation are:
- Model compression
- Cross-architecture transfer: distill from a CNN into a transformer or vice versa, to leverage strengths of different architectures
- Domain adaptation
- Regularization in training

### Similarity-Preserving Knowledge Distillation (SP KD)

SP KD is a KD technique where instead of matching only the output logits of teacher and student we also preserve the pairwise similarities between samples in the features space
$$
\mathcal{L}_{\text{SP}} = \lvert \lvert S^{T} - S^{S} \rvert \rvert^{2}_{F}
$$

### Attention Transfer (AT)

AT is a  technique where instead of directly matching feature maps, we transfer the spacial attention maps from the teacher to the student.

- Extract attention maps $A_T$ and $A_S$ from teacher and students:
$$
A = \frac{1}{C} \sum_{c = 1}^{C} |F_{c}|^{p}
$$
	- $F_c$ is the $c$-th feature channel and $p \in \{ 1, 2 \}$
- Normalize each attention map to unit norm
- Minimize:
$$
\mathcal{L}_{\text{AT}} = \lvert \lvert \hat{A}_{T} - \hat{A}_{S} \rvert  \rvert^{2}_{2}
$$
- Combine with standard CE or KD loss

### FitNets

FitNets extend naive KD by also transferring intermediate feature representations from teacher to student, not just the final output logits

### Self-KD

Self-KD is a technique where we apply KD between 2 networks with the same architecture. The difference between teacher and student lies in the input information, not in model size.

The setup is like this:
- Teacher: trained on richer or more informative inputs.
- Student: trained on degraded, partial, or noisier inputs.
- Distillation loss encourages the student to match the teacher’s intermediate features or final predictions.

This grants some benefits:
- Shifts the learning challenge from model capacity to input efficiency.
- Student can surpass the teacher by learning to extract more discriminative patterns from limited information.
- Useful in scenarios with missing modalities or partial observations.

