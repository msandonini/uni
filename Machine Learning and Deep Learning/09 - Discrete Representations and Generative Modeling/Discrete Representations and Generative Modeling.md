%% 2025/11/13 %%

Most of the times the world is both continuous and discrete, so the problem now becomes the discretization of the space, since even when we observe a continuous phenomenon, we tend to discretize it (so to divide it into distinct parts) in order to simplify it. An example is the alphabet.

This is a problem because until now we always used as loss the gradient descent, which is based on a derivative, which in turn relies on the fact that the input is a continuous function.
Basically, from now on, we will need to trick the gradient into thinking that our discrete input is a continuous one.

%% 2025/11/18  %%

The reason we want discrete models and representations is that they enable:
- Efficient compression
- Symbolic reasoning
- Modular design
	- The meaning of this is that we can consider our NNs as modules, with different transformations for each node
	- This enables us to select just some parts of our model during the forward pass

Problem: in a discrete space we cannot compute the derivatives, so we can't use the gradient descent we used to optimize models until now:
$$
r'=\text{quantize}(r \in \mathbb{R})
$$
This operation is not differentiable. What if I want to compare $r'$ to its ground truth $y$? What metric can I use?

Another problem:
```python
import torch

query = torch.randn(1,4, require_grad=True)    # shape: (1, dim)
keys = torch.randn(5, 4)                       # shape: (num_keys, dim)

# Values to be selected
values = torch.tensor([[10.0], [20.0], [30.0], [40.0], [50.0]])        # shape: (5, 1)

# Compute attention scores
scores = torch.matmul(keys, query.T).squeeze() # shape: (5,)

# Hard selection: non differentiable
selected_index = torch.argmax(scores)          # returns an integer index
selected_value = values[selected_index]        # detached from query

# Loss
loss = selected_value ** 2
loss.backward()
```
Here the problem is that `argmax` is not differentiable, so the backward pass will give an error

Some solutions to this problem are:
- VQ-VAEs (Vector Quantized Variational Autoencoders)
	- Involve straight-through estimators
- Pixel-RNN
	- Employs aggressive training
- Surrogate gradients (e.g. Gumbel Softmax)

## Vector Quantized Variational Autoencoders (VQ-VAEs)

