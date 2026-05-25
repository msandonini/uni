---
course: Computer Vision and Cognitive Systems
---
Visual Generative Models are basically models used for image generation.
Until now we used a supervised learning approach, where we had a $(x, y)$ tuple with $x$ being the data and $y$ the label.
From now, we start using unsupervised learning, where our input data is just $(x)$, so we don't have labels.
With this approach, we want to learn hidden structure in data.
![[Pasted image 20260525092458.png]]
Unsupervised learning is usually useful in clustering, dimensionality reduction, density estimation, etc...

Since in a generative model we learn a probability distribution $p(x)$, it requires to have deep understanding of the probability distribution of the dataset.
![[Pasted image 20260525092806.png]]

While with generative models w learn the probability distribution, with conditional generative models learn the probability distribution of the data given a specific condition.
![[Pasted image 20260525092936.png]]

Recalling Baye's rule:
$$
P(x|y) = \frac{P(y | x)}{P(y)}P(x)
$$
Where, at least from a theoretical point of view:
- $P(x|y)$ is the conditional generative model
- $P(y|x)$ is the discriminative model
- $P(y)$ is the prior over labels
- $P(x)$ is the unconditional generative model

Usually, when we talk about generative models, we talk about both conditional and unconditional models.
