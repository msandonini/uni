---
tags:
  - deep_learning
---
Reinforcement learning is a branch of machine learning which differs from [[supervised learning]] and [[unsupervised learning]] which differs from the previous 2 by the fact that data has no labels, but still has something to be based on.

Reinforcement learning models have the following characteristics:
- No supervisor, only a *reward* signal
- Feedback is delayed, not instantaneous
- Time really matters (sequential and non i.i.d data)
- Agent is *active*, as its actions affect the environment he lives in

A reward $R_t$ is a scalar feedback signal, which indicates how well the agent is doing at step $t$, and the agent job is to maximise the cumulative reward.

The objective is to select actions to maximise total future reward, and since actions may have long term consequences the reward may be delayed.

The history is a sequence of observations ($O_{i}$), actions ($A_{i}$), and rewards:
$$
H_{t} = O_{1}, R_{1}, A_{1}, \dots, A_{t -1}, O_{t}, R_{t}
$$
The state is the information used to determine what happens next based on the history:
$$
S_{t} = f(H_{t})
$$

We can find differences between agent states ($S_{t}^{a}$) and environment state ($S_{t}^{e}$):
- Agent state
	- Whatever information the agent uses to pick the next action
	- Information used by RL algorithms
- Environment state:
	- Whatever information the environment uses to pick the next observation/reward
	- Usually not visible by the agent

We can create a distinction in the agent observability of the environment:
- Full observability
- Partial observability

A *policy* is the agent's left behaviour, and is a map from state to action, and can be either deterministic or stochastic:
- Deterministic: $a = \pi(s)$
- Stochastic: $\pi(a|s) = \mathbb{P}[A_{t} = s | S_{t} = s]$

We define the *return* $G_t$ as the total discounted reward from time-step $t$:
$$
G_{t} = R_{t+1} + \gamma R_{t + 2} + \dots = \sum_{k=0}^{ \infty } \gamma^{k}R_{t + k + 1}
$$



The *value function* is the prediction of future reward which the agent uses to choose its action based on expected return.

The *state-value function* is the expected return starting from state $s$, and then following policy $\pi$
$$
v_{\pi}(s) = \mathbb{E}_{\pi} [ G_{t}|S_{t} = s ]
$$
The *action-value function* $q_{\pi}(s, a)$ is the expected return starting from state $s$, taking action $a$, and then following policy $\pi$
$$
q_{\pi}(s, a) = \mathbb{E}_{\pi} [ G_{t} | S_{t} = s, A_{t} = a ]
$$

Bellman expectation equation (loved by prof. Calderara):
Value function can be decomposed into two parts:
- Immediate reward $R_{t+1}$
- Discounted value of successor state $\gamma v(S_{t} + 1)$
$$
\begin{align}
v_{\pi}(S) &= \mathbb{E}_{\pi}[G_{t}|S_{t} = s] \\
&= \mathbb{E}
\end{align}
$$


The action-value function can similarly be decomposed
$$
q_{\pi}(s, a) = \mathbb{E}_{\pi} [ R_{t+1} ]
$$

%% Prof. Calderara will not ask the model slides (slide 19) %%


