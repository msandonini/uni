---
course: Computer Vision and Cognitive Systems
---
A foundation model is a model which gets pre-trained in order to act as a generic foundation for many different tasks.
[[Unified Visual & Language Models#CLIP ([Learning Transferable Visual Models from Natural Language Supervision](https //arxiv.org/pdf/2103.00020))|CLIP]] is an example of these types of models.
![[Pasted image 20260521103932.png]]

These models have a few characteristics in order to be recognized:
- they are general/robust to many different tasks
- they usually have a large number of parameters and data
- they usually have self-supervised pre-training

A multi-modal model is a model which acts as an integration between 2 different tasks. In our case, these tasks are language understanding (done with [[LLM|LLMs]]), and computer vision.

## LLaVA

Language models which do next token prediction can be applied to a wide variety of tasks at inference.
If we build a model that can accept images and text as input, and then output text, we obtain what is called a Vision-Language Model.

![[Pasted image 20260521104846.png]]
LLaVA uses the autoregressive nature of LLMs in combination with CLIP in order to add visual information to the LLM.
![[Pasted image 20260521105049.png]]

What we need to do in this case is to decide what features we should use from CLIP.
![[Pasted image 20260521105252.png]]
If we took the output tokens discarding the CLS we would obtain non-supervised tokens, which could be random and the loss won't change, so we instead take the tokens from the penultimate layer:
![[Pasted image 20260521105623.png]]
This makes it so that we have more fine-grained set of vectors.

In order to train this architecture, we initialize it with a pre-trained Language Model for LLM Decoder (e.g. [[Llama]]) and a pre-trained image decoder (e.g. CLIP).
After that, we train a new linear layer to train bridge CLIP features to LLM input space, and then fine-tune LLM and linear layer together.

![[Pasted image 20260521110015.png]]

## Segment Anything Model (SAM)

SAM is a segmentation foundational model trained on [[COCO]].
The fact that it is a foundation model means that it can segment also data on which it is not trained.

![[Pasted image 20260521112444.png]]

The prompt encoder can accept points, bounding boxes, or text (even if the text version was never released by Meta, but we know it should work since a paper about it was released).
This model is not able to classify objects, but it's very powerful in segmentation.

The reason why SAM is very powerful is that it has a caching mechanism, so once it receives the image it takes a while to pass it in the image encoder, but then it caches the activation function and it makes it possible to change the object we want to segment almost immediately.

![[Pasted image 20260521113234.png]]


