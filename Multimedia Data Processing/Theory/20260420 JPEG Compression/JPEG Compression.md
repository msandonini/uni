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

