---
course: Multimedia Data Processing
---

From a technical point of view, the video is just a sequence of images, obtained by temporal sampling.
The [PAL](https://en.wikipedia.org/wiki/PAL) standard, used in Europe, plans to send 25 images per second.

A possible solution for encoding the video could be to store all the images in a single data stream containing raw data, but this would require a memory occupation of $W \cdot H \cdot BPP \cdot FPS$, where:
- $W$ is the width
- $H$ is the height
- $BPP$ is the number of bits per pixel
- $FPS$ is the number of images (frames) per second
A 1.5 hours gray level video (8 bpp) with a resolution of $720 \times 576$ at 25 fps would occupy 52.14 GB.

As with images, it's possible to take advantage of the spatial redundancy within each frame to reduce occupancy.
For example, if we apply [[JPEG Compression|JPEG]] encoding to each image the compression would be about of 1:10.
This type of encoding is known as [M-JPEG](https://en.wikipedia.org/wiki/Motion_JPEG) (Motion JPEG).
Unfortunately, even in this way the space requirements would be too high: in the previous example, we would obtain that a 1.5-hour film would occupy (without considering the audio) 5.21 GB, approaching the maximum capacity of a DVD.

## Time difference

The first possible approach is to use the previous frame to predict the current one.
Based on the idea that 2 near frames are extremely similar, unless some small variation due to the acquisition, they are substantially indistinguishable.

Obviously, the differences between two 8 bpp images (values in the range $[0,255]$) are in the range $[-255,255]$, so to bring them back into the visible range you can divide (integer division) by 2 and add 127.

By observing the distribution of the difference values, it can be observed that this is very narrow and very non un-uniform. The entropy of this distribution is 4.06, therefore using a variable length coding it is possible to halve the size of the original frame, even without loss.

![[Pasted image 20260421143949.png]]
![[Pasted image 20260421144009.png]]
![[Pasted image 20260421144026.png]]

This is however based on the assumption that the scene changes little to nothing. If we introduce movement, things change dramatically, as if we move the camera a little in the previous example we obtain an entropy of about 6.17:

![[Pasted image 20260421144046.png]]
![[Pasted image 20260421144102.png]]
![[Pasted image 20260421144129.png]]

To solve this we could encode some movement information, however it does not work in the case of an object moving in the front of the camera.

A possible solution to improve the prediction would be to send information on the displacement vector of each pixel, followed by the difference (prediction error).
However, this is inapplicable, since the displacement vectors would cause an increase in the amount of data, such as to cancel the benefits of the prediction itself.

For this reason, all video compression standards use a trade-off strategy: a *motion vector* is sent for groups of pixels.

The most used block size is $16 \times 16$ (used in [H.261](https://en.wikipedia.org/wiki/H.261), [MPEG-1](https://en.wikipedia.org/wiki/MPEG-1), [MPEG-2](https://en.wikipedia.org/wiki/MPEG-2), [MPEG-4](https://en.wikipedia.org/wiki/MPEG-4)). These are called macroblocks.

The choice to use the $16 \times 16$ macroblocks is due to the simple correspondence between the color planes. In fact, as seen for JPEG, the color is represented using one luminance component and two chrominance components (`YCbCr`) and the chrominance components are then sub-sampled with a $\frac{1}{2}$ factor both in height and in width. So every 4 $8\times8$ blocks on `Y` there are 1 block `Cb` and 1 block `Cr`.

The Motion Vector is a pair $(x, y)$ that indicates, for the current block, in which position of the previous image the most similar block is located.
The position, as the name suggests, is indicated as a displacement vector with respect to the current coordinates, therefore $x$ and $y$ can also have negative values.
Generally, it is not allowed to indicate motion vector that would cause the block of the previous image to be partially outside the image.

In the context of compression, being "similar" means having small differences. With the aim to minimize the [SAD](https://en.wikipedia.org/wiki/Sum_of_absolute_differences) (Sum of Absolute Differences i.e. sum of the absolute values of the differences), a search is carried out.
There are many techniques for carrying out this search, which produce results more or less close to the optimum, which is obviously easily obtainable by carrying out an exhaustive search (try all possible motion vectors, measure the SAD and keep the one that provides the minimum result) .

![[Pasted image 20260421150735.png]]
>[Power-Aware Multimedia: Concepts and Design Perspectives](https://www.researchgate.net/publication/3432475_Power-Aware_Multimedia_Concepts_and_Design_Perspectives)
>Block Matching Motion Estimation. An image is partitioned into 16 × 16 Macro Blocks (MBs). For each MB, the best-matched MB is searched in a $[−p, (p − 1)]$ search range. Sum of Absolute Difference (SAD) is adopted as the criterion for the matching.

![[Pasted image 20260421151204.png]]

By having the previous frame and the motion vector, it is possible to build an image composed of macroblocks of the previous frame, displaced by what is indicated by the motion vector. This operation is called [motion estimation](https://en.wikipedia.org/wiki/Motion_estimation).
This predicted image allows to reconstruct the frame with lower differences and therefore with probable saving of space.

Unfortunately, the space occupied by motion vectors must also be added. It is therefore necessary to introduce a trade-off between the space saved by reducing the differences and the one "wasted" by the motion vector.

To do this, for example, it is possible to add a motion vector only if the SAD of the optimal block and that of the corresponding block $[MV = (0,0)]$ have a difference greater than a predetermined threshold.

- Frame B:
![[Pasted image 20260421151630.png]]
- Predicted image:
![[Pasted image 20260421151711.png]]
- Difference image (B - A):
![[Pasted image 20260421151736.png]]
- Difference image (B - Prediction of B):
![[Pasted image 20260421151817.png]]

## Lossy compression

As for image compression, not all information must be transmitted unaltered to allow to appreciate the video content, even with excellent quality; it is therefore possible to transmit the pixels encoded as inter frames or the differences encoded as intra-frames, accepting a loss in their representation.

The loss should take place on the less significant components of the data, therefore we try to represent the data through a transformation that separates the different information from the contents.

The main transformation used in video encoding is [DCT](https://en.wikipedia.org/wiki/Discrete_cosine_transform), followed by a quantization (integer division).

Different quantization levels of the DCT coefficients produce drastic reductions in the width (uniformity) of the distribution:
![[Pasted image 20260421152322.png]]





---

Useful papers:
- [Fast disparity estimation algorithm for mesh-based stereo image/video compression with two-stage hybrid approach](https://homepage.ntu.edu.tw/~lgchen/publication/paper/[C][2003][VCIP][Shao-Yi.Chien][1].pdf)
- [A fast and high subjective quality sprite generation algorithm with frame skipping and multiple sprites techniques](https://homepage.ntu.edu.tw/~lgchen/publication/paper/[C][2002][ICIP][Shao-Yi.Chien][1].pdf)
- [Power efficient sum of absolute difference algorithms for video compression](https://www.iosrjournals.org/iosr-jvlsi/papers/vol1-issue6/C0161018.pdf)
- [Appraisal of motion estimation techniques in video compression](https://iopscience.iop.org/article/10.1088/1742-6596/1706/1/012070/pdf)
- [Adaptive Recurrent Frame Prediction with Learnable Motion Vectors](https://dl.acm.org/doi/10.1145/3610548.3618211)
