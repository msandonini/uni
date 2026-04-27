---
course: Computer Vision and Cognitive Systems
---

The SIFT algorithm is used in various applications:
- Object Recognition
	- It was used for these tasks when CNN and VIT were a solution, so they used SIFT to extract keypoints and connect them with other images of the same object
	- This works well if the object is exactly the same, so it's good in instance detection (and not really object detection)
	- Keypoints were used also for object classification, but the did not work as good as with instance recognition tasks.
- Image retrieval
	- It was used for image recognition in an image database, to take other images of the same object by matching the keypoint of the image with the keypoints of each other image
- Robot location
	- It's still very used since keypoint extraction is very fast and good to recognize distances.
	- It's less strong in the semantics but very fast
	- Still good if it recognizes just a subset of the objects
- Pick and place
	- Keypoints make it possible to obtain the exact location of an object which needs to be taken by a robot
	- With CNNs and VITs there isn't so much precision in object localization
- Structure from motion
	- We can reconstruct a 3D image of an object by extracting the keypoints of that object by a video, and then we can match the keypoints in the different frames and then reconstruct the 3D object
	- One of the state of the art ways to perform 3D reconstruction
- Augmented reality
	- It's useful to locate where to put virtual objects in a real-world image
There are many other applications of SIFT, as it is the most used keypoints extraction algorithm, but there are also different and newer algorithms which can perform even better.

Keypoint extraction tasks were tried also with CNNs, but it did not work, however what worked was [mixing CNN based descriptor with handcrafted descriptors](http://refbase.cvc.uab.es/files/BRP2019.pdf).
The combination of the 2 has both the location (given by SIFT) and the semantics (given by the CNN).

There are also semantic keypoints, which are keypoints with a semantic information.
They are used for different tasks:
- Pose estimation keypoints
- Facial landmarks
- Vehicle keypoints
These keypoints are not so precise in term of localization, because they are extracted by a CNN or a VIT.
