---
course: Multimedia Data Processing
---
## MPEG

Moving Picture Expert Group (MPEG) has worked to create the specification within the ISO and the IEC.

The MPEG-1 and MPEG-2 standards are both based on discrete cosine transform on block and motion compensation.

MPEG-1 and MPEG-2 have been widely used for applications such as DVD, broadcast via satellite and terrestrial digital.

MPEG-1 was made permanent in 1991 ad was originally optimized to work on 352x240 pixel resolution at 30 fps (NTSC) or 352x288 pixels at 25 fps (PAL).
In the standard this is called Source Input Format (SIF) video.

Even if often it is thought that MPEG-1 is limited to the NTSC and PAL sizes, it actually supports up to 4095x4095 pixels and 60 fps.
The bitrate is optimized for applications with 1.5 MB/sec, but this is not forced in the standard.

MPEG-1 works us defined only for progressive frames, and it does not have support for applications that use interlaced video, such as TV applications.
For this reason, MPEG-2 was introduced in 1994, as it fulfilled exactly this type of needs and introduced the concept of scalability.
With MPEG-2 the reference bitrate was also pumped up to a range between 4 and 9 MB/sec, thus potentially allowing very high video quality.

The first and fundamental difference is that the concept of key-frame is introduced, which is a frame from which you can “restart" as if you were at the beginning of the video.
This type of frame is called intra, hence the name “I-frames". In I-frames, all macroblocks must be intra, with no reference to the previous blocks.
The other frames are called P-frames, as in predicted, because they can also contain macroblocks with references to other frames. Specifically to previously transmitted frames.
It is important to note that there can also be intra macroblocks in P-frames, as is the case with H.261

The second difference is in the quantization of the coefficients of the discrete cosine transform. The quantization in this case is not uniform, but is weighed for two arrays that by default are as follows:
![[Pasted image 20260508092049.png]]
There is also a scale factor in the range (0.0,1.0] that is multiplied by each of the values, allowing quantization to be adjusted during encoding.

From what we said, the frame structure would such a dependency as following:
![[Pasted image 20260508092240.png]]
Unfortunately, in many cases the information that is used to make the prediction is not available in the previous frame
![[Pasted image 20260508092316.png]]
While considering the frame in the middle, we can't find information about what was under the circle in the previous frame but, if we could look at the next frame, we would have that information, so MPEG adopted the solution of defining a third type of frame, called bidirectional frame or B-frame, which looks for macroblocks in previous and following frames:
![[Pasted image 20260508092504.png]]

### Video layer

An MPEG video is divided into a hierarchy of layers that allows the handling of any transmission errors, stream search, editing, and audio synchronization:
- The first layer is called video sequence layer, and is a complete video with no external references (such as a movie or advertisement)
- The second layer is the GOP, which is the Group of Pictures: one or more I frames and possibly P or B frames
- The third layer is the picture, then divided in slices. Each slice is a sequence of macroblocks (typically a multiple of the row). Each slice is then composed of macroblocks and blocks, similarly to H.261
Each one of these layers has its own 32-bit start code, defined in the MPEG syntax, and consists of 23 bits set to `0`, followed by a `1`, then followed by 8 bits that specify which start code we're actually looking at.

### B-frames

Introducing forward prediction significantly complicates data stream management.
As an example, let's consider a sequence of frames like the following:
$$
\begin{align}
GOP_{0} &= I_{0}B_{1}B_{2}P_{3}B_{4}B_{5}P_{6}B_{7}B_{8} \\
GOP_{1} &= I_{9}B_{10}B_{11}P_{12}\dots
\end{align}
$$
In this case, frame 0 is type I, so it can be decoded without any other information. Frame 3 is predicted and will need information from frame 0, frames 1 and 2 will instead refer to frames 0 and 3.
So, in this case, we need frame 3 before 1 and 2 can be decoded, so it's useless to transmit them first.
This is why in the stream we will find this:
$$
\begin{align}
GOP_{0} &= I_{0}P_{3}B_{1}B_{2}P_{6}B_{4}B_{5} \\
GOP_{1} &= I_{9}B_{7}B_{8}P_{12}B_{10}B_{11}\dots
\end{align}
$$
Not all of the information needed to decode $GOP_{1}$ is within it, as frames 7 and 8 depend on frame 6, which is  inside of $GOP_{0}$.

The fact that for each macroblock in a B-frame there can be a backward reference, a forward one, or both, means that the current macroblock is predicted as an interpolation between a previous macroblock and a subsequent one.
![[Pasted image 20260508093752.png]]

In order to address these problems MPEG has a greater time distance between frames I and P, and so it becomes necessary to expand the motion vector search area ($\pm 32$ pixels).
Moreover, motion vectors are specified with a precision of half a pixel for more effective encoding. This means that two whole positions must be interpolated to obtain the correct reference.

Thanks to the bitstream syntax, it is also possible to access the desired location (random access) and to fast forward effortlessly, decoding only P frames, or only I, or an I every n.
Also, the notion of slices allows for faster synchronization after data loss.
![[Pasted image 20260508094206.png]]


