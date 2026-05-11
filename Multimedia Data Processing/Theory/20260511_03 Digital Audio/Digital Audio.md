---
course: Multimedia Data Processing
---
The transformation of the signal from analogue (continuous) to digital (discreet) is called sampling.
The etymology of this word comes from the fact that samples are picked up from the original signal, undergoing this process at regular time intervals (sampling frequency).

Nyquist's theorem states that, when sampling is carried out at a frequency equal to at least double the band of the signal being sampled, the transition from analogue to digital takes place without any loss of information.
Unfortunately, in the chain of operations carried out to recover the analogue signal starting from stored samples, we'll nevertheless have some loss of information if we compare it to the original signal.
The lower the sampling rate than the signal band, the more new aliasing frequencies emerge.

Sampling a signal at frequency f means extracting f samples per second from the signal.
In the case of an audio signal sampled with CD standard, 44100 samples are extracted each second. Every sample is represented by a binary 16 bit number.
So, a stereo signal produces the following number of samples per second:
$$
2 (\text{stereo}) \times 16 (\text{bit}) \times 44100 (\text{samples}) = 1 411 200 \text{ bps}
$$
If we wanted to express this result in bytes we would have:
$$
\frac{1411200}{8} = 176400 \text{ bytes} = 172.26 \text{ Kb}
$$