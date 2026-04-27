3D and 2D geometric primitives are what we mainly use to describe three-dimensional shapes.

The vision model is based on the physical lens models, and o the geometric optics so the world can be described by the 3D geometry and its mapping onto 2D planes.
Our brain vision system uses geometric descriptors to recognize the world, both embedded in the perception and learned after Euclides.

In order to perform transformation we need to review euclidean geometry.
In euclidean geometry we basically have a point in a plane defined by 2D coordinates (this is also basically how we represent a pixel in an image).
This representation has a problem with perspective and parallel lines definition, so we use homogeneous coordinates in a projected space.

In the 2D case $x=(x, y)$:
$$
\text{x} = (x, y) \in \mathcal{R}^{2} \to \tilde{\text{x}} = (\tilde{x}, \tilde{y}, \tilde{w}) \in P^{2}
$$
What this formula represents is a projective plane of the 2D plane:
![[Pasted image 20260427102301.png]]
Each point $p$ represented in unhomogeneous coordinates $(x, y)$ in $\pi$ is in biunivocal correspondence with the term $(x, y, 1)$ in $\mathbb{R}^{3}-(0, 0, 0)$, and the projective space is called $P^{2}$.
The line $O_p$ is the line of the coordinates $(wx, wy, w)$ for each $w$.
Thus, given $S$ the set of lines through $O$:
$$
p = (x, y, 1) \in \pi \to \{(wx, wy, w,) w \in R\} \in S
$$

![[Pasted image 20260427102833.png]]


