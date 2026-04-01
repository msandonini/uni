---
course: Computer Vision and Cognitive Systems
---
Segmentation tasks are divided in Semantic and Instance Segmentation:
- Semantic segmentation is the task where we classify the pixels
- Instance segmentation is the task where we find the bounding boxes of the instances of an object, and then perform segmentation on the specific objects instances

## Semantic segmentation
As previously said, semantic segmentation classifies each single pixel of an image.

The first idea to perform semantic segmentation is to use a sliding window to classify the center pixel of each patch.
In order to do this, we pass the image in a CNN, but the CNN's pooling layer reduces the size of the image, giving us a smaller output.

What we really want, instead of a CNN with a pooling layer, we want an architecture with several convolution layers and the argmax in the end to evaluate the scores, and not pooling layer.
This architecture, however, has some problems:
- Small receptive field to perform in a good way
- Lots of learnable parameters, so this architecture takes a lot of space and is quite slow

To solve these problems, the solution was to use a standard CNN (with the pooling layers) to perform the downsampling of the image and the classification, and then apply an upsampling network on the output of the CNN in order to upscale the output and obtain an image of the same size as the original one.

In order to design the upsampler, the first ideas were the following 2:
- Nearest neighbors
	- For each layer, replicate each pixel to their near pixels, in order to double the image size on each layer
	- This works, but the detail resolution remains low
- Bed of nails
	- For each pixel, we create an image with a $2 \times 2$ square per-pixel where the pixel value is on the top left, and all the values in its nearest neighbors are 0

Another solution is to track the max values' positions of the max pooling, and then when we do the upsampling we apply the unpooling by putting the value in the tracked position, and all other values are set to 0. This solution has the same problem of the bed of nails

What we really want to do is to make the inverse operation of the convolution (which is called a transpose convolution), since the downsampling actually happens in the convolution and not in the pooling (since in the convolution we have stride, padding, and dilation).
To make this transpose convolution we use a convolutive kernel which uses the pixel value of the reduced image as weight. In the positions where the kernels overlap, what we can do is to sum the weights, so that we don't lose detail in the image

