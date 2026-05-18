---
course: Computer Vision and Cognitive Systems
---
Making deep neural architectures understand video data is useful for various tasks:
- robotics / manipulation
- self-driving cars
- collective activity understanding
- video captioning
- video editing
- VR
- video QA
- ...

In order to perform these tasks we need a variety of different videos.
To obtain those, there are various datasets:
- UCF 101
	- Dataset from Google, composed of YouTube videos
	- Used for video classification
	- Contains 13'320 videos and 101 action categories
	- The videos have large variations in camera motion, object appearance and pose, viewpoint, background, illumination, etc...
- Sports-1M
	- Composed of YouTube videos
	- Used for video classification
	- Contains 1'133'157 videos and 487 sports labels
- YouTube8M
	- From Google
	- Used for video classification and retrieval
	- Composed of machine-generated annotations from 3'862 classes
	- Has audio-visual features
- Charades
	- Composed of crowdsourced "boring" videos of people doing daily activities
	- Used for action classification and sentence prediction
	- Contains 9'848 videos with RGB and optical flow features
	- Has video-level and frame-level classification, but no human localization
- Kinetics (DeepMind)
- Atomic Visual Actions (AVA)
	- By Berkeley and Google
	- Contains 57.6k segments of 3 seconds each
	- Used for pose and object interactions
	- It's fine-grained, but has no annotations about objects
- Moments in Time
	- From MIT
	- Contains 1'000'000 videos of 3 seconds each, with 339 verbs
	- It's not limited to humans
	- It's sound dependent
	- It's balanced, but only has a single label, making it suitable for classification but not detection
- M-VAD and MPII-MD
	- Video clips with descriptions (e.g. "SOMEONE holds a crossbow", "He and SOMEONE exit a mansion", ...)
	- Used for multimodal models bridging videos and natural language
- Sparsely Labeled ACtions Dataset (SLAC)
	- From MIT and Facebook
	- Contains 520k untrimmed videos with 200 classes and 1.75M clip annotations
- DALY
	- From INRIA
	- Contains spatial annotations:
		- Bounding box around the action
		- Upper body pose annotation, including bounding box around the head
		- Bounding box around objects involved in the action
- Large Scale Movie Descriptor Challenge (LSMDC)
	- Combination of M-VAD and MPII-MD
	- Used for various applications:
		- Movie description
		- Description prediction for 4-5 seconds movie clips
		- Movie retrieval
		- Video caption finding
		- Movie Fill-in-the-Blank (QA)
![[Pasted image 20260513124034.png]]

Video understanding is a more difficult task with respect of image understanding, mainly because of its characteristics and the challenges it poses:
- Computationally expensive
- Lower quality
- Resolution, motion blur, occlusion
- Requires lots of training data

Before deep learning usage in this field, the video understanding task relied on feature extraction of:
- local features, using HOG and HOF (Histogram of Optical Flow)
- trajectory based features
The extracted features were then aggregated via bag of visual words and Fisher vectors

In order to represent motion, before using Deep Learning, we could use Optical Flow or Trajectory Stacking:
![[Pasted image 20260513124735.png]]
With deep learning, expressing a video as a 3D signal with 2 spatial coordinates $(x, y)$ and one temporal coordinate $t$, by fitting $t$, we can understand a video as a sequence of images.

## Multiple Frames

![[Pasted image 20260513125304.png]]
With single frame models, the combination is commonly implemented as a small NN on top of a pooling operation. The limitation of this is that pooling is not aware of the temporal order.

To solve this problem, different ways to fuse features from multiple frames were implemented:
![[Pasted image 20260513125502.png]]

By using multiple frames we reduce spatial dimension to reduce model complexity, and we can achieve multi-resolution (low-res context + high-res foveate).
![[Pasted image 20260513125820.png]]

The interesting part of the paper where this was published[^1] is that the best single model was slow fusion, but the ensemble of all these fusion models was what worked best:
![[Pasted image 20260513125913.png]]

