Saliency is the task of estimating where you will look at when you see an image.

How we see the things is very different from how we encode them, and knowing which are the most attractive spots in an image is useful to learn how we can encode and process it.
For example, a background can be compressed more since it's not as interesting as the foreground.
This is used in advertisements.

From saliency we can obtain a map which tells us where the human eye will focus.
![[Pasted image 20260427095400.png]]

Saliency detection in humans is a key attentional mechanism that facilitates learning and survival by enabling organisms to focus their limited perceptual and cognitive resources on the most pertinent subset of the available sensory data.

Since saliency is subjective 2 different people will see different things in the same image. In our case, saliency tries to extract an average of what people usually see.

One of the first saliency extraction mechanisms was created by Itti and Koch:
![[Pasted image 20260427095611.png]]
This saliency extraction mechanism is quite old, but the base idea still works decently.

No feature contains semantics, as we just have features based on color, intensity, and orientation.


Following the idea of multi-level features, we can use a VGG-16 in order to obtain both some perceptual-level features and some semantic-level features:
![[Pasted image 20260427100423.png]]
In this architecture we combine the attention levels and high level features, and then we apply the learned prior.
Usually we have the tendency to focus on the center of the image, however this architecture does not, since computers are translation invariant.
In order to add importance to the center of the image we can make the prior focus on it.
This is fully learned, and not pre-set.

![[Pasted image 20260427101103.png]]

It's possible to apply saliency also to videos. In this case we need to keep motion into account, as also the movement is something that catches the human attention.
