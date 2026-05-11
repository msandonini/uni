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




