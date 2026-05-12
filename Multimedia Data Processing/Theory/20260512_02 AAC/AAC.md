---
course: Multimedia Data Processing
---
AAC is a lossy audio coding format designed to be the MP3 successor.
It is defined in ISO documents ISO/IEC 13818-7 and ISO/IEC 14496-3 as part of the MPEG2 and MPEG4 standards.

It introduces many improvements but the overall structure of the encoder is still very similar to that of an MP3 encoder.
Both MP3 and AAC are perceptual audio coding systems.

The AAC format can work with audio signals sampled using sampling rates ranging from 8 kHz to 96 kHz.
It is a multichannel format that supports up to 48 regular audio channels and up to 16 additional LFE channels (Low Frequency Effect) dedicated to audio signals in the 3 – 120 Hz band.

AAC supports both CBR (Constant Bit Rate) coding and VBR (Variable Bit Rate) coding.
The encoding exploits many perceptual and psychoacoustics techniques to achieve the best compression results, such as:
- Block switching
- Prediction
- Temporal Noise Shaping
- Masking effects
- Non-uniform quantization
Huffman coding is used in the last encoding steps (noiseless coding).

The basic task of a perceptual audio coding system is to compress the digital audio data in a way that:
- the compression is as efficient as possible
- the reconstructed (decoded) audio sounds exactly (or as close as possible) to the original audio before compression.
Other requirements may include:
- Low complexity (in order to make encoding and decoding as inexpensive as possible for both software and hardware)
- Flexibility (to make the encoder usable in different scenarios)
Perceptual audio coding is a lossy compression technique.

![[Pasted image 20260512150830.png]]

The quantization process introduces noise in the reconstructed signal.
The goal is to shape the introduced quantization noise to reduce the noise perceived by the human auditory system.
Psychoacoustic and perceptual models are employed.
![[Pasted image 20260512150952.png]]
![[Pasted image 20260512151103.png]]

## Sub-band processing

The  sub-band analysis filter-bank transforms the input audio signal in its spectral representation.
The input audio is analysed by means of a sliding window of N samples in order to produce N spectral coefficients.
The spectral analysis has many purposes:
- Spectral coefficients are used to calculate masking information
- Spectral coefficients will be quantized and coded in the final bit stream (as in the [[JPEG Compression | JPEG encoder]]).
![[Pasted image 20260512151906.png]]

AAC uses the Modified Discrete Cosine Transformation (MDCT) to calculate spectral coefficients (in other words MDCT is used as a filter-bank):
$$
X_{k} = \sum_{n=0}^{2N-1} x_{n} w_{n} \cos\left[ \frac{\pi}{N}\left( n+\frac{1}{2}+\frac{N}{2} \right) \left( k + \frac{1}{2} \right) \right] \hspace{1cm} k \in [0, N-1]
$$
The inverse transform used to obtain samples from the spectral coefficients is called Inverse MDCT (IMDCT):
$$
y_{n} = \frac{2}{N} w_{n} \sum_{k=0}^{N-1} X_{k} \cos \left[ \frac{\pi}{N} \left( n + \frac{1}{2} + \frac{N}{2} \right) \left( k + \frac{1}{2} \right) \right] \hspace{1cm} n \in [0, 2N - 1]
$$
The MDCT produces N coefficients from 2N input values.
Viceversa the IMDCT produces 2N values from N spectral coefficients.
To obtain N coefficients from N samples the overlap-add technique is used.

MDCT is a modified version of the type IV of the DCT (DCT-IV).
It is also a lapped transform, which means that it is performed over 50% overlapped blocks of the input signals.
![[Pasted image 20260512153424.png]]
MDCT is used since by it being a lapped transform, blocking artifacts are reduced, and also because it has a property called time-domain aliasing cancellation (TDAC), which makes it possible for the inverse transform to remove the introduced aliasing, permitting perfect reconstruction of the original signal.

With analysis/synthesis via MDCT the input audio signal is padded with L zeros at the beginning and at the end in order to not lose any information around the edges.
The MDCT is applied on subsequent couples (this is called overlap operation) of L samples each in order to produce L coefficients.
Then the audio samples values are reconstructed by adding the second half of the previous reconstructed window with the first half of the current one, hence why MDCT is called a lapped transform.
![[Pasted image 20260512154115.png]]

An AAC encoder always processes a 2048 audio samples at a time.
A block of 2048 samples is called *frame*.
The MDCT can be applied on same windows of different length.
AAC supports 2 different window lengths:
- 2048 is the regular size
- 256 is used when a transient is detected in the audio samples (i.e. a drum hit)
This technique is called block switching, and it is employed to better represent short and sudden variations in the audio samples.
For each frame processed by the encoder 2 situations may occur:
![[Pasted image 20260512154356.png]]


