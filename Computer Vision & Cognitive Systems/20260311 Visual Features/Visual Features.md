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

The "classical" computer vision pipeline started in the late '80s, and at that time there was very small knowledge in neuroscience on the nature of the brain, since cortex and vision functionalities where not so well known, so the pipeline was based on a bottom-up data driven approach.

![[Pasted image 20260311124607.png]]

![[Pasted image 20260311124640.png]]
![[Pasted image 20260311124659.png]]
![[Pasted image 20260311124731.png]]

In the recent years, the approach to computer vision changed, becoming based on the usage of AI to learn the features to be used for a specific goal.

As of now, the standard is using **[[foundation models]]** to learn everything in a prior unsupervised manner and than downstream tasks.
This is working on very generic and well represented objects/concepts, but is still not suitable for all specific tasks

Given an image, [[feature extraction]] is normally the task which performs the extraction of a **n-dimensional vector** representing some visual property.
The feature has to be designed to effectively summarize the visual content, so it's a quantization problem or a compression problem.

The choice criteria for visual features are basically 4 different proprieties:
- Discriminant propriety
	- Features must assume values that are significantly different for objects belonging to different classes
- Reliability propriety
	- Features must assume values that are similar for objects belonging to the same class
- Independence propriety
	- Features must be independent from each other
- Minimum cardinality propriety
	- Features must be as few as possible

Some classical visual features in images are:
- Color (perceptual features)
- Shape (contours)
- Texture (continuity and spatial similarity)
- Depth (3D shape)
- Motion (continuity in time)
- Perception (keypoints)
- Saliency (attention-based)


