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

All these coordinates make it possible for us to perform all the transformations in a matrix form.

We can perform different operations:
- Translation
	- The movement of a point based on a translation vector
	![[Pasted image 20260427103517.png]]
	- In homogeneous coordinates, translation can be obtained by a matrix product ; it is possible to find a matrix T, constituted by the identity matrix and the translation vector such that:
$$
\begin{bmatrix}
X_{2} \\
Y_{2} \\
1
\end{bmatrix} =
\begin{bmatrix}
1 & 0 & dx \\
0 & 1 & dy \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
X_{1} \\
Y_{1} \\
1
\end{bmatrix}
$$
- Euclidean transformation: Translation and rotation
	- These transformations are also called Isometries, or Class I transformations.
	- All Euclidean transformations are isometries
$$
\begin{bmatrix}
x' \\
y' \\
1
\end{bmatrix} =
\begin{bmatrix}
\epsilon \cos \theta & -\sin \theta & t_{x} \\
\epsilon \sin \theta & \cos \theta & t_{y} \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
1
\end{bmatrix}
\hspace{1.5cm} \epsilon=\pm_{1}
$$
- 2D scaling
	- This scales an image by a scaling factor.
	- This operation preserves the orientation and not the area
- Class II: Similarity transformation
	- This transformation is a 2D scaling + rotation + translation.
	- Each point is rotated, scaled, and translated.
$$
\begin{bmatrix}
x' \\
y' \\
1
\end{bmatrix} =
\begin{bmatrix}
\epsilon \cos \theta & -\sin \theta & t_{x} \\
\epsilon \sin \theta & \cos \theta & t_{y} \\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x \\
y \\
1
\end{bmatrix}
\hspace{1cm} x' = H_{s} x = \begin{bmatrix}
sR & t \\
0^{T} & 1
\end{bmatrix}x
\hspace{5mm} R^{T}R = I
$$
