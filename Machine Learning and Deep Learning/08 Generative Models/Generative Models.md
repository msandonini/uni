---
tags:
  - deep_learning
  - generative_models
---
%% 2025/11/11 %%

*Generative modeling* is a area of ML which deals with models of distributions $p(x)$, defined over datapoints $x$ in some potentially high-dimensional space $\chi$

In the case of images, $x$ values which look like real images should get high probability, with the aim of synthetizing new images similar to those already in the dataset, but without being the same.

Why are these models important? 
- Creation of new samples to be used for other algorithms' training
- Compute the probability of a sample being of a certain specified class, so it can be used for anomaly detection

## Variational Autoencoders (VAE)

Denoising autoencoders and contractive autoencoders can implicitly learn the structure of probability distribution $p(x)$.

To model the distribution of data, the first idea would be to use the normal (gaussian) distribution $\mathcal{N}(x|\mu, \Sigma)$.
In the case of images, this cannot be applied to images, since images are a more complex set of data compared to the just numerical ones, since an image of the same object could have way more variables (e.g. colors, position, angle, race of an animal, etc...).

A common thing in the engineering fields, when working with difficult data, is to not change the function but change the space instead. 
Practically, the solution is to go from our space $X$ to a new space $Z$ where we can use the gaussian distribution.

### Latent Variable Models

The idea of *Latent Variable Models* is to relate a set of observable variables to a set of latent variables, so to relate a new variable $z$, in a different system of coordinates, to our original input $x$.

![[Latent_Variable_Models.png]]

Basically, our new $z$ variables represent hidden quantities learned from $x$, like relations between some values.

$$
p(x) = \int p(x, z) dz = \int p(x|z) p(z) dz
$$
This integral is often **intractable** to compute in closed form, since we have infinite possible solutions.
This kind of intractable integral is one of the iconic problems in Bayesian statistics, probabilistic ml, and graphical models.
One possible solution is to use a **Monte Carlo approximation**:
$$
p(x) \approx \frac{1}{K} \sum_{k=1}^{K} p(x|z^{(k)}), z^{(k)} \sim p(z) 
$$
**Sampling procedure**:
- Sample $z \sim p(z)$
- Sample $x \sim p(x|z)$
- Apply Monte Carlo approximation

### Variational Inference

Having the Monte Carlo approximation, the problem is now choosing which $z$ to use.
What we need is a sort of *proposal distribution* (a phantomatic distribution which gives us the best $z$ values to reconstruct our function), so we now need to learn $q(z|x)$ such that it approximates well the *true* distribution $p(z|x)$ using a simpler distribution that is easy to evaluate.
$$
q^*(z|x) = \arg \min_{q} D_{KL}[q(z|x) || p(z|x)]
$$
This is hard since directly minimizing the $KL$ divergence requires computing $\log p(x)$, which is generally impossible for complex generative models, so this is now an optimization problem.

We want the $q^*(z|x)$ which is the solution of our optimization problem.
We start by rewriting the $\min$'s argument.
$$
* = E [\log q(z|x) - \log p(z|x)]
$$
- $D_{KL}$ is the logarithm

By definition $p(z|x) = \frac{p(x, z)}{p(x)}$, and by the same definition $p(x|z) = \frac{p(x,z)}{p(z)}$
So, we can say that $p(x, z) = p(x|z)p(z)$, which makes it so that $p(z|x) = \frac{p(x|z)p(z)}{p(x)}$
$$
* = E \left[ \log q(z|x) - \log \frac{p(x|z)p(z)}{p(x)} \right]
$$
By logarithm's properties we can then say that:
$$
* = E [\log q(z|x) - \log p(x|z) - \log p(z) + \log p(x)]
$$

By expected value's ($E$) properties, $E[a + b] = E[a] + E[b]$, so we can rewrite like this:
$$
* = E[\log q(z|x)] - E[\log p(x|z)] - E[\log p(z)] + E[\log p(x)]
$$
Now we can focus on just $\log p(x)$, which we can remove from the expected value since it's not dependent on $z$:
$$
E[\log p(x)] = \log p(x)
$$
$$
* = E[\log q(z|x)] - E[\log p(x|z)] - E[\log p(z)] + \log p(x)
$$
$$
* = KL(q(z|x) || p(z)) - E[\log p(x|z) + \log p(x)]
$$
$$
\log p(x) - D_{KL}[q(z|x)||p] = E[\log P(x|z)] - KL(q(z|x)||p(z))
$$
We call the $E[\log P(x|z)] - KL(q(z|x)||p(z))$ quantity ELBO (Evidence Lower BOund), and it is the value which represents the lower bound of the $KL$ divergence.

Instead of minimizing the divergence delta, I can maximize the ELBO.

### Variational Autoencoder (VAE)

A **Variational Autoencoder (VAE)** is an autoencoder trained to maximize the Evidence Lower Bound (ELBO), and it is composed of the following components:
- Encoder network $q_{\phi}(z|x)$
- Decoder network $p_{\theta}(x|z)$

A key difference from a standard AE is that the VAE's encoder does not output a deterministic vector, but the parameters (mean and variance) of a latent distribution.

