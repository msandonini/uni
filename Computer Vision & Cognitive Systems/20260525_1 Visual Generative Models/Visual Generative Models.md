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

Recalling Bayes' rule:
$$
P(x|y) = \frac{P(y | x)}{P(y)}P(x)
$$
Where, at least from a theoretical point of view:
- $P(x|y)$ is the conditional generative model
- $P(y|x)$ is the discriminative model
- $P(y)$ is the prior over labels
- $P(x)$ is the unconditional generative model

Usually, when we talk about generative models, we talk about both conditional and unconditional models.

There are different types of generative models:
- Explicit density (can compute $P(x)$)
	- Tractable density (really compute $P(x)$)
		- Autoregressive
	- Approximate density (approximate $P(x)$)
		- [[Generative Models#Variational Autoencoders (VAE)|VAEs]]
- Implicit density (cannot compute $P(x)$)
	- Direct (can directly sample from $P(x)$)
		- [[Generative Models#Generative Adversarial Networks (GANs)|GANs]]
	- Indirect (approximate samples from $P(x)$)
		- Diffusion models
![[Pasted image 20260525093807.png]]

## Autoregressive models

The goal of autoregressive is to write down an explicit function for $p(x) = f(x, W)$.
Treating the image as a sequence of 8-bit subpixel values, we predict each subpixel as a classification among 256 values

The only issue is that we have too many pixels (a 1024x1024 image is a sequence of 3M subpixels), so it's too expensive.
The solution is to model as a sequence of tiles, not a sequence of subpixels.

Autoregressive Models directly maximize likelihood of training data:
$$
p_{\theta}(x) = \prod_{i=1}^{N}p_{\theta}(x_{i}|x_{1},\dots,x_{i-1})
$$

## Generative Adversarial Networks

GANs give up on modeling $p(x)$, but allows to draw samples from $p(x)$.

Having data $x_{i}$ drawn from distribution $p_{\text{data}}(x)$, we want to sample from $p_{\text{data}}$.
To do so, we introduce a latent variable $z$ with simple prior $p(z)$ (e.g. unit Gaussian), we sample $z \sim p(z)$, and pass it to a generator network $x = G(z)$.
$x$ is then a sample from the generator distribution $p_{G}$, so we want $p_{G} = p_{\text{data}}$.
![[Pasted image 20260525095626.png]]

To train a GAN we jointly train the generator G and discriminator D with a minmax game:
$$
\min_{\text{G}} \max_{\text{D}} (E_{x \sim p_{\text{data}}} [\log D(x)] + E_{z \sim p(z)}[\log(1 - D(G(z)))])
$$
![[Pasted image 20260525095923.png]]

This is one of the most difficult networks to train, as plotting the loss there's no way of knowing how it's progressing or not. 

When training D, we fix G:
![[Pasted image 20260525100604.png]]
- $E_{x \sim p_{\text{data}}}[\log D(x)]$ means that the discriminator wants $D(x) = 1$ for real data
- $\log(1-D(G(z)))$ means that the discriminator wants $D(x) = 0$ for fake data

At the same way, when training G, we fix D:
![[Pasted image 20260525100700.png]]
- $E_{x \sim p_{\text{data}}}[\log D(x)]$ does not depend on G
- $\log(1-D(G(z)))$ means that the generator wants $D(x) = 1$ for fake data

Generator G and discriminator D are both neural networks.
StyleGAN is a more complex architecture that injects noise via adaptive normalization.
![[Pasted image 20260525101443.png]]

GAN latent space is smooth.
This is not a forced behaviour but an emerging one, as during training we did not force it.
This also means that given latent vectors $z_{0}$ and $z_{1}$ we can interpolate between them: 
$$
\begin{align}
z_{t} &= tz_{0} + (1 - t)z_{1} \\
x_{t} &= G(z_{t})
\end{align}
$$

- Pros:
	- Simple formulation
	- Good image quality
- Cons:
	- No loss curve to look at
	- Unstable training
	- Hard to scale to big models + data

GANs are not so used anymore because it's difficult to scale up the architecture to bigger models.

## Diffusion models

Diffusion models are the current state of the art.
There are many different mathematical formalisms and tons of variance in terminology and notation between papers.

The starting point of diffusion models is picking a latent picture (a noise distribution $z \sim p_{\text{noise}}$, usually unit Gaussian).
![[Pasted image 20260525103930.png]]
Starting from this random image, we now train the network to de-noise it removing a little bit of noise: $f_{\theta}(x_{t}, t)$.
At inference time, we sample $x_{1} \sim p_{\text{noise}}$ and apply $f_{\theta}$ many times in sequence to generate a noiseless sample $x_{0}$.

### RectifiedFlow
Supposing we have a simple $p_{\text{noise}}$ and samples from $p_{\text{data}}$, on each training iteration, we sample:
$$
\begin{align}
z &\sim p_{\text{noise}} \\
x &\sim p_{\text{data}} \\
t &\sim \text{Uniform}[0, 1]
\end{align}
$$
![[Pasted image 20260525104509.png]]
Now, we set $x_{t} = (1-t)x + tz, v=z-x$, so we train a NN to predict v:
$$
L = \lvert \lvert f_{\theta}(x_{t}, t) - v \rvert  \rvert_{2}^{2} 
$$
The core training loop is just a few lines of code:
```python
for x in dataset:
	z = torch.randn_like(x)
	t = random.uniform(0, 1)
	xt = (1 - t) * x + t * z
	v = model(xt, t)
	loss = (z - x - v).square().sum()
```

At the same way, even the sampling is just a few lines of code:
```python
y = user_input()
sample = torch.randn(x_shape)
for t in torch.linspace(1, 0, num_steps):
	v = model(sample, y, t)
	sample = sample - v / num_steps
```

![[Pasted image 20260525164729.png]]

The major problem with this is that the user wants a high quality image, so this model is really heavy.

### Latent Diffusion Models (LDMs)

In reality, what gets used are latent diffusion models, where we train encoder and decoder to convert images to latents.
![[Pasted image 20260525164443.png]]
After this we train the diffusion model to remove noise from latents (here the encoder is frozen).
![[Pasted image 20260525165117.png]]

%% Questo è effettivamente un autoencoder, tutti gli altri visti nel corso no (il prof specifica perché in esame tutti sbagliano) %%

The training follows the VAE's training, typically with a very small KL prior weight.
The problem is that the decoder outputs are often blurry.
The solution to this is to add a discriminator:
![[Pasted image 20260525165248.png]]


