Keypoints are a way to extract descriptors from an image, with each descriptor associated to a location of the image, in order to obtain sparse features instead of dense ones. This is done since there is a variety of tasks (e.g. image correspondence) where extracting some features makes more sense than having all the dense features matrix.

Here we are tackling 2 tasks:
- Keypoint detection
	- Finds the more interesting points or regions of the image
- Keypoint description
	- Describes a patch around the point/region with a vector of features

## Keypoint detection

### Harris detector
The HARRIS keypoint detector is an algorithm which extracts points from various regions based on variations in the gradient.

![[Pasted image 20260420094504.png]]

Given a pixel $q(x, y)$ and a neighborhood window $\Omega(q)$, let's compare (as in template matching) the windows with itself after a $\delta$ shift in a $d$ direction ($d$ is the unitary vector). From here, we look for a point where the $D$ information is high.
$$
D_{q}(d) = \sum_{r \in \Omega(q)}[d^{T} \nabla I(r)]^{2}
$$
$D$ is the information content associated with $q$ in the $d$ direction, relative to the window.
Basically we slide a window over the image and look at points where there is a greater variance.

Simplifying, we can see the information content $D$ as the value computed as the intensity difference $D=E(u, v)$ after the shift $d=(u,v)$:
$$
E (u,v) = \sum_{x, y} w(x, y) [I(x+u, y+v) - I(x,y)]^{2}
$$
So, using Taylor:
$$
\begin{align}
E(u, v) &\approx \sum_{x, y} w(x, y)[I(x, y) + uI_{x} + vI_{y} - I(x, y)]^{2} \\
&= \sum_{x, y} w(x, y)[uI_{x} + vI_{y}]^{2} \\
&= \sum_{x, y} w(x, y)(u \hspace{5mm} v)\begin{bmatrix}
I_{x}I_{x} & I_{x}I_{y} \\
I_{x}I_{y} & I_{y}I_{y}
\end{bmatrix}\begin{bmatrix}
u \\
v
\end{bmatrix}
\end{align}
$$
Thus we can see a valuable information content in a point q if the M Matrix is "valuable". These points with valuable content could be edges, corners, etc... .
$$
\begin{align}
E(u, v) \simeq \begin{bmatrix}
u, v
\end{bmatrix} M \begin{bmatrix}
u \\
v
\end{bmatrix}\\ \\
 
M = \sum_{x, y}
 w(x, y)\begin{bmatrix}
I_{x}^{2} & I_{x}I_{y} \\
I_{x}I_{y} & I_{y}^{2}
\end{bmatrix}\end{align}
$$
$M$ is called structure tensor, or also auto-correlation matrix (also Hessian matrix)

The point $p$ in the image is "salient" (as a corner) if the information content is meaningful enough, thus a threshold value exists so that $\min\{d^{T} Md|d \in \mathbb{R}^{2}.||d||=1\} > \tau$.
This is equivalent to saying $\min \lambda > \tau$.

Corners and edges can be distinguished by analyzing the Hessian eigenvalues computed on a sliding window $w(x, y)$.
Eigenvalues $\lambda_{1}$ and $\lambda_{2}$ of $M$ reveal the intensity of the gradient change within the 2 most significant orthogonal direction:
- if $\lambda_{1} \gg \lambda_{2}$ or $\lambda_{1} \ll \lambda_{2}$ there is an edge
- if $\lambda_{1} \sim \lambda_{2}$ and they are large, we have a corner
- If they are small we are in a flat region

![[Pasted image 20260420100209.png]]

The Harris detector is invariant to the intensity changes and the rotation, but not to the scale.
![[Pasted image 20260420100737.png]]
![[Pasted image 20260420100754.png]]
![[Pasted image 20260420100818.png]]

### SIFT (Scale Invariant Feature Transform)
