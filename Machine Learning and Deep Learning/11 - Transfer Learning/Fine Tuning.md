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


