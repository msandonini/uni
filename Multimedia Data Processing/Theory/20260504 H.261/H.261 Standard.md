H.261 was introduced in 1990, and it is the first "modern" standard for video encoding

The standard title is "Video codec for audiovisual services at p x 64 kbit/s". This was initially designed for transmission over ISDN lines, which allowed bi-directional traffic at 64 kbps, therefore by using several lines in parallel it was possible to obtain a band of $p \times 64$ kbits, with $p$ being the number of lines, up to a max of 30.

The goal of the standard was video telephony, so the whole standard ignores the use of reference points for random access search on a stream.

The standard supports 2 different frame sizes:
- Common Interchange Format (CIF), at 352 x 288 pixels
- Quarter-CIF (QCIF), at 176 x 144 pixels

The images are coded as [[Color and its representation#Transmissive color spaces|YCbCr]], with the chrominance components subsampled by half in width and height (for every 4 values of Y there are 1 value of Cb and 1 of Cr).
As with [[Video Compression#Time difference|Motion Vector]] each 16 x 16 pixels macro block contains four 8 x 8 blocks of Y and on 8 x 8 block respectively for Cb and Cr.
![[Pasted image 20260504112840.png]]

The H.261 standard does not work with entire frames, but the fundamental unit to which the previous scheme is applied is the Macroblock, therefore there are no INTRA or INTER frames.
In each frame there can be INTER or INTRA macroblocks, so some macroblocks transmission can be avoided if these are sufficiently similare to those of the previous frame.
There is also a loop filter which, after the creation of the image, allows to smooth the variations within the block. This is a low-pass filter with values that can be easily implemented with integer arithmetic and shifts.

The 2D version is represented by the matrix:
$$
\begin{bmatrix}
\frac{1}{16} & \frac{1}{8} & \frac{1}{16} \\
\frac{1}{8} & \frac{1}{4} & \frac{1}{8} \\
\frac{1}{16} & \frac{1}{8} & \frac{1}{16}
\end{bmatrix}
$$
This is very close to a Gaussian filter with $\sigma = 0.8$.

The usage of this loop filter has a very low computational cost and allows to slightly reduce the blocky effect given by compression. 
The standard also provides that up to 3 frames can be skipped per transmitted frame in order to reduce the frame rate.
In addition, to prevent the overall image quality from being excessively low, each macroblock must be transmitted INTRA at least once every 132 times it is transmitted.
There is no indication on when to transmit INTRA or INTER, nor on the level of quantization to use or how to choose it, nor on when a block may not be transmitted.

