---
tags:
  - computer_vision
  - convolutional_neural_networks
---
A CNN works by using a kernel to navigate on an image.
When the kernel passes on a window in the pixel matrix, it applies a function, applying element-wise multiplication between the kernel values and the window values, and the values obtained in a single pass then get summed with each other in order to obtain a new value which will occupy a single cell in the output matrix (the output matrix will always be of a smaller size in respect to the input image's pixel matrix).

![[Pasted image 20260304122318.png]]

