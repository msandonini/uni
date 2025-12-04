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

Deep Ensembles rely on redundancy of representations to improve performance and robustness, but they are hard to deploy in production due to their high computational and memory requirements.
To solve this problem we can train a very large and complex model to simplify learning, and then distill its knowledge into a smaller efficient one