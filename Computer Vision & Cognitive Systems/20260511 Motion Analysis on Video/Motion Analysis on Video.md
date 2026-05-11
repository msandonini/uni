---
course: Computer Vision and Cognitive Systems
---
## Sparse Optical Flow

Optical flow should not be computed in all points but only for points where the brightness feature is significant.
%% Slide 49 - KLT Kande Lucas Tomasi Feature Tracking

![[Pasted image 20260511092026.png]]

In order to enable feature tracking on optical flow, we can extract regions of interest by thresholding the magnitude of motion vectors, and then perform k-means clustering for each connected region.
By doing this, we obtain an image where color intensities gives information on object boundaries to counter the smoothing of motion vectors across edges in optic flow estimate.
![[Pasted image 20260511092447.png]]

There also are some algorithms like the SIFT flow, where instead of using Harris we use SIFT to extract and track keypoints, and this has better results than Harris.

## Dense Optical Flow

Dense optical flow methods use Deep Learning to do estimation, but as such they need a ground truth.
In order to get such ground truth the models get trained on synthetic data.

Dense optical flow models are usually CNNs, modeled as to obtain the following result:
$$
(u, v) = f(I_{t-1}, I_{t})
$$
In this case:
- $u$ is the motion vector in the $x$ direction
- $v$ is the motion vector in the $y$ direction
- $f$ is the CNN
- $I_{t}$ and $I_{t-1}$ are two consecutive frames

Having the $I_{t}$ and $I_{t-1}$ frames of shape $(c, x, y)$, and giving them to the CNN, what we obtain is a vector of shape $(2, x, y)$, because we have one channel for $u$ and one channel for $v$.

To train these models we have few datasets:
- Flying chairs
- MPI Sintel

### Supervised NN-based dense flow estimation (Flownet)

![[Pasted image 20260511095733.png]]

#### Flownetsimple

Flownetsimple is a network used to compare 2 frames of $(c, x, y)$ shape.
To do so, we stack them in a single $(2\cdot c, x, y)$ frame in order to pass them to the CNN as a single image.
In reality, Flownetsimple did not work by stacking 2 images but by stacking 6.
![[Pasted image 20260511100323.png]]
It consists only of conv layers, and it allows the network to decide itself how to process and extract the motion information.

#### Flownetcorr

Flownetcorr, instead of stacking the images, firs processes them separately, and then it correlates their features at different locations and process further.
![[Pasted image 20260511100456.png]]
In this case we have 2 separate, yet identical processing streams.
The network first produces meaningful representation of 2 images separately and then combine at a later stage.
This works more like a matching approach.

The advantage with respect to Flownetsimple is that Flownetcorr, working on the single image, is able to recognize objects before extracting movement, while Flownetsimple just forces the recognition from the start by looking at the differences between channels.
