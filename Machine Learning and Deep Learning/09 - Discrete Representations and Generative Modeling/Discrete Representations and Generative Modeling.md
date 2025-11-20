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
\begin{array}{lll}
1: & \textbf{Input: } \text{input } x, \text{encoder } E(\cdot), \text{decoder } D(\cdot), \text{codebook } \{e_k\}_{k=1}^K & \\
2: & z_e \leftarrow E(x) & \text{\# Encode input} \\
3: & k \leftarrow \arg \min_j \|z_e - e_j\|^2 & \text{\# Nearest codebook entry} \\
4: & z_q \leftarrow e_k & \text{\# Quantized latent} \\
5: & z_q^{\text{st}} \leftarrow z_e + \text{detach}(z_q - z_e) & \textbf{\# } \color{red}{\text{Straight-Through Estimator}} \\
6: & \hat{x} \leftarrow D(z_q^{\text{st}}) & \text{\# Reconstruct} \\
7: & \mathcal{L}_{\text{rec}} \leftarrow \|x - \hat{x}\|^2 & \text{\# Reconstruction loss} \\
8: & \mathcal{L}_{\text{codebook}} \leftarrow \|\text{stopgrad}[z_e] - z_q\|^2 & \\
9: & \mathcal{L}_{\text{commit}} \leftarrow \|z_e - \text{stopgrad}[z_q]\|^2 & \\
10: & \mathcal{L} \leftarrow \mathcal{L}_{\text{rec}} + \mathcal{L}_{\text{codebook}} + \beta \mathcal{L}_{\text{commit}} & \\
11: & \text{Backpropagate and update model and codebook} &
\end{array}
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

