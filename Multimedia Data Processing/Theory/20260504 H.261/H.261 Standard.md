---
course: Multimedia Data Processing
---

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
There is no indication on when to transmit INTRA or INTER, nor on the level of quantization to use or how to choose it, nor on when a block may not be transmitted (so that each video encoder can tackle different needs).

## Bitstream structure

The fields are bit-coded and are transmitted with the most significant bit first.
The structure of the stream is divided into 4 levels of layers:
- Picture
- Group of blocks (GOB)
- Macroblock (MB)
- Block
Each level is usually preceded by a header, except for the block.

### Picture layer

The picture layer is composed of:
- Picture start code (PSC) - 20 bits: `0000 0000 0000 0001 0000`
	- This is not byte aligned
	- A search for a PSC requires a bit-by-bit scan
- Temporal Reference (TR) - 5 bits: value from 0 to 31 which is increased by one each time
	- Tracks any skipped frame
- Type information (PTYPE) - 6 bits: a bitmapped field where the fourth bit represents the picture type
	- QCIF is `0`
	- CIF is `1`
- Extra insertion information (PEI) - 1 bit: If `1` indicates that there is a byte of additional information (PSPARE) following
	- The standard says not to insert them and to ignore those that meet until they are defined (which never happened). 
	- All the following continues with PEI until this is 0

### GOB layer

Each picture is divided in 12 GOBs:
![[Pasted image 20260504115621.png]]

Each GOB layer is composed of:
- Group of Blocks Start Code (GBSC) - 16 bits: `0000 0000 0000 0001`
- Group Number (GN) - 4 bits: number indicating the GOB number:
	- 0 corresponds to PSC
	- 13, 14, 15 are not used
	- This is useful to skip sending the GOB if it's equal to the preceding one
- Quantizer information (GQUANT) - 5 bits: quantization value to use for all blocks in the GOB
- Extra insertion information (GEI) - 1 bit:
	- Same mechanism as [[#Picture layer|PEI]]
	- In this case the information is called GSPARE

### Macroblock layer

Each GOB is divided into 11 x 3 macroblocks of size 16 x 16
![[Pasted image 20260504120123.png]]

Each macroblock starts with a Macroblock Address (MBA) coded at variable length (variable length code or VLC).
For the first MB transmitted, its absolute address is sent (from 1 to 33), while for subsequent ones the difference between the current address and that of the previously transmitted MB is sent (prediction of the MBA).
At this stage it is possible that, instead of meeting the VLC of an MBA, a start code (PSC or GBSC) is encountered, which means that the current GOB has ended (it may not contain macroblocks).
There is also a VLC that allows to enlarge the bit stream, for example to obtain exactly a certain bit rate, in cases where compression reduces it excessively (used very rarely).

Differently from [[JPEG Compression|JPEG]], the standard does not allow to change the Huffman table.
![[Pasted image 20260504120740.png]]

The second variable length field is the Type information (MTYPE), which provides information on the macroblock and the elements present.
![[Pasted image 20260504121218.png]]



