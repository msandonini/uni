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
&= \mathbb{E}_{\pi}[R_{t+1} + \gamma R_{t+2} + \gamma^{2}R_{t+3}+\dots|S_{t} = s] \\
&= \mathbb{E}_{\pi}[R_{t+1} + \gamma(R_{t+2} + \gamma R_{t+3} + \dots)|S_{t} = s] \\
&= \mathbb{E}_{\pi}[R_{t+1} + \gamma G_{t+1}|S_{t} = s] \\
&= \mathbb{E}_{\pi}[R_{t+1} + \gamma v_{\pi}(S_{t + 1})|S_{t} = s] 
\end{align}
$$
The state-value function can again be decomposed into immediate reward plus discounted value of successor state:
$$
v_{\pi}(s) = \mathbb{E}_{\pi}[R_{t+1} + \gamma v_{\pi}(S_{t+1})|S_{t} = s]
$$

The action-value function can similarly be decomposed:
$$
q_{\pi}(s, a) = \mathbb{E}_{\pi} [ R_{t+1} + \gamma q_{\pi}(S_{t+1}, A_{t+1}) | S_{t} = s, A_{t} = a]
$$

%% Prof. Calderara will not ask the model slides (slide 19) %%

## Model-free prediction

The model-free prediction estimates the value function given a policy in a non-observable environment. To do so, different techniques can be used:
- [[#Monte-Carlo reinforcement learning|Monte-Carlo]]
- [[#Temporal-Difference reinforcement learning|Temporal-Difference]]

### Monte-Carlo reinforcement learning

MC methods can learn directly from episodes of experience, which can apply only to *episodic* environments (all episodes must terminate), and uses the simplest possible idea (value = mean return)

Policy evaluation:
- To evaluate state $s$
- Every time-step $t$ the state $s$ is visited in an episode.
- Increment counter $N(s) \leftarrow N(s) + 1$
- Increment total return $S(s) \leftarrow S(s) + G_{t}$
- Value is estimated by mean return $V(s) = \frac{S(s)}{N(s)}$
- By law of large numbers $V(s) \rightarrow v_{\pi}(s)$ as $N(s) \to \infty$

Incremental Monte-Carlo updates:
- Update $V(s)$ incrementally after episode $S_{1}, A_{1}, R_{2}, \dots, S_{T}$
- Compute return $G_t$
- For each state $S_t$ with return $G_t$:
$$
\begin{align}
&N(S_{t}) \leftarrow N(S_{t}) + 1 \\
&V(S_{t}) \leftarrow V(S_{t}) + \frac{1}{N(S_{t})}(G_{t} - V(S_{t}))
\end{align}
$$
- Usually a running mean is employed, i.e. forget old episodes:
$$
V(S_{t}) \leftarrow V(S_{t}) + \alpha(G_{t} - V(S_{t}))
$$

Monte-Carlo has a problem: it is very slow.
### Temporal-Difference reinforcement learning

In TD our objective is to learn $v_{\pi}$ online from experience under policy $\pi$.
While in Monte-Carlo our formula is like this:
$$
V(S_{t}) \leftarrow V(S_{t}) + \alpha(G_{t} - V(S_{t}))
$$
the simplest temporal-difference learning algorithm ($TD(0)$) update value $V(S_{t})$ is calculated toward estimated return $R_{t+1} + \gamma V(S_{t+1})$:
$$
V(S_{t}) \leftarrow V(S_{t}) + \alpha(R_{t+1} + \gamma V(S_{t+1}) - V(S_{t}))
$$
where:
- $R_{t + 1} + \gamma V(S_{t+1})$ is called the TD target
- $\delta_{t} = R_{t+1} + \gamma V(S_{t+1}) - V(S_{t})$ is called the TD error

This works since by removing $G_{t}$, TD can learn *before* knowing the final outcome, so:
- TD can learn online after every step
- MC must wait until the end of episode before return is known
- TD can learn without the final outcome
- MC can only learn from complete sequences
- TD works in continuing (non-terminating) environments
- MC only works for episodic (terminating) environments

Bias/Variance trade-off:
- Return $G_t = R_{t+1} + R_{t+2} + \dots + \gamma^{T-1} R_{T}$ is unbiased estimate of $v_{\pi}(S_{t})$
- True TD target $R_{t+1} + v_{\pi}(S_{t+1})$ is unbiased estimate of $v_{\pi}(S_{t})$
- TD target $R_{t+1} + v(S_{t+1})$ is biased estimate of $v_{\pi}(S_{t})$
- TD target is much lower variance than the return:
	- Return depends on many random actions, transitions, rewards
	- TD target depends on one random action, transition, reward

## Model-free control

- Model-free prediction
	- estimate the value function given a policy in a non-observable environment
		- Monte-Carlo Learning
		- Temporal-Difference Learning
- Model-free control
	- find a good policy in a non-observable environment
		- On-Policy Monte-Carlo Control
		- On-Policy Temporal-Difference Learning
		- Off-Policy Learning

How to improve a policy?

- Given a policy $\pi$
- Evaluate the policy $\pi$:
$$
\begin{align}
v_{\pi}(s) &= \mathbb{E}(R_{t+1} + \gamma R_{t+2} + \dots | S_{t} = s) \\
q_{\pi}(s, a) &= \mathbb{E}(R_{t+1})
\end{align}
$$