The loss function of a VAE is the following:
$$
\mathbb{E}_{z \sim q_{\phi} (z|x)} [\log p_{\theta}(x|z)] - D_{KL} [q_{\phi}(z|x) || p(z)]
$$
- This loss subtracts the regularization term (which is our $D_{KL}$) from the reconstruction term.

![[VAE_Architecture.png]]

New problem: how can we sample new images?
- If all training as gone well, the posterior distribution is very similar to the prior, so we can discard the encoder and sample from the prior, so it can generate new images by picking new samples from the prior and pass it to the decoder

Also, we can use the VAE to process the $\log p(x)$, making it useful in Anomaly Detection

Problem: the sampling step $z \sim \mathcal{N}(z|\mu(x), \sigma^2(x))$ is not differentiable.
To solve this we use a trick called *reparametrization trick*, which performs a shift operation and then scales it based on mean and variance
$$
z = \mu+\sigma^2\epsilon
$$

%% 2025/11/13 %%
### Generative Adversarial Networks (GANs)

The objective of GANs is to create a network whose output is a bit less blurry than VAEs

Adversarial means that the neural networks compute against each other

Limitation of VAEs:
- Use latent variables $z$, optimize a lower bound on likelihood
- Ofte produce blurry reconstructions

GANs:
- No explicit density function
- Learn to mapi noise $z \sim p(z)$ directly to real data distribution via adversarial training

Basically:
- If I want something that is just good, VAEs are ok
- If I want something with high variance, I need to use GANs



> [!NOTE] Core Idea
> Sample from simplle noise distribution $z \sim p(z)$
> 
> Learn transformation $G(z) \to$ Real data distribution

Basically what we focus on here is the decoder part modeling, so we start from a random vector and we then train a NN to transform it into an image

#### GAN Idea
- Generator: team of counterfeiters, trying to fool police with fake currency
- Discriminator: police, trying to detect the counterfeit currency

*Competition* is what drives **both** teams to improve their models until the counterfeits are indistinguishable from the genuine articles.
This is basically a binary classification problem, where the 2 classes are "real" and "fake".


The *generator* network directly produces samples $x=G(z)$
The *discriminator* network tries to distinguish the fake data from the real one

As long as the discriminator improves, also the generators will improve

#### Architecture

The discriminator emits a probability value indicating whether x is a real training example rather than a fake one.

In terms of loss function we obtain something like this:
$$
\min_{\theta_{g}} \max_{\theta_{d}} [\mathbb{E}_{x \sim p_{data}} \log D_{\theta_{d}} (x) + \mathbb{E}_{z \sim p(z)} \log(1 - D_{\theta_{d}}(G_{\theta_{d}}(z)))]
$$
This loss is different from the previous ones since this needs to combine the losses of 2 separate networks, which are said to *train jointly* in a **minmax game**.

So, the point is that with gradient descent we know how to minimize the function but not how to maximize it, so we alternate 2 steps:
- Gradient ascent on discriminator
$$
\max_{\theta_{d}} [ \mathbb{E} \sim p_{data} \log D_{\theta d}(x) + \mathbb{E}_{z \sim p(z)} \log (1 - D_{\theta_{d}}(G_{\theta_{g}}(z))) ]
$$
- Gradient descent on generator
$$
\min_{\theta_{g}}[\mathbb{E}_{z \sim p(z)} \log(1 - D_{\theta_{d}}(G_{\theta_{g}}(z)))]
$$

N.B.: $\theta_{b}$ and $\theta_{g}$ are 2 different parameters

Problem: In this model we have the exact opposite problem of the exploding gradient: the **vanishing gradient**.
This is born by the fact that if the discriminator is too good and the generator is not yet producing realistic samples, the generator will receive very small gradients, leading to vanishing gradient

Solution: instead of minimizing $\log(1 - D(G(z)))$ we can maximize $\log(D(G(z)))$

The latent space of the GAN (hidden layer of the generator) can be combined with each others, so we can apply sort of arithmetic operations to the images to create the output we want.

Different loss functions and architectures have been proposed to improve GANs:
- LSGAN
- Wasserstein GAN
- CycleGAN
	- Able to produce unpaired image-to-image translation
	- This is based on a mechanism called *Cycle Consistency* (a property which implies that there must not be correspondence between a photo and a drawing), which makes it possible for example to convert a drawing into a photo and vice-versa
- Progressive GANs
	- Born from the problem that training on high-res images is very computationally difficult
	- Works by training at a low resolution and progressively growing generator and discriminator to higher resolutions.
![[Progressive_GANs.png]]
- StyleGANs (1, 2, and 3)
	- Paper from Nvidia
	- Introduced a style-based generator architecture, allowing for fine control over generated image attributes
	- This is a normal GAN which uses a modified batch normalization function called AdaIN
		- The AdaIN function is a batch normalization function which accepts an additional input from a network which characterize the style of the image, making the batch normalization formula something like $\text{AdaIN}(y) = y_{S} \frac{x - M_{b}}{\sigma_{b}} + y_{b}$
![[Style_GANs.png]]

#### Pros and Cons

Pros:
- Can use backpropagation
- Loss function is learned instead of being hand selected
- No MCMC needed
Cons:
- Hard to train since it's less stable
- Need to manually babysit during training
- No evaluation metric, so it's harder to compare with other models
