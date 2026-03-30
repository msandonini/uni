---
course: Multimedia Data Processing
---
## CIELAB Color space
The CIEXYZ color space is considered the absolute reference for all color definition, but it has the flaw of describing the physical nature of the color and not its perception by the observer.
A series of color spaces were then defined in 1976, among which **CIELAB** has become the de-facto standard in industrial colorimetric practice.
The first coordinate of this space can be obtained from the following formulas:
$$
\begin{align}
L^{\star} &= 116 \left( \frac{Y}{Y_{n}} \right)^{\frac{1}{3}} - 16 \qquad& \left( \frac{Y}{Y_{n}} \right) > 0.008856 \\
L^{\star} &= 903.3 \left( \frac{Y}{Y_{n}} \right) \qquad& \left( \frac{Y}{Y_{n}} \right) \leq 0.008856
\end{align}
$$
This is called *CIE 1976 Lightness* and reproduces the perception of the brightness in the standard observer, referring to an illuminant whose characteristics are $(X_{n}, Y_{n} = 100, Z_{n})$
This scale is uniform with an excellent approximation and it is defined in the range $[0, 100]$.
The other 2 coordinates are $a^{\star}$ and $b^{\star}$, and are defined as:
$$
\begin{align}

a^{\star} &= 500 \left[ f\left( \frac{X}{X_{n}} \right) - f\left( \frac{Y}{Y_{n}} \right) \right] \\
b^{\star} &= 200\left[ f\left( \frac{Y}{Y_{n}} \right) - f\left( \frac{Z}{Z_{n}} \right) \right]
\end{align}
$$
Where:
$$
f(x) = \Big{ \{ } \space
\begin{align}
&x^{\frac{1}{3}} \qquad &x>0.008856 \\
&7.787 x + \frac{16}{116} \qquad &x \leq 0.008856
\end{align}
$$

## Color reproduction

To reproduce colors we have 3 methods:
- Additive synthesis
	- Colors get created by mixing lights in different chromaticity
	- Mix of all colors is white
- Subtractive synthesis
	- Colors gets created by overlapping light absorption of the different components differently
	- Mix of all colors is black
	- Primarily used in printers
- Spatial integration
	- Differently colored and close points that overlap in the human eye, thus producing a result similar to additive synthesis
	- Used, for example, in monitors and in screening inks printing

The television system is conceived starting from the cathode ray tube structure (CRT) which synthesizes the color through spatial integration of RGB phosphors arranged in mosaic on the screen.

The color space is therefore built on the basis of the chromaticity of the lights emitted by the three types of phosphors.

An RGB space is thus obtained in which only the colors enclosed in a cube can be displayed, the vertices of the cube represent the colorimetric coordinates of the phosphors

![[Pasted image 20260330112319.png]]
> [!INFO] Gamut
> The intersection of this space with the $R + G + B = 1$ plane produces a triangle that can be represented in the CIEXYZ space, and it is called ***"Gamut"*** of the monitor

The relationship between the luminance emitted by the CRT monitor and the value of the signal that drives the electron beam is not linear but exponential:
$$
\frac{L_{v}}{L_{v, max}} = \left( \frac{E}{E_{max}} \right)^{\gamma}
$$
Since the electronic circuit necessary for linearization was very expensive, the signal was corrected with the so-called gamma correction before being transmitted over the air. Thus, the gamma correction refers to the exponent and not to the colors.
Starting from the **NTSC** standard, the choice was $\gamma=2.2$

>[!INFO] Gamma correction values
>Realistic values for gamma would be between $2.35$ and $2.55$, but the television standards are designed for situations in which the screen is viewed in environments with soft light and therefore leave a margin to obtain an increase in contrast.

![[Pasted image 20260330113203.png]]

Gamma corrected values, being exponential instead of linear, cannot be used in arithmetic calculations, as the resulting value will be wrong (for example, if we take the average of the gamma corrected colors corresponding to 2 and 10, instead of the gamma corrected value corresponding to $6$ (which corresponds to $\sim 51$) we obtain a value of $\sim 81$):
$$
\begin{align}
&\alpha = a^{\gamma}, \quad \beta = b^{\gamma} \\
&\delta = \left(\frac{a + b}{2} \right)^{\gamma}, \quad\delta' = \frac{\alpha + \beta}{2} = \frac{a^{\gamma} + b^{\gamma}}{2} \neq \delta
\end{align}
$$

In a PC, we usually use the *truecolor* representation, which uses three 8-bit values for each pixel to control the 3 channels of the RGB color space.

If not otherwise specified, when working with digital images on the computer we are working with values acquired and corrected with a gamma factor.

## Transmissive color spaces

Even if we think based on the $RGB$ color space, to transmit colors we usually use different color spaces, because when it was created, the video signal had to be visible also on black and white televisions, so it was thought to separate the luminance component ($Y$) from the other, called chrominance.
In order to do this, a series of standards was born:
- $YIQ$ 
	- Used in NTSC regions
- $YUV$
	- Used in PAL regions
- $YCC$
	- Used in Kodak PhotoCD
- $YC_{B}C_{R}$
	- Used in digital video, JPEG, MPEG

While $YIQ$ and $YUV$ standards are important in the world of analog signals, the $YC_{B}C_{R}$ standard has assumed a dominant role in digital.
The conversion formulas in the case of $RGB$ values $[0, \dots, 255]$ are:

$$
\begin{bmatrix}
Y \\
C_{B} \\
C_{R}
\end{bmatrix}
=
\begin{bmatrix}
0.299 & 0.587 & 0.114 \\ -0.1687 & -0.3313 & 0.5 \\ 0.5 & -0.4187 & -0.0813
\end{bmatrix}
\begin{bmatrix}
R \\
G \\
B
\end{bmatrix}
+
\begin{bmatrix}
0 \\
128 \\
128
\end{bmatrix}
$$
As we can see in the formula, the channels are divided in $\sim 30 \%$ red, $\sim 60\%$ green, and $\sim 10\%$ blue, as it tries to mimic the human perception of color.

## Ordered space for Computer Graphics

In addition to the RGB standard, these spaces are used to introduce numerical color specification.
This type of transformation is useful for processing images for an interface with the human operator.
Each of these variants is based on the use of hue and saturation to represent the color.
![[Pasted image 20260330122051.png]]

### HSV (Hue, Saturation, Value)

- H is an angle between 0 and 360
- S is a value between 0 and 1
- V is a value between 0 and 1
This is a $0 \leq R, G, B \leq 1$ color space transformation, where for each point are defined:
$$
\begin{align}
\text{Max} = \max(R, G, B) \\
\text{Min} = \min(R, G, B)
\end{align}
$$
The coordinates are then given by the following formulas:
$$ 
\begin{aligned} 
V &= \text{Max} \\ 
S &= \frac{(\text{Max} - \text{Min})}{\text{Max}} \\ 
H &= \frac{\pi}{3} 
\begin{cases}
\frac{G - B}{(\text{Max} - \text{Min})} & \text{Max} = R \\
2 + \frac{B - R}{(\text{Max} - \text{Min})} & \text{Max} = G  \\
4 + \frac{R - G}{(\text{Max} - \text{Min})} & \text{Max} = B  \\
\end{cases} 
\end{aligned} $$
![[Pasted image 20260330122241.png]]

### HLS

The HLS color space was introduced by TRKTRONIX as its standard color, and it is a rework of the HSV system where the V (value) is replaced by L (Lightness):
$$
L = \frac{\text{Max} + \text{Min}}{2}
$$
Only the S (Saturation) definition changed:
$$
S = \begin{cases}
\frac{\text{Max - Min}}{\text{Max + Min}} &L\leq 0.5 \\
\frac{\text{Max - Min}}{2 - \text{Max + Min}} &L > 0.5
\end{cases}
$$

The pyramid structure of the HSV is doubled as shown on the right.
This, for example, is the system used in the standard dialog box for selecting Windows colors.
![[Pasted image 20260330123522.png]]

## Chromatic Quantization

Like spatial resolution, color resolution is also a compromise between cost and performance.
It is not always necessary to have all the colors of the truecolor images (24 bits per pixel, 8 for each channel).
It is therefore possible to save storage space and reduce the computational load by reducing the number of colors. This can be done with different techniques:
- Use fewer bits per band (e.g. 5-5-5 or 5-6-5 in the case of 15 and 16-bit hicolor respectively)
- Use a look-up table (color map): a finite number of colors (e.g. 256) stored on a table is chosen and the pixel value is a pointer to that table which contains RGB triad.
	- This was used in VGA
	- The list of available colors is called palette

"In ancient times" the CGA card had a 4-color palette, the 16-colors EGA and the "revolution" occurred with the VGA card that allowed a 256-colors palette

The choice of the palette plays a fundamental role in the quantization of colors.
It is possible to use a standard palette that contains a subset of the possible colors, chosen by dividing the RGB cube into a standard number of steps for each channel.
This operation can be done by choosing a step equal to:
$$
N = [\sqrt[3]{ \text{Elem} }]
$$
Where $\text{Elem}$ is the number of elements to insert in the final palette. It is easy to verify how in the case of 256 elements the number of steps should be 6, leading to a palette of 216 equally spaced elements, while the remaining can be chosen at will

Choosing a palette that best represents the color space of the image optimizes the colors reduction.

In 1980 Paul Heckbert proposed the Median Cut Algorithm, a technique for obtaining an optimized palette:
- the three-dimensional histogram of the colors contained in the image is calculated;
- the minimum parallelepiped oriented like the axes that contains all the colors must then be found;
- a cut on the longer direction of the box must be performed. The cut should be in the point that leaves (approximately) the same number of elements in the 2 halves (median cut).
- the cutting process is repeated for the box with most elements (or the largest as volume) until as many boxes as the required colors have been obtained. The representative colors will be given by the box’s colors average.
A further point to focus on is the technique to assign the palette to the image, since this implies a concept of similarity between colors. Usually graphics programs use the Euclidean distance in the RGB
space as a metric, even if this is not perceptually so meaningful.
