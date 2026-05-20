---
course: Computer Vision and Cognitive Systems
---
The task of classifying images and video has two main problems: 
- we lose lots of information, as an image usually contains way more info than the one that the networks are able to extract (so the network is not descriptive enough)
- when we add the classes to the dataset we might miss some ones
These problems are described as **closed vocabulary** limitations:
![[Pasted image 20260518105431.png]]

%% 2026/05/20 %%
## CLIP (Learning Transferable Visual Models from Natural Language Supervision)

CLIP is based on 2 big ideas:
- Data
	- While prior vision datasets where in the form of $\mathcal{D}$={\<img\>, "dog"}, CLIP collects datasets of (image, text) pairs as $\mathcal{D}$={\<img\>, "a corgi wearing a Zorro cape and mask"}, so we change from a dataset describing each image with a single word to a dataset describing each image with a free-formed text
- Representation
	- If $\mathcal{D} = \{(I_{j}, T_{j})\}$ is the dataset, learn:
		1. An image encoder $f: \mathbb{R}^{H \times W \times 3} \to \mathbb{R}^{D}$
		2. A text encoder $g: \mathbb{R}^{M} \to \mathbb{R}^{D}$
		such that $f(I_{k})$ and $g(T_{l})$ are close for $k = l$ and are far away for $k \neq l$

This was nothing new theory-wise, as everything was already there, but CLIP was the first working model of this
