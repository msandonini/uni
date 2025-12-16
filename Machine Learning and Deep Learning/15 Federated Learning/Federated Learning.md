---
tags:
  - deep_learning
---
In Federated Learning the idea is the same as in Continual Learning, but spreading tasks not on the time axis but on the space axis.

This is born by the fact that until now, machine learning was done in a centralized way:
- All data is in one single point of the network
- Single model, combined dataset
- Iterative optimization (SGD)
	- The model's parameters are iteratively updated using Stochastic Gradient Descent, epoch after epoch until the model converges
Centralized ML is a problem because