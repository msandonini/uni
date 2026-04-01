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