In general terms, [[Generative Models#Variational Autoencoders (VAE)|VAEs]] have a tendency to generate blurry, unrealistic outputs.
The problem here is *mode collapse* (or *posterior collapse*), which means that the encoder's variational posterior quickly collapses to the prior distribution.
Solutions:
- $\beta$-VAE by \[4\]
	- introduces a hyper-parameter $\beta$ to weigh the importance of the KL divergence within the ELBO objective:
$$
E_{z \sim Q(z | X)} [\log P(X|z)] - \beta D_{KL} [Q(z|X) \parallel P(z)]
$$
- VQ-VAE
	- The idea is to extract a discrete representation from the original image
	- The output of the VQ-VAE's encoder is a grid of discrete symbols, and the decoder will take this map of symbols and will try to extract the original data

### Architecture

Differently from VAEs, the latent embedding space does not follow a Gaussian distribution.
![[VQ_VAE_Architecture.png]]
The model takes an input $x$, that is passed through an encoder network obtaining a continuous output $z_{e}(x)$.

The latent space is defined through a *learnable* lookup table (*codebook*) $e \in \mathbb{R}^{K \times D}$, where $K$ is discrete latent space size and $D$ is the dimensionality of each latent embedding vector. Hence, the codebook is $K \times D$.
Each of the $K$ embedding vectors $e_{i} \in \mathbb{R}^{D}, i=1, 2, \dots, K$ is learnable through gradient descent.

Given $z_{e}(x)$, the discrete latent variables $z$ is computed by a nearest neighbour look-up using the shared embedding space.
$$
q(z=k|x)= \begin{align}
1 \text{ if } &  k = \arg \min_{j} \parallel z_{e}(x) - e_{j} \parallel_{2} \\
0 \text{ otherwise}
\end{align}
$$

The proposal distribution $q(z = k|x)$ is deterministic.

Given $z_e(x)$, the discrete latent variables $z_q(x)$ is computed by a nearest neighbour look-up using the shared embedding space.

The input to the decoder is the corresponding embedding vector $e_k$.
$$
z_{q}(x) = e_{k}, \text{ where } k = \arg \min_{j} \parallel z_{e}(x) - e_{j} \parallel_{2}
$$
The complete set of parameters are union of parameters of the encoder, decoder, and the embedding space $e$.

![[VQ_VAE_Overall.png]]

The forward computation pipeline can be seen as a regular autoencoder with a particular non-linearity that maps the latents to 1-of-K embedding vector.
Such operation is *not differentiable* and would, as such, break the gradient flow.
The solution is the straight-through gradient estimation. With this method, the gradients are approximated by just copying the gradients from the decoder input $z_q(x)$ to the encoder output $z_e(x)$.

In general terms, the *Straight-Through Estimator (STE)* allows training by:
- Using the discrete output in the forward pass
$$
\text{forward: } z_{q} = \text{quantize}(z_{e})
$$
- Backpropagating gradients as if the operation were the identity
$$
\text{backward: } \frac{\partial L}{\partial z_{e}} \approx \frac{\partial L}{\partial z_{q}}
$$
Problem: due to the straight-through gradient estimation, the embeddings $e_i$ receive no gradients from the reconstruction loss $\log p(z|z_{q}(x))$.
To learn the embedding space, VQ-VAEs use the simplest dictionary learning algorithms, the *Vector Quantisation (VQ)*.
$$
L = \log p(x|z_{q}(x)) + \parallel \text{stopgrad}[z_{e}(x)] - z_{q}(x) \parallel_{2}^{2} + \beta \parallel z_{e}(x) - \text{stopgrad}[z_{q}(x)] \parallel_{2}^{2}
$$
Where:
- $\log p(x|z_{q}(x))$ is the reconstruction error
- $\parallel \text{stopgrad}[z_{e}(x)] - z_{q}(x) \parallel_{2}^{2}$ is the Vector Quantisation
- $\beta \parallel z_{e}(x) - \text{stopgrad}[z_{q}(x)] \parallel_{2}^{2}$ is the commitment term

The decoder optimises only the first loss term, while the encoder optimises the first and the last loss terms, and the lookup is optimised by the middle loss term.
The second term encourages the codeword to be as close as possible to the latent vector, while the third one encourages the encoder to be committed to the chosen codeword.

N.B.: $\text{stopgrad}[\cdot]$ stands for the stop gradient operator: it constraints its operand to be a *non-updated constant* during backpropagation

$$
\begin{align}
1: & \textbf{Input: } \text{input } x, \text{encoder } E(\cdot), \text{decoder } D(\cdot), \text{codebook } \{e_k\}_{k=1}^K \\
2 & z_e \leftarrow E(x) & \text{\# Encode input} \\
3 & k \leftarrow \arg \min_j \|z_e - e_j\|^2 & \text{\# Nearest codebook entry} \\
4 & z_q \leftarrow e_k & \text{\# Quantized latent} \\
5 & z_q^{\text{st}} \leftarrow z_e + \text{detach}(z_q - z_e) & \textbf{\# } \color{red}{\text{Straight-Through Estimator}} \\
6 & \hat{x} \leftarrow D(z_q^{\text{st}}) & \text{\# Reconstruct} \\
7 & \mathcal{L}_{\text{rec}} \leftarrow \|x - \hat{x}\|^2 & \text{\# Reconstruction loss} \\
8 & \mathcal{L}_{\text{codebook}} \leftarrow \|\text{stopgrad}[z_e] - z_q\|^2 \\
9 & \mathcal{L}_{\text{commit}} \leftarrow \|z_e - \text{stopgrad}[z_q]\|^2 \\
10 & \mathcal{L} \leftarrow \mathcal{L}_{\text{rec}} + \mathcal{L}_{\text{codebook}} + \beta \mathcal{L}_{\text{commit}} \\
11 & \text{Backpropagate and update model and codebook} &
\end{align}
$$

$$
z_{q}^{st} = z_{e} + \text{detach} (z_{q} - z_{e})
$$
Interpretation:
- Forward: $z_{q}^{st} = z_{q}$ (quantization is performed)
- Backward: Gradients flow only through $z_e$ (gradients are not affected by quantization)
- Effectively treats quantization as the identity function during backpropagation

VQ-VAE can be used as a *learned image compressor*:
- The encoder maps input images to discrete latent codes
- The decoder reconstructs the image from those codes
- The codebook indices can be compressed by using entropy coding

Advantages of using VQ-VAEs as such are the facts that VQ-VAEs learn domain-specific features, outperforming handcrafted codecs at low bitrates, and generating visually coherent reconstructions using fewer bits.

The problem with VQ-VAE is that it learns an encoder, a decoder, and a codebook of learnable embeddings, but it does not learn a prior over the latent codes, and so we can reconstruct inputs but cannot easily generate new samples.

The solution to this problem is to learn a prior over the discrete latent space (*learned prior*), so instead of sampling directly from the discrete latent space (not doable since we don't know its distribution) we first learn this distribution with another generative model, and we can then sample from this learned prior and use the VQ-VAE decoder to generate realistic new data.

## Autoregressive models (PixelCNN)

PixelCNN is an autoregressive model that can learn from a sequence of $K$ discrete symbols.

> [!NOTE] Autoregressive
> An autoregressive note is a model that can be factorized by 

With the VQ-VAE model, we have a set of training examples

We need to learn a generative model (*learned prior*) on top of these codes


**Idea**: Cast the joint density as a product of conditional distribution

**Chain rule of probability**: The prior $p_{\theta_{z}} (z)$ over discrete latent codes can be learned using an autoregressive factorization of the joint density: 
$$
p_{\theta_{z}} (z) = \prod_{t=1}^{T} p_{\theta_{z}} (z_{t_{0} | z_{<t}})
$$
Each latent code $z_t$ is predicted conditioned on all previous ones in the sequence.

**Conclusion**: The joint distribution can be written as a product of conditionals, and this forms the basis of autoregressive generative models.

Each latent variable $z_t$ is a discrete symbol from a codebook of size $K$, and each conditional can be modeled as a categorical distribution:

$$
p_{\theta_{z}} (z_{t} | z_{<t}) = \text{Cat} (z_{t}; \pi_{\theta_{z}} (z_{<t})), z_{t} \in \{1, \dots, k\}
$$
where $\pi_{\theta_{z}} (z_{<t}) \in \Delta^{K-1}$ is the predicted probability vector over each entry of the codebook, which can be parameterized by a NN.

Common choices for $p_{\theta_{z}}$:
- Pixel RNNs
- PixelCNN
- Transformers

Here we will focus on PixelCNN

### PixelCNN

The general idea is to model the prior over discrete latent variables $z \in \{ 1, \dots, K \}^{H \times W}$ using a 2D autoregressive model.

The joint distribution is factorized as:
$$
p_{\theta_{z}} (z) = \prod_{i=1}^{H} \prod_{j = 1}^{W} p_{\theta_{z}} (z_{i, j} | z_{<i, j})
$$
where $z_{<i, j}$ denotes all previously generated pixels in a raster scan order.
![[PixelCNN.png]]

#### Inference

Sampling is performed sequentially:
- Start with an empty image (or latent grid)
- For each pixel or latent vector $(i, j)$ in the image grid sample $z_{i, j}$ from the predicted categorical distribution:
	- Perform a *forward pass* through the PixelCNN to obtain the conditional distribution:
$$
p_{\theta_{z}} (z_{i, j} | z_{< i,j}) = \text{Cat} (z_{i, j}; \pi_{\theta_{z}}(z_{i, j})), \text{where } \pi_{\theta_{z}}(z_{< i, j}) = \text{PixelCNN} (z_{i, j}; \theta_{z})
$$
	- Sample $z_{i, j}$ from the predicted categorical distribution:
$$
z_{i, j} \sim p_{\theta_{z}} (z_{i, j} | z_{<i, j})
$$
- Fill in the grid one pixel at a time in raster scan order (row by row)

At generation time, pixels are sampled one by one, in raster-scan order (left-to-right, top-to-bottom), using the predicted distribution conditioned on previously generated pixels.

**Note**: This process is inherently slow, as each pixel depends on all previous ones, but
ensures valid samples from the model.

Implications:
- Sampling time scales linearly with the number of pixels.
- Cannot parallelize pixel generation.

For 2D data (images), we have two masking strategies:
- Mask type A
	- excludes the current pixel (i, j)
	- used in the first layer only to enforce strict causality
- Mask type B:
	- includes the current pixel (i, j)
	- used in all subsequent layers

This distinction is necessary since in the first layer we cannot access the current pixel $(i, j)$ that is supposed to predict (so we use type A), while in the subsequent layer we can allow the model to access the current pixel's position in the *feature maps* produced by earlier layers (so we use type B)

#### Training

PixelCNN is used to maximized the log-likelihood of the training data, which is equivalent to minimizing the negative log-likelihood:
$$
\mathcal{L} (\theta_{z}) = - \sum_{i, j} \log p_{\theta_{z}}(z_{i, j} | z_{<i, j})
$$
The output for each position is a discrete distribution (e.g. a softmax over $K$ categories, one for each codebook line)

The training loss corresponds to the standard *cross-entropy* between the predicted distribution and the true target.

*Problem*: sampling from PixelCNN is slow, as it requires a sequential forward pass for each pixel due to the autoregressive dependency. 

*Solution*: since during training ground-truth pixel values are available, we can apply **teacher forcing**:
- Unlike sampling, the model does not rely on its own predictions to generate subsequent pixels during training
- The model predicts all pixels in parallel through a single forward pass, using the ground-truth values as inputs for conditioning
- This avoid sequential generation during training, drastically speeding up process.

*Result*: Despite sequential sampling at inference, training is efficient and fully parallelizable.
![[PixelCNN_Pseudocode.png]]

During training we have a single forward pass, and we do not sample.

Each pixel is a classification problem over 255 values, so each loss is a sum of all the possible pixels.

Since this gives me an histogram containing each pixel, PixelCNN models the exact data likelihood:
$$
\log p(x) = \sum_{i, j} \log p(x_{i, j} | x_{<i, j})
$$
- This can be computed efficiently in a single forward pass using masked convolutions
- Allows us to assign a score probability (or log-likelihood) to any image

Since I then have a log-likelihood, PixelCNN is very useful in Anomaly Detection tasks and Novelty Detection (detect out-of-distribution samples by thresholding likelihood)

### Combined Pipeline

Since VQ-VAE learns a discrete latent space using vector quantization and encodes maps inputs to discrete latent codes, we can use it to learn the discrete latent space, on which we will then train PixelCNN to learn the generative prior, sample from PixelCNN and then decode via VQ-VAE decoder.

## Gumbel Softmax

In VQ-VAE we were exploiting the Straight-Through Estimator (STE).
An alternative is to use the **Gumbel Softmax**, which allows sampling from a categorical distribution during the forward pass through a NN.

$$
y_{k} = \frac{\exp\left( \frac{\log \pi_{k} + g_{k}}{\lambda} \right)}{\sum_{j} \exp\left( \frac{\log \pi_{j} + g_{j}}{\lambda} \right)}
$$ This shares similarities with the reparametrization trick used in VAEs

In *Gumbel Softmax*, $\lambda$ is used as smoothing parameter, where:
- $\lambda = 0$: Hard categorical choice:
$$
y_{k} = \text{one-hot}(\arg \max_{j} \pi_{j})
$$
- $\lambda = 1$
$$
y_{k} = \frac{\exp\left( \frac{\pi_{k}}{\lambda} \right)}{\sum_{j} \exp\left( \frac{\pi_{j}}{\lambda} \right)}
$$

The Gumbel-Softmax Trick allows sampling from a categorical distribution in a differentiable way using:
$$
y_{k} = \frac{\exp\left( \frac{\log \pi_{k} + g_{k}}{\lambda} \right)}{\sum_{j} \exp\left( \frac{\log \pi_{j} + g_{j}}{\lambda} \right)} \text{ with } g_{k} \sim \text{Gumbel} (0, 1) 
$$
- $\pi_{k}$: unnormalized logits (e.g. output of an ancoder)
- Gumbel noise $g_{k} \sim \text{Gumbel}(0, 1) = -\log (-\log(U)), U \sim \mathcal{U}(0, 1)$ adds stochasticity
- $\lambda$: temperature, controls how close the sample is to one-hot
![[Pasted image 20251121153629.png]]

Example with PyTorch:
```python
import torch.nn.functional as F
# Logits over 3 categories (batch_size = 1)
logits = torch.tensor([[2.0, 0.01, 1.0]], requires_grad=True)
tau = 0.5 # Temperature
# First soft sample
y_soft1 = F.gumbel_softmax(logits, tau=tau, hard=False)
print("Soft sample (pass 1):", format_tensor(y_soft1))
# Second soft sample
y_soft2 = F.gumbel_softmax(logits, tau=tau, hard=False)
print("Soft sample (pass 2):", format_tensor(y_soft2))
# Hard sample
y_hard = F.gumbel_softmax(logits, tau=tau, hard=True)
print("Hard sample (approx. one-hot):", format_tensor(y_hard))
```
The output of this will be:
```
Output.
Soft sample (pass 1):
[[0.99, 0.01, 0.0]]
Soft sample (pass 2):
[[0.08, 0.0, 0.92]]
Hard sample (approx. one-hot):
[[0.0, 0.0, 1.0]]
```
Here, the `tau` value is set always the same, since we are sampling, so the values can change. 

The initial example now becomes like this:
```python
scores = torch.matmul(keys, query.T).squeeze() # shape: (5,)
# Gumbel-Softmax for differentiable selection
weights = F.gumbel_softmax(scores, tau=0.1, hard=True) # shape: (5,)
# Differentiable value selection (softmax-weighted sum)
selected_value = torch.sum(weights.unsqueeze(1) * values)
# Loss (e.g., encourage high value selection)
loss = selected_value ** 2
loss.backward()
# Show gradients
print("Selected value:", selected_value.item())
print("Gradient w.r.t. query:", query.grad)
# Selected value: 30.0
# Gradient w.r.t. query: tensor([[ 0.2450, -0.2618, -3.1309, 4.7076]])
```
