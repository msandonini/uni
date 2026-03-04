---
tags:
  - computer_vision
  - convolutional_neural_networks
---
A [[Machine Learning and Deep Learning/CNN|CNN]] works by using a kernel to navigate on an image.
When the kernel passes on a window in the pixel matrix, it applies a function, applying element-wise multiplication between the kernel values and the window values, and the values obtained in a single pass then get summed with each other in order to obtain a new value which will occupy a single cell in the output matrix (the output matrix will always be of a smaller size in respect to the input image's pixel matrix).

![[Pasted image 20260304122318.png]]

In a 3D scenario where we work with an image of $H \times W$ size with $C$ channels, what we do is apply the same kernel of size $kH \times kW$ adding an extra axis to the kernel in order to make it pass over all the channels, making it learn $(kH \times kW) \times iC$ parameters. This is still a 2D convolution since the kernel keeps moving over just 2 axes.

A convolutional layer usually takes $iC$ input feature maps, but also produces $oC$ output maps, where each one of these output maps considers all input feature map, which is the equivalent of performing the operation $oC$ times with different kernel and biases.
![[Pasted image 20260304123241.png]]
In this case, we have an input shape $(iC, H, W)$ and a kernel shape $(oC, iC, kH, kW)$, which is like having $oC$ different kernels and biases, and this will produce an output of shape $(oC, oH, oW)$, which is like performing $oC$ different cross-correlations.
Also, if we do it for a batch of $n$ different images in parallel, we add the $n$ parameter to our coordinates.

Other parameters we can pass to the kernel are **stride** and **padding**.
- Stride: controls the stride for the cross-correlation.
	- We usually assume 1.
	- If larger than 1 the kernel pass will stride more while moving, making the output smaller since less windows are processed.
- Padding: the amount of implicit paddings on both sides for padding number of points for each dimension.
	- We usually assume 0.
	- A typical choice is $k - 1$, where $k$ is the kernel size, so that the output shape matches the input shape on spatial axes.
	- Usually we pad with 0s, even if other options are possible.
![[Pasted image 20260304124225.png]]

As we can have all $(kH \times kW)$ kernel sizes, we can also have a $(1 \times 1)$ kernel, which keeps the image size the same, and it is very powerful since it can change the number of channels without changing the image size.
![[Pasted image 20260304124837.png]]

Another important parameter is the **dilation** which makes it possible to increase the kernel's perceptive field without increasing its size.
![[Pasted image 20260304125711.png]]
This is important because it means that a single pixel can see a bigger part of the image without increasing the number of learnable parameters.

