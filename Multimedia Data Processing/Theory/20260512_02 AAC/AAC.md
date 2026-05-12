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

