A video is a sequence of images (frames), so an ordered set of frames in a sequence of instants of time $t_{k}$ with:
- $Dt = t_{k+1} - t_{k}$ constant for $k=0, \dots, n - 1$
- $V(x, y) = [f_{0}(x, y), f_{1}(x, y), \dots, f_{n-1}(x, y)]$
$Dt$ is not always constant, as frames can be skipped, adjusted, or added, however we suppose that $Dt$ is constant and a priori known.

Us humans, in order to process motion, use the dorsal posterior path in parietal cortex.
![[Pasted image 20260506122117.png]]
In order to understand motion with an artificial system, we must use a plethora of sensors. The most used ones are:
- Passive Infrared (PIR) sensors
	- Small, low power, easy to use, inexpensive.
	- Senses changes in temperature between the background and a warm body
	- IRs have a pyroelectric sensor that detects levels of infrared radiation
- Microwave sensors
	- Uses continuous waves of microwave radiation to detect motion, similarly to how a radar speed gun works
	- Sends out high radio frequency and measures the reflection off an object by sensing for a frequency shift and, if it does detect a shift, the motion detector is activated.
- Dual Tech/Hybrid technologies which use both the previous
- Radars
- Cameras

Localization in the space/time is tracking, and tracking an object means also to understand its motion, and understand if what is moving is points, objects, or the camera itself.

![[Pasted image 20260506123411.png]]
>As an example, in this image the camera is moving in the upper direction ([[Video Compression#Time difference|motion vectors]] are pointing down, so the objects are detected as if moving downwards).
>Not every object is detected as moving because there is a contrast threshold applied in order to detect bounds

Working on motion, the knowledge of the acquisition system is always mandatory, as we must know if the motion analysis is from:
- Fixed cameras
- Cameras with constrained motion (e.g. PTZ)
- Moving or unknown cameras
- Constrained but unknown egocentric motion

In computer vision, motion is used for many different tasks:
- Moving point estimation:
	- sparse and dense motion estimation, motion of undefined objects
	- point movement detection, shot detection
	- speed of background, foreground points and camera motion
	- SFM structure from motion (3D reconstruction by motion)
- Moving object detection:
	- estimating motion of background and foreground regions
	- detecting shapes in motion in 2D and 3D
	- understanding objects, people, actions by motion cue
- Detected object motion detection
	- spatial and temporal coherency analysis
	- tracking single and multiple targets
	- tracking objects with multiple point of views
	- reidentifying moving objects (re-id)

When working with notion we have 3 correlated but different terms:
- Motion
	- The actual motion concept
- Motion field
	- Projection of 3D motion in a plane
- Optical flow
	- What can be computed visually from images

