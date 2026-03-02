We recognize objects by its contours, which are characterized by strong luminance variations.

Drawing the contours of an image is quite easy for humans, even if often subjective, but it's a challenging problem for computers.

 We call **edge** a local property of a pixel and its neighborhood to have a rapid intensity variation, but to compute it in an image, we need to compute its derivative, in order to be able to tell where there are variations.

An edge is a vector, with a magnitude and a direction, and it depends on the luminance variation, which can be computed as a gradient. The edge has the direction perpendicular to the gradient direction, which always pointed in the direction of greater luminance.

With the term **border** we refer to a propriety of a *region*, while the edge is a *local* propriety. We can compute borders by selecting the strong edges.

