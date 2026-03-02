---
tags:
  - computer_vision
---
We recognize objects by its contours, which are characterized by strong luminance variations.

Drawing the contours of an image is quite easy for humans, even if often subjective, but it's a challenging problem for computers.

 We call **edge** a local property of a pixel and its neighborhood to have a rapid intensity variation, but to compute it in an image, we need to compute its derivative, in order to be able to tell where there are variations.

An edge is a vector, with a magnitude and a direction, and it depends on the luminance variation, which can be computed as a gradient. The edge has the direction perpendicular to the gradient direction, which always pointed in the direction of greater luminance.

![[Pasted image 20260302095049.png]]

With the term **border** we refer to a propriety of a *region*, while the edge is a *local* propriety. We can compute borders by selecting the strong edges.

There are many reasons to have an edge:
- Discontinuity between the surface colors of an object
- Discontinuity between the depth of multiple objects
- Discontinuity in an object's surface normal
- Discontinuity in the illumination value (e.g. a shadow)
So, when computing edges, we don't get just the object edges, but also edges caused by the previous discontinuities.

In order to perform border detection, we need to compute these steps:
- Use of an edge detection operator (edge detector)
- Selection of strong edges with some given criteria
- Linking the edges (labelling)

The gradient of a 2D continuous function $f(x, y)$:
$$
\nabla f = \left[ \frac{df}{dx}, \frac{df}{dy} \right] 
$$
The gradient direction is given by:
$$
\theta = \tan^{-1} \left( \frac{df}{dy} / \frac{df}{dx} \right)
$$
The edge strength is given by the gradient magnitude:
$$
\left\lvert  \left\lvert  \nabla f \right\rvert   \right\rvert  = \sqrt{ \left( \frac{df}{dx} \right)^{2} + \left( \frac{df}{dy} \right)^{2} }  
$$

There are multiple ways to execute discrete detection:
- **Forward difference**: $\Delta_{h} [f] = f(x + h) - f(x)$
- **Backward difference**:
	- Uses the function values at $x$ and $x - h$ instead of the values at $x+h$ and $x$
$$\nabla_{h} [f] (x) = f(x) - f(x - h)$$
- **Central difference**
	- We use both
$$
\delta_{h} [f] (x) = f\left( x+\frac{1}{2} h \right) - f\left( x - \frac{1}{2} h \right)
$$

We can compute central difference given the function $f(x, y)$ and the discretization $f(r, c)$
$$
\frac{d f (r, c)}{d r} = f(r + 1, c) - f(r - 1, c)
$$
$$
\frac{df(r, c)}{dc} = f(r, c + 1) - f(r, c - 1)
$$
Can be computed by convolution with the convolution masks:
![[Pasted image 20260302100431.png]]

Now, which kernel do we want to use?
The previous one is going to work, but images are noisy, so different types of kernel were created:
- **Prewitt Mask**:
![[Pasted image 20260302101221.png]]
- **Dobel operator**:
![[Pasted image 20260302101257.png]]
- **Frei and Chen**:
![[Pasted image 20260302101332.png]]

Each kernel does comes with a tradeoff:
![[Pasted image 20260302101844.png]]

![[Pasted image 20260302102216.png]]

