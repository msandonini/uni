Given a transformation $x' = Hx$ and given an initial image $I = f(x)$, we call **parametric transformation** the process in which we create a new image $I'=g(x)$. To do so, we have 2 different algorithms:
- Forward: 
	- For every pixel $x$ in $f(x)$ compute the destination location $x'=h(x)$ and copy the pixel $f(x)$ to $g(x')$
	- This is straightforward, but has some limitations:
		- $x'$ can be not integer, so further transformation or blending is needed to distribute it in the neighborhood (in computer graphics this is called *splatting*)
		- Some $x'$ point can be not defined
- Inverse
	- For every pixel $x'$ in $g(x')$ compute the destination location $x = \hat{h}(x')$ and resample $f(x)$ at location $x$ and copy to $g(x')$
	- This is defined in each point (we get no holes)
	- If the initial location is not an integer coordinates some interpolation methods can be adopted (neighbour, bilinear, bicubic, etc...)
	- The inverse kernel in this case is the inverse matrix

All the previous transformations can be done in a 3D space by basically adding an additional coordinate.
The translation remains fundamentally identical, except for the fact that now we have one more dimension.
The rotation changes a bit, as we now need to take care of the rotation axis. As an example, in a 3D rotation around the Z axis the operation is the following:
$$
\begin{cases}
X_{2} = X_{1} \cos \vartheta - Y_{1} \sin \vartheta \\
Y_{2} = X_{1} \sin \vartheta + Y_{1} \cos \vartheta \\
Z_{2} = Z_{1}
\end{cases}
$$
![[Pasted image 20260429124519.png]]

Composite transformations are obtained by multiplying the matrices of each step:
$$
T_{c} = T_{4}\cdot T_{3}\cdot T_{2}\cdot T_{1}
$$



