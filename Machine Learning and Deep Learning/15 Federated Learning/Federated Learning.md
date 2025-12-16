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
- Iterative optimization ([[Stochastic Gradient Descent|SGD]])
	- The model's parameters are iteratively updated using [[Stochastic Gradient Descent]], epoch after epoch until the model converges
Centralized ML is characterized by different problems:
- Single point of failure
- Hardware limits
- High bandwidth usages for big datasets
- Privacy problems while downloading the data from the server
These problems can be circumvented by, instead of sending data to a centralized model, sending the pre-trained model to where the data is stored

The overall idea of federated learning is to have a paradigm where the data and the model are spread between different devices in different geographical positions.
This paradigm works on the fact that a server coordinates a set of clients to collaboratively train a model without sharing their raw data.
This enables training on decentralized data for improved privacy and efficiency, sharing the updated model instead of the data.

Federated learning is based on a set of steps:
0. The server has an initialized network (global model) but no data, which is distributed among clients
1. Server sends the global model to selected clients
2. Clients perform local training on their private data (one or more epochs)
3. Clients send local model updates (e.g. gradients or new weights) back to the server
4. Server aggregates updates (e.g. by averaging) to improve the global model
The steps 1-4 get repeated until convergence.

![[FL_idea.png]]

In FL we encounter different key challenges:
- Data heterogeneity (non-IID data)
	- Clients have diverse data distributions, causing *[[client drift]]* and potentially lower model accuracy
- Partial participation
	- Each round, only a fraction of clients is active
	- Across rounds the set of participants changes (stragglers, drop-outs)
- Communication overhead
	- Limited network capacity means minimizing the size
	- Frequency of model updates is critical for efficiency
- Privacy and security
	- Although raw data stays local, shared model updates may still leak information

## Federated Averaging (FedAvg)

FedAvg is the foundational algorithm for FL:
- Each round, a subset of clients receives the current global model, trains on its local data, and sends the updated model back.
- The server then averages these client updates to obtain a new global model. This iterative process continues for multiple rounds.

- Init:
	- Server sets initial global model parameters $w^{0}$
- For each round $t = 1, 2, \dots, T$:
	- Server selects a subset $C_t$ of available clients
	- Server sends the current model $w^{t-1}$ to all clients in $C_{t}$
	- Each client $i \in C_{t}$ initializes $w^{t-1}$ and performs local training to obtain an updated model $w_{i}^{t}$
	- Clients send its model's weight $w_{i}^{t}$ (or the model difference) back to the server
	- Server aggregates the weights to form the new global model:
$$
w^{t} \leftarrow \sum_{i \in C_{t}} \frac{n_{i}}{\sum_{j \in C_{t}} n_{j}} w_{i}^{t}
$$
The idea of sending the model can be viewed as an attempt to reach a sort of agreement in the knowledge of the model across all the network.

The main problem with FedAvg is that with non-iid client data, local models can diverge significantly ([[client drift]]), harming the global model's convergence and accuracy.

FedAvg limitations have led to various improvements, which can be categorized into 3 families:
- [[#Server-side approach]]
	- The server employs more powerful ways to aggregate the parameters
- Client-side approach
	- Each client has some additional terms, that constrain their objective or their weights to force consistency
- Prototype-based approach
	- Constraint are forced in feature space instead of weight space, in order to obtain a good trade-off between consistency among clients and specialization on local-datasets

## Server-side approach

Parameter averaging (e.g. FedAvg) treats every weight dimension as equally informative. This works when updates come from i.i.d. data but can be sub-optimal under heterogeneity.
To solve this problem we can weight the contribution of each model parameter by how confident the model is about that parameter, measured using the [[Fisher Information Matrix]]


