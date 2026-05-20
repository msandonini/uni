---
course: Computer Vision and Cognitive Systems
---
The task of classifying images and video has two main problems: 
- we lose lots of information, as an image usually contains way more info than the one that the networks are able to extract (so the network is not descriptive enough)
- when we add the classes to the dataset we might miss some ones
These problems are described as **closed vocabulary** limitations:
![[Pasted image 20260518105431.png]]

%% 2026/05/20 %%
## CLIP ([Learning Transferable Visual Models from Natural Language Supervision](https://arxiv.org/pdf/2103.00020))

CLIP was nothing new theory-wise, as everything was already there, but CLIP was the first model making it work.

This model is based on 2 big ideas:
- Data
	- While prior vision datasets where in the form of $\mathcal{D}$={\<img\>, "dog"}, CLIP collects datasets of (image, text) pairs as $\mathcal{D}$={\<img\>, "a corgi wearing a Zorro cape and mask"}, so we change from a dataset describing each image with a single word to a dataset describing each image with a free-formed text
- Representation
	- If $\mathcal{D} = \{(I_{j}, T_{j})\}$ is the dataset, learn:
		1. An image encoder $f: \mathbb{R}^{H \times W \times 3} \to \mathbb{R}^{D}$
		2. A text encoder $g: \mathbb{R}^{M} \to \mathbb{R}^{D}$
		such that $f(I_{k})$ and $g(T_{l})$ are close for $k = l$ and are far away for $k \neq l$
	- Basically, instead of a single encoder like before we learn 2 encoders which both project their results in a single shared embedding space

![[Pasted image 20260520124635.png]]

To merge the 2 vectors we use cosine similarity, so that all the numbers of the diagonal are close to 1 and the further we get from the diagonal the further the further we get from 1.

After computing the similarity we normalize with the soft-max and then we use cross-entropy to make this a classification problem.
For each row, the ground-truth for the row is the index of the row (so the ground truth for the row is basically the value that would be on the diagonal of the matrix).
The same thing is then done for each column.
This way we create an association between the text and the image
This process is called Contrastive loss or InfoNCE loss.

```python
def forward(self, image, text):
	image_features = self.encode_image(image) # (N, D)
	text_features = self.encode_text(text) # (N, D)
	
	# normalized features
	image_features = image_features / image_features.norm(dim=1, keepdim=True)
	text_features = text_features / text_features.norm(dim=1, keepdim=True)
	
	# cosine similarity as logits
	logit_scale = self.logit_scale.exp()
	logits = logit_scale * image_features @ text_features.t() # (N, N)
	
	# fill in the loss
	# Hint: use torch.arange and F.cross_entropy
	target = torch.arange(image_features.shape[0], device=image_features.device)
	loss_image = F.cross_entropy(logits, target)
	loss_text = F.cross_entropy(logits.t(), target)
	
	# average of the two
	loss = (loss_image + loss_text) / 2.0
	return loss 
```
%% This loss usually gets asked in work interviews %%

The visual features extracted this way are always better than the ones usually obtained by a normal classification task. This is because texts are more descriptive than single words, so each image is associated with way more information than it would be in the classification.


