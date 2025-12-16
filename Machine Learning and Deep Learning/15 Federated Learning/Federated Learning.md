---
tags:
  - deep_learning
---
In Federated Learning the idea is the same as in Continual Learning, but spreading tasks not on the time axis but on the space axis.

This is born by the fact that until now, machine learning was done in a centralized way:
- All data is in one single point of the network
	- Training data from all sources is aggregated and stored on a central server or in a data center
	- The model has access to the entire dataset during training
- Single model, combined dataset
	- A single global model is trained on this unified dataset
	- This traditional approach relies on processing all data centrally before model training
- Iterative optimization (SGD)
	- The model's parameters are iteratively updated using Stochastic Gradient Descent, epoch after epoch until the model converges
Centralized ML is characterized by different problems:
- Single point of failure
- Hardware limits
- High bandwidth usages for big datasets
- Privacy problems while downloading the data from the server
These problems can be circumvented by, instead of sending data to a centralized model, sending the pre-trained model to where the data is stored

The overall idea of federated learning is to have a paradigm where the data and the model are spread between different devices in different geographical positions.
This paradigm works on the fact that a server coordinates a set of clients to collaboratively train a model without sharing their raw data.
This enables training on decentralized data for improved privacy and efficiency, sharing the updated model instead of the data.

0. The server has an initialized network (global model) but no data, which is distributed among clients
1. Server sends the global model to selected clients
2. Clients perform local training on their private data (one or more epochs)
3. Clients send local model updates (e.g. gradients )