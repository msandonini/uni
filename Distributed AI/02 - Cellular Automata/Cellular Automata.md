---
date: 2026/09/28
aliases:
  - CA
---
Cellular Automatas are the simplest complex dynamical systems, as they are easy to define and understand while still exhibiting very complex behaviour.
They are very useful to understand complex systems, grasp the power of interaction, visualize complex behaviour, and simulate complex spatial systems.

Automata = "Auto" (ancient greek for "self") + "Mata" (indian derived word for "Conscious awareness").
This definition evolved to the meaning of a robot able to perform complex tasks.

Being a kind of complex dynamical system, we can approach CA as a minimal distributed system:
- Cellular because made as a regular grid of cells
- Automata because cells are simple reactive agents with a local state and perceiving the state of surrounding cells, executing a continuous loop program to update the state *S* via a state transition function *f*.
```python
def cell():
	while True:
		S = f(S, neighbors)
```

$$
\text{CA} = (\text{S}, \text{d}, \text{N}, \text{f})
$$
- $\text{d}$ = dimensional organization of the lattice
- $\text{S}$ = local state of cells
- $\text{f}$ = state transition function
- $\text{N}$ = neighborhood

CAs present 2 dynamic characteristics:
- Dynamic evolution (cells change state based on their current state and the states of neighbors)
	- $S_i (t+1) = f (S_i (t), S_{n1} (t), \dots, S_{nj}(t))$
- Dynamic state transitions (which can be either synchronous or asynchronous)

CAs are defined as complex systems as with time, through the interaction dynamics, they can exhibit a very complex behaviour, even though they use very simple components and structure (an example is Conway's game of life, which with very simple structures and rules is able of demonstrating a very complex behaviour).
Example of Conway's GoL's simple rules:
- if 3 or more cells are alive in the neighborhood the cell becomes alive
- if less than 2 cells are alive in the neighborhood the cell becomes dead
- if 4 or more cells are alive in the neighborhood the cell becomes dead
Basically a cell remains alive only if it has 2 or 3 alive neighbors, otherwise it dies

CA behaviours are divided in different classes:
1. Stability: cells interact very little with each other, a cell does not feel the influence and stabilize to a steady state
2. Periodicity: cells interact with each other, but mostly locally, so th local changes in a cell depends on the state of only a few of other cells
3. Chaos: cells interact very strongly with each other, and the effects propagate at a global scale, making the local state of a cell dependent on the past states of all other cells
4. Self-organized behaviours: cells interact strongly with each other, but some effects transmit faster and some other much slower, so that slower effects lend to the formation of regular patterns that get continuously perturbed by global effects

The class to which a CA belongs is determined by a limited set of parameters. The most relevant one is typically the Lyapunov exponent ($\lambda$), which measures the tightness of interactions among components (the amount of feedbacks in th system and the amount of global scale effects in interactions):
- $\lambda \to 0$
	- All cells die
	- Not enough feedback to keep the system alive
	- Class 1 (e.g. rule 32)
- $0 < \lambda < 0.3$
	- Periodic patterns
	- Enough feedback to keep the system alive but still limited enough to avoid complex interactions
	- Class 2 (e.g. rule 90)
- $\lambda \to 0.3$
	- Stable non-periodic structures
	- The interaction feedback is strong, but it still preserves the possibility for regular self-organized structures to exist
	- Class 4 (e.g. rule 110)
- $\lambda > 0.3$
	- Random chaotic behaviour
	- Too much feedback noise to sustain any regular behaviour
	- Class 3 (e.g. rule 30)

In real life systems we have asynchronicity, since there is not a global clock but a lot of local different clocks.
When we are in an async context, the dynamics are dramatically different from those of synchronous CAs, as it's easier to reach self-organization patterns.
If we perturb state transition in async CAs, we can see that global scale self-organized behaviours emerge
![[Pasted image 20260928153601.png]]

CAs are useful to study and simulate complex systems, like complex distributed and DAI systems or complex natural behaviour.
Also, they can be useful to simulate spatial phenomenas (e.g. the growth of snowflakes and the wave diffusion)
