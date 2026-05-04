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

Following the MTYPE, the following fields may be present:
- Quantizer (MQUANT) - 5 bits: indicates that from here on the quantization value must be the one indicated
- Motion vector data (MVD)
	- If a block is of the MC type, 2 VLCs are provided, one for the vertical and one for the horizontal components.
	- The values are the difference from the previous one, which is considered (0, 0) if we are at 1, 12, 23 MB, if the previous was skipped, or if the previous was not MC.
	- A further optimization is carried on, as the difference between the components of 2 MVs, by them being limited between $\pm 15$, is in the range $\pm 30$.
	- Knowing the value of the previous component only 31 of the 61 values are possible, so in the VLC table for MVDs 2 different values correspond to the same VLC. The correct value is the one that makes fall in the ragne $\pm 15$.

![[Pasted image 20260504123132.png]]

The last field of the Macroblock layer is the Coded Block Pattern (CBP).
This field is a 6-bit bitmap indicating which blocks are present in the MB.
The blocks are numbered like this:
![[Pasted image 20260504123314.png]]
Each CBP is associated with a VLC in order to further compress this field too.

![[Pasted image 20260504123400.png]]

## Block layer

In the Block layer the coefficients of the transform (TCOEFF) of the blocks indicated in the CBP are coded according to the zig-zag order. If the MB is INTRA, all the blocks are present.

All the coefficients of the transforms, both INTRA and INTER, except the first one, are represented as a pair (run,level), which indicates the number of null coefficients preceding the non-zero level that is being coded.
Typically the pairs (run,level) are present in the following table. Those that are not present are encoded with a 20-bit word: escape, run, level. escape is code 0000 01, run is a 6-bit unsigned integer and level is an 8-bit two's complement signed integer. Obviously, level cannot be zero.
![[Pasted image 20260504123618.png]]
The last bit "s" indicates the level sign:
- `0` if positive
- `1` if negative

At the end of each block there is an end of block (EOB) 10 code, which indicates that all the other coefficients are null. 
The first coefficient for INTRA blocks is simply coded with 8 bits, except for the value 128 (`1000 0000` in binary) which is replaced by 255 (`1111 1111`) in order not to create false start codes.

The first coefficient for INTER blocks uses the same table as the others, but since it cannot be an EOB, it shortens the combination by one bit (run=0, level=± 1) (see table)

The level is basically the quantization coefficient.

Quantization in H. 261 is defined in terms of reconstruction, i.e. the inverse operation that must be performed to switch from quantized to dequantized (reconstructed) values. The formula is as follows:

$$
\begin{align}
&\text{QUANT is odd:} \\
&\begin{cases}
\text{REC} = \text{QUANT} \cdot (2 \cdot \text{level} + 1) & \text{level}>0 \\
\text{REC} = \text{QUANT} \cdot (2 \cdot \text{level} - 1) & \text{level}<0
\end{cases} \\ \\

&\text{QUANT is even:} \\
&\begin{cases}
\text{REC} = \text{QUANT} \cdot (2 \cdot \text{level} + 1) -1 & \text{level > 0} \\
\text{REC} = \text{QUANT} \cdot (2 \cdot \text{level} - 1) +1 & \text{level < 0} \\
\end{cases} \\
 \\
&\text{REC} = 0 \hspace{.5cm} \text{level}=0
\end{align}
$$

The $2 \cdot \text{level}$ in the reconstruction formulas is present because the DCT coefficients are divided by 2 x QUANT during the coding. So the quantization goes from 2 to 62 (QUANT is always between 1 and 31).
A simpler fixed division by 8 is used for the DC coefficient of the INTRA blocks.
