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
In a composite transformation the order is important, as in the example above the first transformation is $T_{1}$, and the last is $T_{4}$, thus the order is basically the following:
$$
P_{2} = T_{c} \cdot P_{1} = T_{4} \cdot T_{3}\cdot T_{2}\cdot T_{1}= T_{4}\cdot(T_{3}\cdot (T_{2}\cdot(T_{1}\cdot P_{1})))
$$


In Computer Vision, transformations are useful to perform transformations on the images before processing them. For example, if we have 2 separate images which we want to unify in a landscape image, we can do so by using homography estimation:
![[Pasted image 20260429130412.png]]
- We select 4 points in the same plane but not collinear, each with its set of coordinates:
$$
\begin{bmatrix}
x_{i}' \\
y_{i}' \\
1
\end{bmatrix} = 
\begin{bmatrix}
h_{00} & h_{01} & h_{02} \\
h_{10} & h_{11} & h_{12} \\
h_{20} & h_{21} & 1
\end{bmatrix}
\begin{bmatrix}
x_{i} \\
y_{i} \\
1
\end{bmatrix}
$$
- In this formula $h_{00}, \dots, h_{21}$ are the variables
$$
\begin{align}
x_{i}' &= h_{00} x_{i} + h_{01} y_{i} + h_{02} \\
y_{i}' &= h_{10} x_{i} + h_{11} y_{i} + h_{12} \\
1 &= h_{20} x_{i} + h_{21} y_{i} + 1
\end{align}
$$
$$
\begin{cases}
x_{i}' = \frac{h_{00} x_{1} + h_{01} y_{1} + h_{02}}{h_{20} x_{1} + h_{21} y_{1} + 1} \\
y_{i}' = \frac{h_{11} x_{1} + h_{11} y_{1} + h_{12}}{h_{20} x_{1} + h_{21} y_{1} +1ì 1}
\end{cases}
$$
- Now we repeat for the 4 points, obtaining a matrix of 8 equations (slide 66)

In real life, when we take a photo or a video, we are basically applying a 3D to 2D transformation.
3D to 2D transformations can be of 2 types:
- Orthographic
	- Given $x$ a 2D point and $p$ a 3D point, $x = (x, y)$, $p=(x, y, z)$
	- With this transformation we basically drop the z coordinate
	- In the real world, this is possible only when the depth of the objects is the same or when we are using cameras with a very long focal length
![[Pasted image 20260429131506.png]]
- Perspective
	- This is the most commonly used projection, as it is the one usually obtained by normal cameras and in normal conditions. Here, points are projected on the image plane by dividing by their z component (this is why the more distant objects look smaller)
![[Pasted image 20260429131525.png]]