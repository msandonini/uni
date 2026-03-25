---
course: Computer Vision and Cognitive Systems
tags:
  - computer_vision
---

Image recognition is a classification task, and as such, we use cross-entropy (as in 99% of all classification tasks).
Object detection, on the other hand, is a more complex task, as its output is composed by the bounding boxes of the objects and the class of these, so we have $n \times 2$ outputs, where $n$ is the number of bounding boxes, and as such when we pass an image to the model we don't know the number of outputs we will get.

Comparing different computer vision tasks, we can categorize them in 4 main groups:
- Semantic segmentation
	- Outputs the different classes of the image for each recognized shape
	- Works on pixels and not on objects
	- Cannot count the number of instances
- Classification + localization
	- Recognizes the class of a single object
	- Works on a single object
- Object detection
	- Recognizes the class of multiple objects
	- Works on multiple objects, so we can count the single instances
- Instance segmentation
	- A sort of mix between the object detection and semantic segmentation
	- Recognizes the shapes of the single instances of the objects
	- Can count the number of different instances
![[Pasted image 20260325123103.png]]

![[Pasted image 20260325123122.png]]

An example of object detection is the following:
![[Pasted image 20260325123200.png]]
As we can see in the image, the output of object detection is a set of boxes (so a set of coordinates), with a category and its confidence score for each box.

A simple way of doing object detection is applying a image classification CNN to different smaller cuts of an image, which could work, but is incredibly inefficient, since different objects can have different sizes and different positions, so we must apply different cycles in order to apply different cuts of different sizes and positions (and it can get very slow since it needs to apply many forward passes).

### R-CNN

In 2014, [Ross Girshick](https://scholar.google.com/citations?user=W8VIEZgAAAAJ&hl=en) created the [R-CNN](https://arxiv.org/abs/1311.2524) architecture, which is a CNN architecture based on a selective search to distinguish regions of the images based on the colors, in order to identify a limited number of bounding boxes with a good chance of containing an image

![[Pasted image 20260325124724.png]]

![[Pasted image 20260325124823.png]]

This architecture still has some problems:
- the CNNs expect a fixed input size and regions can have different dimensions, a resizing of the image regions is needed, however this could break the image recognition pass, as the reshape could modify the image appearance
- training is slow
- inference is slow

### Fast R-CNN

In 2015 Girshick proposed a solution to the problems of R-CNN, which is [Fast R-CNN](https://arxiv.org/abs/1504.08083), which extracts the regions of interest after applying the ConvNet, reducing the number of forward passes to just 1.

![[Pasted image 20260325130719.png]]

> [!INFO] Note
> In a ConvNet, most of the learnable parameters are on the fully connected layer, which is bad since the feature extraction is done before we arrive to these layers.

We want the RoIs to be modifiable, but as a requirement of the ConvNet layers the constraint we have when writing a layer is that the math operation in it must be differentiable, so we apply the **RoI pooling layer**.

![[Pasted image 20260325130049.png]]

After applying the RoI pooling, we then put our fully connected layers, and we apply the bounding box regressors in order to perform the classification task.

![[Pasted image 20260325130653.png]]

> [!INFO] Note
> The RoI algorithm is fixed and not trainable

#### RoI pool

<!-- Images in slides 42 - 47 -->

In the RoI pooling layer we start from a 3D input shape (4D if we consider the batch size).
This image is passed in a CNN to align the coordinate and "snap" the image to the grid cells.
At this point we extract a fixed number of regions, and then we apply max pooling for each extracted cell, reducing the dimensionality to a $2 \times 2$ and picking the max value of the 4 regions.

Given a feature map obtained from an image, with shape $(C, H, W)$, the coordinates of a bounding box $(y_1, x_1, y_2, x_2)$, and a desired output shape $(oH, oW)$
![[Pasted image 20260325132606.png]]
- We round the coordinates of the bounding box to the nearest integer, thus obtaining a bounding box which can be “aligned” with the coordinate space of the feature map
![[Pasted image 20260325132656.png]]
- We divide the bounding box into a $(oH, oW)$ grid of cells
- The $(i, j)$-th cell covers the range $[⌊y_1 + i * (y_2 - y_1 + 1)/oH⌋, ⌈y_1 + (i + 1) * (y_2 - y_1 + 1) / oH⌉]$ over the $y$ axis $[⌊x_1+j*(x_2-x_1+1)/oW⌋, ⌈x_1+(j+1)*(x_2-x_1+1)/oW⌉]$ over the x axis where 
	- $⌊$, $⌋$ indicate the floor
	- $⌈$, $⌉$ indicate the ceiling,
	- $/$ is the float division
	- all intervals exclude the right side.
- Finally, we max pool over the $(oH, oW)$ grid of cells
- As in a normal max pooling, we take the maximum over each channel independently
- Therefore, we obtain a $(C, oH, oW)$ output.
![[Pasted image 20260325133306.png]]

This is what happens for a single input image and a single input bounding box.
Of course, the ROI Pooling operator usually works on multiple bounding box at the same time, and over a batch of images
Each image in the batch has its own bounding boxes.

![[Pasted image 20260325133602.png]]
As we can see, the [[#Fast R-CNN]] is the fastest algorithm between those, however the region proposal is what is taking a lot of time

### Faster R-CNN

In 2015, in order to make [[#R-CNN]] even faster, [Faster R-CNN]() was proposed.

This architecture substitutes the Region Proposal Algorithm (which is slow as it is a fixed algorithm run on CPU) with a Region Proposal Network, which is basically a 2-layer CNN (which can be run on the GPU, so it can be faster).
![[Pasted image 20260325133748.png]]

The Region Proposal Network is basically a network which, for a set of pixels of an image called anchors, predicts if the box around the anchor contains an image (it's a binary classification).

![[Pasted image 20260325134121.png]]

In practice use $K$ different anchor boxes of different size and/or scale at each point, and in a single pass we compute the different anchor boxes to predict whether the box contains an object or not, and we have 2 outputs:
- The box transforms
	- Loss is MSE
- The classification (so if the box contains an object or not)
	- Loss is Binary Crossentropy
![[Pasted image 20260325134401.png]]

After the RPN, we use RoI Pooling and an upstream classifier and bbox regressor just like Fast R-CNN.

