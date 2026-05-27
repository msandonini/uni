---
course: Computer Vision and Cognitive Systems
---
![[Pasted image 20260525172906.png]]
Detection and tracking are like the chicken or the egg problem, as we have 2 approaches:
- Detection by tracking
	![[Pasted image 20260525173333.png]]
	![[Pasted image 20260525173411.png]]
- Tracking by detection
	![[Pasted image 20260525173117.png]]
	![[Pasted image 20260525173358.png]]

%% All'esame verranno chiesti solo Kalman & DeepSORT %%

%% 2026/05/27 %%

## Normalized Cross Correlation (NCC)

NCC is a single object tracker without motion analysis and prediction
![[Pasted image 20260527122903.png]]
NCC is based on template matching, which is a brute force method for tracking single objects, allowing a posterior motion estimation.
The similarity measure can be a direct template comparison or statistical measures between two probability densities.
Template matching is inefficient due to the brute force search, as it limits the object search to the neighborhood of its previous position, however if the template is not rigid or changes it shows drift.

