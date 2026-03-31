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
