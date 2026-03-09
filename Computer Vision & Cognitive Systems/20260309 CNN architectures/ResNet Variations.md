---
tags:
  - computer_vision
---
## Wide Residual Networks

![[Pasted image 20260309103533.png]]

Variation of ResNet which increases the number of channels, passing from a basic residual block to a wide residual block, and it results in a less deep network (50-layer wide Res-Net outperforms 152-layers original ResNet).

Switching from a basic residual network to a wide residual network also increases computation efficiency.
## ResNeXt

![[Pasted image 20260309103615.png]]

Also from the creators of ResNet, it's a sort of fusion between ResNet and GoogLeNet, as it uses different parallel layers.

## Deep Networks with Stochastic Depth

![[Pasted image 20260309103655.png]]

During training, randomly, some layers get deactivated, in order to reduce vanishing gradients, training times, and make the network more robust.

## Squeeze-and-Excitation Networks (SENet)

![[Pasted image 20260309103811.png]]
![[Pasted image 20260309103845.png]]

The idea is to take the output of a convolution and reweight the channels by adding a feature recalibration module that learns to adaptively reweight feature maps.

## Densely Connected Convolutional Networks

![[Pasted image 20260309103746.png]]

These networks are composed of dense blocks where each layer is connected to every other layer in feedforward fashion.
This alleviates vanishing gradients, strengthens feature propagation, and encourages feature reuse.

## Neural Architecture Search (NAS)

![[Pasted image 20260309104042.png]]

A network (usually a reinforced learning network) trained to invent new network architectures

