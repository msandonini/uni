---
course: Computer Vision and Cognitive Systems
---
Segmentation tasks are divided in Semantic and Instance Segmentation:
- Semantic segmentation is the task where we classify the pixels
- Instance segmentation is the task where we find the bounding boxes of the instances of an object, and then perform segmentation on the specific objects instances

## Semantic segmentation
As previously said, semantic segmentation classifies each single pixel of an image.

The first idea to perform semantic segmentation is to use a sliding window to classify the center pixel of each patch.