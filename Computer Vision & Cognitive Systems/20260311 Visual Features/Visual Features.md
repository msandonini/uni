---
tags:
  - computer_vision
---
In order to perform a CV task, we need to generate a semantic representation of the image.
![[Pasted image 20260311122323.png]]

To represent the image we can either use a geometrical shape or a visual shape.
In the case of a visual shape, it has 2 properties:
- Class: describes if the shape is a 2D view or a 3D image based on the depths of point clouds
- Number of views (so if the image is represented by a single view or by multiple views)

![[Pasted image 20260311123018.png]]

Computational Vision has 3 levels:
- Computational
	- What the system does and why
- Algorithmic / Representational
	- How the system does what it does and what representations and processes are used
- Implementational
	- How the system is physically realized

To compute an image in order to extract 3D data, the process passes by 4 levels:
- A 2D image is created with intensity values at each point (pixels)
- A primal sketch of the scene based on feature extraction of fundamental components of the scene, including edges, regions, etc...
- 2.5D sketch of the scene, where textures are acknowledged
- Definition of the 3D model

![[Pasted image 20260311124314.png]]


