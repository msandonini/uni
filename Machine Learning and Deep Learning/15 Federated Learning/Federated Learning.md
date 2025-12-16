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
- [[#Client-side approach]]
	- Each client has some additional terms, that constrain their objective or their weights to force consistency
- Prototype-based approach
	- Constraint are forced in feature space instead of weight space, in order to obtain a good trade-off between consistency among clients and specialization on local-datasets

## Server-side approach

Parameter averaging (e.g. FedAvg) treats every weight dimension as equally informative. This works when updates come from i.i.d. data but can be sub-optimal under heterogeneity.
To solve this problem we can weight the contribution of each model parameter by how confident the model is about that parameter, measured using the [[Fisher Information Matrix]]
$$
F_{\theta} = \frac{1}{N} \sum_{i=1}^{N} \nabla_{\theta} \log p(x^{(i)}|\theta) \nabla_{\theta} \log p(x^{(i)}|\theta)^{T}
$$
There is a theoretical relation between the empirical Fisher Information Matrix (FIM) and the second derivative of the loss near a minimum: in particular, the [[Fisher Information Matrix|FIM]] can be used as an approximation of the Hessian matrix near a minimum.

Since FIM captures the curvature of the function, a high Fisher information for parameter $i$ indicates that that parameter is pivotal, so if we modify it we are likely going to increase the value of the loss function.
On the contrary, if another parameter $j$ has low Fisher information it means that its value is not so important, and by mildly changing it the value of the loss should remain more or less the same.

The core formula of the Fisher-weighted average is obtained as follows:
- Given $M$ client models $\{\theta_{i}\}_{i=1}^{M}$ with identical initialization, approximate each model's posterior as a Gaussian-distributed posterior $p(\theta|\theta_{i}, F_{i})$, where $F_i$ is the Fisher Information Matrix.
- The objective is to find the set of weights $\theta^{\star}$ that maximizes the joint posterior, that is, the posterior of all clients' models:
$$
\theta^{\star} = \arg \max_{\theta} \prod_{i=1}^{M} \lambda_{i} p(\theta|\theta_{i}, F_{i})
$$
where $\lambda_{i}$, $\sum_{i} \lambda_{i} = 1$ is an ulterior set of scalars.

This optimization problem holds a closed-form solution, which is given by:
$$
\theta^{\star} = \left( \sum_{i} \lambda_{i} F_{i} \right)^{-1} \left( \sum_{i} \lambda_{i} F_{i} \theta_{i} \right)
$$
Problem: Both estimating and storing a full FIM can be non-feasible when the number of parameters of the neural network becomes fairly large, especially since all modern architectures are over-parameterized.
Solution: Using an approximation of the FIM, such as its diagonal, that can be represented as a vector, can become tractable. It also simplifies the closed-form solution, which becomes:
$$
\theta^{\star} = \frac{\sum_{i=1}^{M} \lambda_{i} F_{i} \theta_{i}}{\sum_{i=1}^{M} \lambda_{i} F_{i}}
$$

## Client-side approach

Under non-iid data, FedAvg's local updates can move in inconsistent directions, causing the global model to drift from the true optimum.

In this approach our goal is to make each client follow as closely as possible the ideal update direction (the one we would obtain if all data were available in one place).
- The ideal direction is easy to compute if:
	- All data are stored on a single client
	- Clients send both their model parameters and gradients to a central server
- The server could then aggregate all gradients, compute the global update, and send it back to the clients
- Clients would use this information to correct their local update direction, avoiding drift caused by non-IID data.
The challenge with this solution is that directly exchanging gradients is communication-expensive.
To solve this we can approximate this global correction efficiently.

### SCAFFOLD

SCAFFOLD introduces adjusted local gradients to correct for client drift.

<u>Adjusted local gradient</u>: when client $i$ trains on current model $w$, it uses
$$
g_{i}(w) = \nabla \mathcal{L}_{i}(w) + c - c_{i}
$$
which pulls the client's update direction closer to the global direction, reducing drift.
The variables $c$ and $c_i$ are defined as control variates.

![[SCAFFOLD_algorithm.png]]

## Prototype-based approach

The concept of prototypes is connected to the concept of classes.
The idea behind prototypes is to obtain the centroid of each class (an aggregation of every point in the class which can be obtained for example by calculating the point with the smaller total distance from all the samples of the same class).
These prototype can then be used to perform classification.
The idea of these approaches is to not send the data to the model on the server but to send the prototypes.

### FedProto

FedProto has each client $i$ compute protoypes $p_{i, c}$ for each class $c$.
Given client $i$'s feature extractor $f_{i}$, classifier $g_{i}$ and local dataset $D_{i}$, each client computes the prototype for a given class $c$ at the end of each round as:
$$
p_{i, c} = \mathbb{E}_{(x, y) \sim D_{i}} [f_{i(x)}: y = c]
$$
Clients send these prototypes to the server, and the server averages the received prototypes to form global prototypes for each class.

The server sends the global prototypes back to the clients. Each client $i$ then adds a regularization term to its loss to keep its local prototypes close to the global ones:
$$
\mathcal{L}_{i}^{\text{FedProto}} = \mathcal{L}_{i}^{(\text{local})} + \lambda \lvert \lvert p_{i, c} - \bar{p}_{c} \rvert  \rvert^{2}
$$
which penalizes the discrepancy between $p_{i,c}$ and the global prototype $\bar{p}_{c}$ for each class $c$.
This ensures that feature representations across clients remain aligned, addressing heterogeneous label distributions.
Inference can also be done using nearest-mean classifier:
$$
\hat{y} = \arg \min_{c} \lvert \lvert f(x) - \bar{p}_{c} \rvert \rvert_{2} 
$$

The usage of FedProto grants various advantages:
- Efficiency
	- Prototype vectors are much smaller than full model updates, so communication costs are reduced since we only share prototypes and not entire models
- Effectiveness
	- By regularizing toward global prototypes, FedProto outperforms FedAvg and similar methods on heterogeneous benchmarks, achieving higher accuracy in federated settings.
