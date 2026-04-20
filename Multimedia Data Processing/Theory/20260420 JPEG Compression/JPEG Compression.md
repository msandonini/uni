JPEG is an abbreviation for *Joint Photographic Experts Group*, and it is a standard for the compression of static images in continuous color tones.
It was designed to encode photographic images, as opposed to computer-generated synthetic images.

Since it is a standard, it's not a single algorithm, but simply defines how the image must be stored, in order to make it possible to have different implementation techniques.
The standard is based on the usage of different techniques:
- Encoding via Discrete Cosine Transform (DCT)
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



