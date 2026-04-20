---
course: Computer Vision and Cognitive Systems
---
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

Now that we have the keypoints, how can we describe them?
- If we know where the corners are, how can we match them?
- Which descriptor do we need to use for this feature?
A solution could be a vector of the 9 pixel values, but this is not invariant to luminance variation nor rotation.
### SIFT (Scale Invariant Feature Transform)

SIFT is both a detector and a descriptor.
We want to detect keypoints in a way that is invariant to scale.
To do so, we work on images at different scale producing octaves in a pyramidal level.
![[Pasted image 20260420101714.png]]

The first octave is obtained by the convolution operation at different $\sigma$s such that $\sigma_{n}=k^{n} \sigma_{0} \hspace{5mm} (k=2)$.
The DoG ([Difference of Gaussian](https://en.wikipedia.org/wiki/Difference_of_Gaussians)) at scale $\sigma$ is obtained by the difference of two nearby scales separated by a constant $k$.
All the DoGs are an approximation of Laplacian.
After the first octave is completed the image is subsampled by a factor equal to 2 for a next pyramid way
![[Pasted image 20260420102344.png]]
![[Pasted image 20260420102621.png]]

After obtaining the octaves, we need to localize the keypoints.
The highest variation causes a peak (local extreme).
Local extrema of $D(x, y, \sigma)$ are the local interest points.
If $p$ is a local extrema, it is selected as a candidate keypoint.
Each candidate keypoint is compared to the 9 neighbours in the scale above and below.
Only pixels that are local extrema in **3 adjacent levels** are promoted as keypoints.

The number of scales and octaves is selected empirically.

Edge has large principal curvature across the edge, but a small one in the perpendicular direction.
The principal curvatures can be calculated from a Hessian function. The eigenvalues of H are proportional to the principal curvatures, so two eigenvalues shouldn’t diff too much.
Lowe suggests keep points with r=10:

$$
H = \begin{bmatrix}
D_{xx} & D_{xy} \\
D_{xy} & D_{yy}
\end{bmatrix}
\hspace{1cm}
\frac{\text{Tr}(H)^{2}}{\text{Det}(H)} < \frac{(r+1)^{2}}{r}
$$

By assigning a consistent orientation, the keypoint descriptor can be orientation invariant. For a keypoint, if $L$ is the Gaussian smoothed image with the closest scale, for a region around keypoint compute gradient magnitude and orientation using finite difference.

After doing so, we create a histogram with 36 bins for orientation, and weight each point with Gaussian window of $1.5 \sigma$

![[Pasted image 20260420103729.png]]

Peak orientation is the keypoint canonical orientation.
Any peak within 80% of the highest peak is used to create a keypoint with that orientation. Local peaks within 80% create multiple orientations. About 15% has multiple orientation (<span>&rarr;</span> multiple keypoints).

In order to describe the points we need to do a set of passages:
- Divide the 16x16 window into a 4x4 grid of cells
- Compute an orientation histogram for each cell
- 16 cells \* 8 orientations = 128 dimensional descriptor
![[Pasted image 20260420104707.png]]


