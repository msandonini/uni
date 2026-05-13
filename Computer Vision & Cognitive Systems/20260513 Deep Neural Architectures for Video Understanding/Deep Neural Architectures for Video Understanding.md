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

## Single Frame Models

![[Pasted image 20260513125304.png]]
Combination is commonly implemented as a small NN on top of a pooling operation. The limitation of this is that pooling is not aware of the temporal order