![[Pasted image 20260513131854.png]]
The limitation for the feed forward + static window approach is that increasing the length L of the window causes a fast increase in the number of parameters, the decisions are independent between time steps, and there's a cumbersome padding when there are not enough samples to fill the L size.

A possible solution is to instead use [[RNN|RNNs]], as they are well suited for processing sequences.
![[Pasted image 20260513132254.png]]
The problem with RNNs is that they are sequential and cannot be parallelized.

![[Pasted image 20260513132327.png]]

Another possibility is to use a 3D CNN (C3D).
By adding an extra dimension to standard CNNs, we obtain that:
- An image is a (iC, H, W) tensor, so we use (oC, iC, kH, kW) kernels
- A video is a (iC, T, H, W) tensor, so we use (oC, iC, kT, kH, kW) kernels
![[Pasted image 20260513132538.png]]

The difference with 2D convolutions is that 3D conv kernels move over 3 axes, learning features that encode temporal information.
![[Pasted image 20260513132631.png]]
![[Pasted image 20260513132642.png]]

In order to use C3D on longer videos, the video needs to be split into chunks (also known as *clips*), with a number of frames that fits the receptive field of the C3D (usually clips are composed of 16 frames):
![[Pasted image 20260513133333.png]]
In a C3D the filters need to learn both the object and the movement:
![[Pasted image 20260518094716.png]]

The main problem of the C3D is that it underperformed.
## Two Stream 2D CNNs

A different paradigm to including temporal features is to extract optical flow for a stack of frames and use it as an input to a CNN:
![[Pasted image 20260513134119.png]]

A more sophisticated idea is to apply the fusion not only at the end but between the intermediate conv layers. This is done because mid-level fusion allows the network to learn cross model interactions between the 2 streams, learning that a specific type of motion combined with a specific type of image is related to an action:
![[Pasted image 20260513134142.png]]
![[Pasted image 20260513134151.png]]

%% 2026/05/18 - From slide 53 %%

The two-stream solution is loosely inspired by neuroscience, where the ventral stream does the object identification, while the dorsal stream mediates the required sensorimotor transformations for visually guided actions directed at such objects
![[Pasted image 20260513134640.png]]

## Inflated 3D CNNs (I3D)

The author of I3D, in order to tackle the problem of low C3D performance, tried to modify the training process, training a 2D layer and plugging it into a 3D one in order to pass its knowledge to it:
![[Pasted image 20260518100238.png]]
In order to pass the 2D layer weights to the 3D layer, the kernel gets picked and stacked N times, and then it gets fine tuned.
The 3D models are initialized with ImageNet images transformed into a video sequence.
![[Pasted image 20260518101033.png]]
![[Pasted image 20260518101046.png]]

## Two-Stream I3D

A two-stream I3D is basically the same as the two-stream C3D but with an I3D:
![[Pasted image 20260518101205.png]]
This is a bit redundant, but it works better.
## Pseudo 3D Residual Networks (2D+1D) - ICCV2017

This is a set of networks that try to approximate 3D Networks in order to make them simpler.
To do so, they decompose the network:
![[Pasted image 20260518102024.png]]
These are technically 3D kernels, but there is at least one axis that does not support the temporal information ($1 \times 3 \times 3$ conv) and 2 axes which don't support spatial information ($3 \times 1 \times 1$ conv).
In this way we have one layer which takes into account the spatial differences and a different one which takes into account the temporal differences.
![[Pasted image 20260518102224.png]]

### Spatiotemporal Separable 3D - CVPR2018

This is basically the same as the previous one, as it was a concurrent work.
### ResNet (2+1)D - CVPR2018

Still, same as the previous one but with a different architecture.

## Non-local Neural Networks

These networks apply spatial-temporal attention among frames, interconnecting things that are distant from each other:
![[Pasted image 20260518102816.png]]



---

[^1]: Karpathy, A., Toderici, G., Shetty, S., Leung, T., Sukthankar, R., & Fei-Fei, L. . Large-scale video classification with convolutional neural networks. CVPR 2014
