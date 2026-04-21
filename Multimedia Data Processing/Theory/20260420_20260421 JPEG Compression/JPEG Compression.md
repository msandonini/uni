---
course: Multimedia Data Processing
---

JPEG is an abbreviation for *Joint Photographic Experts Group*, and it is a standard for the compression of static images in continuous color tones.
It was designed to encode photographic images, as opposed to computer-generated synthetic images.

Since it is a standard, it's not a single algorithm, but simply defines how the image must be stored, in order to make it possible to have different implementation techniques.
The standard is based on the usage of different techniques:
- Encoding via [Discrete Cosine Transform (DCT)](https://en.wikipedia.org/wiki/Discrete_cosine_transform)
- Run Length Encoding (RLE)
- Huffman Encoding

JPEG has different operating modes:
- Lossless JPEG
- Sequential (baseline) JPEG
	- The everyday implementation of JPEG
- Progressive JPEG
	- Progressive type of loading, where it first loads a blurry image, and then the definition gets better with more loading passes.
- Hierarchical JPEG
	- Designed for very big images divided in zoom-able chunks

## Lossless JPEG

Lossless JPEG exploits a linear prediction technique.
The idea is to exploit the idea that if I predict the following pixel I can avoid to store it since I am already able to predict it.
The problem with this idea is that it's impossible to predict correctly the next pixel, but if we are able to say what it will likely be, we get close to the real value, and then we can send the error with respect to the prediction.
This is better since we are changing the way in which we represent the images from just colors to the errors, which will have a great probability of being small.

The residual image is constructed as the difference between the current pixel x and the y value obtained with the prediction. The residual image is then compressed with Huffman

In lossless JPEG we have 8 different prediction schemes:
- $y = 0$
- $y = a$
- $y = b$
- $y = c$
- $y = a + b - c$
- $y = a + \frac{b - c}{2}$
- $y = b + \frac{a-c}{2}$
- $y = \frac{a+b}{2}$

## Baseline JPEG

JPEG is a color-blind compression algorithm, as it does not care what it is compressing. The input is an array of n-bits per pixel values. If the image is in color (e.g. RGB) each plane is compressed separately.

![[Pasted image 20260420114114.png]]

Each pixel is scaled by subtracting $2^{n-1}$ from it.
The image is divided in non-overlapping 8x8 blocks, where each one is then processed with the DCT transform obtaining 8x8 coefficients (first pass where we have data loss).
The coefficients are quantized (divided) using a table specified by the standard, which provides a different quantization value for each frequency (second pass where we have data loss).
The coefficients are sorted using a zig-zag path, and then they are encoded using a variable bit length entropic encoder (Huffman encoding tables).

![[Pasted image 20260420114136.png]]
>[!INFO] Image
>In the image we see the usual zig-zag paths used for sorting the coefficients

The biggest data loss happens in the quantization process, as the quantization is a really aggressive operation.

![[Pasted image 20260420114114.png]]

### DCT

The DCT is a variant of Fourier Transform, which however employs only the cosine in order to remain in the real domain.
It has interesting properties for compression, since it separates the spatial frequencies by polarizing the lower ones at lower values of the coefficients.
$$
\begin{align}
N &= 8 \\
S_{u} &= C_{u} \sum_{x=0}^{7} s_{x} \cos \frac{\pi(2x + 1) u}{16} \hspace{5mm} ; \hspace{5mm} u = 0, \dots, 7 \\
C_{u} &= \frac{1}{2 \sqrt{ 2 }} \\
 \\
& [1, 2, 3, 4, 5, 6, 7, 8] \rightarrow [S_{0}, S_{1}, \dots, S_{7}]
\end{align}
$$
- $S$ is the transformed signal
- $C$ is the normalization (scaling coefficients)
- $u$ is the point in which we are computing the transform
- s is the original vector we are transforming
$S_{0}$ is just the sum of all the coefficients $S_{x}$

![[Pasted image 20260420121709.png]]

Basically the DCT changes the base of the vector space, so obtaining the correct base we get a different representation of the same stuff, and this base change allows us to describe the frequency changes of our data.
This different representation is useful in image compression since by moving from pixels to frequencies we changed the probability distributions of the symbols.
Also, the human eye is not uniformly able to capture frequency changes in images, as it perceives low frequencies better than high ones, so if I make a mistake on higher frequencies, the error is perceived less than an error on lower frequencies, allowing us to be more aggressive in the quantization of higher frequencies (so that we can reduce the amount of data while still having low perceivable error).

In the DCT the first value of each block (the one at position $(0, 0)$, being the low frequency one, is called `DC` coefficient, while the other ones are called `AC` (because as alternate current they have higher frequencies than the direct current).

The `DC` coefficient is encoded differently with respect for each block, and it is proportional to the average of the pixel values in the block.
The `DC` coefficient is compressed differently from the `AC` coefficients, since the average value of a block will be similar to that of the neighboring blocks.
The `DC` coefficients are then encoded by difference with respect to the previously encoded block.

The direct (forward) and inverse DCT functions are as follows:
$$
\begin{align}
&\text{FDCT} \hspace{5mm} S_{uv} = \frac{1}{4} C_{u}C_{v} \sum_{y=0}^{7} \sum_{x=0}^{7} s_{xy} \cos \frac{(2x + 1) u \pi}{16} \cos \frac{(2y + 1) v \pi}{16} \\
&\text{IDCT} \hspace{5mm} s_{xy} = \frac{1}{4} \sum_{v=0}^{7} \sum_{u=0}^{7} C_{u}C_{v}S_{uv} \cos \frac{(2x + 1) u \pi}{16} \cos \frac{(2y + 1) v \pi}{16} \\
&C_{x} = \begin{cases}
\frac{1}{\sqrt{ 2 }} & x=0 \\
1 & \text{otherwise}
\end{cases}
\end{align}
$$

Since we need to encode the `DC` coefficient, and we are working with 8-bit/pixel value maps, 11-bit precision `DC` coefficients are obtained, so differential coding will require 12-bit precision.
A category table is defined for `DC` values with 12 possible ranges of values.
A 4-bit index called `SSSS` allows to identify from which category the current coefficient belongs to, and a Huffman table is then defined with the `SSSS` variable length encoding.

The DC coefficient for the current block is calculated, then we subtract the previously coded value from this by creating the `DC` differential coefficient (`DIFF`).
The value of the `SSSS` category to which `DIFF` belongs is found, and for each category `SSSS` bits are added to the `SSSS` Huffman code to identify which `DIFF` was generated.
When DIFF is positive, the least significant `SSSS` bits of `DIFF` are added, and when `DIFF` is negative the least significant `SSSS` bits of DIFF - 1 are added. In practice the first bit of those added is 0 if `DIFF` is negative and 1 if positive.

`AC` encoding is similar, but instead of using `SSSS` we use `NNNNSSSS`, where `NNNN` represents the number of null coefficients encountered by the last coded coefficient and before the current one.

The syntax of the bit string is rather complex, but broadly speaking the concept is that the data is divided into blocks hierarchically ordered.
Before each block we have a marker (`FF`), which identifies a segment of file. The marker is followed by 2 bytes which indicate the length of the segment (in bytes).
When, during an encoding, the `FF` byte is created in the output string, a `00` is also added (the string is stuffed with an extra byte, which is why this is called *byte stuffing*).
If after an `FF` byte the decoder sees a `00`, it ignores it. If the byte is not a `0`, it must be a marker.
At the end of the encoding of any block, if a completely full byte is not obtained, we add as many `1`s as needed to complete the byte.

If we consider the R, G, and B components, it could be done as following:
![[Pasted image 20260421141703.png]]

However, for this situation the [JFIF (JPEG File Interchange Format)](https://en.wikipedia.org/wiki/JPEG_File_Interchange_Format) format has been defined, which provides the following transformation:
![[Pasted image 20260421141829.png]]
In this way, the color components are sub-sampled by reducing the size to one quarter of the original.


