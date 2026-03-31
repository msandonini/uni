## 3-CCD

The first idea to capture colors was to use a physical device split the light into its components.
To do so, the first method was the usage of a [dichroic prism](http://en.wikipedia.org/wiki/Image:Dichroic-prism.png) to split light in 2 parts. In order to obtain all the different components of the spectrum from this a set of glass pieces were taken, and one of their faces was colored in a specific color which reflected one specific color of the spectrum while making the other pass.

![[Pasted image 20260331141547.png]]
> [!INFO] 3-CCD Layout
> The diagram shows a possible layout:
> - A light beam enters the first prism (A), and the blue component of the beam is reflected from a low-pass filter coating (F1) that reflects blue light (high-frequency), but transmits longer wavelengths (lower frequencies).
> - The blue beam undergoes total internal reflection from the front of prism A and exits it through a side face.
> - The remainder of the beam enters the second prism (B) and is split by a second filter coating (F2) that reflects red light but transmits shorter wavelengths.
> - The small air space between the two prisms allows total internal reflection

This technique was used in old professional cameras, called 3-CCD cameras
![[Pasted image 20260331142316.png]]

![[Pasted image 20260331142405.png]]

## Bayer Pattern

The **Bayer Pattern** is a kind of filter created in 1976 at Kodak by Bryce Bayer, and is nowadays the standard used for every modern camera.
This filter is basically a single CCD array with a colored grid pattern on top acting as filter.
There are different combinations of Bayer patterns:
- CMY-Y
- CMY+G 
- RGB+E (Sony) more sensitive

![[Pasted image 20260331142802.png]]
> [!INFO] Green prevalence
> Notice how the green is the most diffused color in the pattern, as the human eye is more perceptive of the green channel. This pattern is called RGBG

This kind of filter decreases sensitivity to light, which becomes 1/3 of the monochrome.

The Bayer pattern has some advantages over 3-CCD technology:
- Only one sensor needed;
- No prisms are needed;
- Lower cost and size;
- Lower weight: portable devices;
On the other hand, the information of the Bayer pattern is sampled, so in each pixel it is necessary to reconstruct the missing components, as the images obtained in this way do suffer from aliasing.
![[Pasted image 20260331143316.png]]

In order to solve the aliasing problem we now need some way to apply the demosaicing process.

### Demosaicing

To apply demosaicing different techniques were created:
- Interpolation by convolution: Nearest neighbor, bilinear, cubic [Sak98], [Ram02], etc.
- AI-based algorithms

#### Nearest Neighbor Replication
In nearest neighbor replication (NRR) the missing components are interpolated with neighboring pixel values. The closest pixel can be in any of the four fundamental directions, above,
below, left or right.

![[Pasted image 20260331145430.png]]

This is the fastest idea, but it gives bad results, as it has quite a few problems:
- It creates many false colors that can create problems for image processing.
- High gradient transitions are very jagged (Zipper effect).
- The interpolated image tends to be noisy.

#### Bilinear interpolation
With bilinear interpolation, the missing components are interpolated with a bilinear interpolation of neighboring pixels. The components can be interpolated simultaneously

![[Pasted image 20260331145410.png]]
![[Pasted image 20260331145354.png]]

This algorithm is very efficient and often forms the basis for other better ones, but it has quite a few problems:
- The "pure" color of adjacent pixels can change abruptly.
- The whole image is subject to low pass filtering, causing a blur effect.
- Zipper effect reduced but not eliminated.

#### Linear interpolation with Laplacian 2nd order correction terms (LIL2)
The missing components are interpolated in an adaptive way, following the chromatic gradients.
This gives maximum performance in the case of images with vertical or horizontal edges.

The interpolation of green pixels has priority

This technique works based on the assumption that color planes are perfectly correlated in small areas of the image, so we approximate the following equations for the constants $j$ and $k$:
$$
\begin{align}
G &= B + k \\
G &= R + j
\end{align}
$$
After obtaining the linear interpolation we apply the Laplacian 2nd order correction.
In the case of green, it is calculated as follows
$$
\begin{align}
\Delta H = |G4 - G6| + |B5 - B3 + B5 - B7| \\
\Delta V = |G2 - G8| + |B5 - B1 + B5 - B9|
\end{align}
$$
![[Pasted image 20260331145217.png]]

Then the interpolation follows the following algorithm:
![[Pasted image 20260331145118.png]]

In the case of red, we have different possible cases:
- The two nearest pixels of the same color of the missing component are in the same column:
![[Pasted image 20260331150111.png]]
$$
R4 = \frac{R1 - R7}{2} + \frac{G4 - G1 + G4 - G7}{4}
$$
- The two nearest pixels of the same color of the missing components are in the same row:
![[Pasted image 20260331150136.png]]
$$
R2 = \frac{R1 + R3}{2} + \frac{G2 - G1 + G2 - G3}{4}
$$

After separating the cases, we define the compound gradients:
$$
\begin{align}
\Delta N &= |R1 - R9| + |G5 - G1 + G5 - G9| \\
\Delta P &= |R3 - R7| + |G5 - G3 + G5 - G7|
\end{align}
$$

So, the interpolation follows the following algorithm:
![[Pasted image 20260331150532.png]]

The interpolation of the blue is the same as the red
