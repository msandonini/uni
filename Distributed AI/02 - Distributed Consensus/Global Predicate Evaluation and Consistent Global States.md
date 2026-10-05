---
date:
  - 2026/10/05
---
A key general problem in distributed and [[Distributed architectures & introduction to DAI|DAI]] systems is how to reach a common understanding of what is happening in the system and what is the overall state of the distributed computation.
Understanding if $v$ has a certain value or not is not an opinion, as either $v(t) = v_t$ or $v(t) \ne v_t$; thus, there is no need of reasoning or to applying some strategy to decide what is the value of $v$.

We define Global Predicate Evaluation (GPE) as a specific type of consensus problems where we need to know if a specific condition is currently taking place in the distributed computation.
Formally, given a predicate $P$ over the global state $\sum$ of the computation, we must determine if at a given time $t$ such statement is true ($P(\sum(t))=\text{true}?$).
This presents a new key problem: distributed systems are inherently asynchronous, as there is no global clock and there is no concept of simultaneity, so the global state observed by processes may not be consistent.

Assuming the existence of a process $P_0$ acting as observer who needs to evaluate a predicate, we can have 2 different approaches:
- Reactive architecture: each process, when executing an event, notifies $P_0$ by sending it a message describing the event
- Snapshot (or proactive) architecture: $P_0$ proactively sends each process a state inquiry message
In order to work with these 2 different architectures we must introduce some concepts:
- Distributed system: a collection of sequential processes $p_1, p_2, \dots, p_n$ networked by unidirectional communication channels (each with local clocks)
- Distributed computation: a computation executed by a distributed system
- Events: the activity of each sequential process, which can be internal events ($e$) or communications ($\text{send}(m)$ or $\text{receive}(m)$)
- Local history of process $p_i$: $h_i = e_i^{1}e_i^{2}\dots$, where $e_i^{x}$ is the $x_{\text{th}}$ event of process $i$
- Global history: $H = h_1 \cup h_2 \cup\dots h_n$
- Space diagram: representation of a distributed computation
- Happened before relation: a relation (not necessarily cause-effect) among events in a distributed computation
	- If $e_i^k, e_i^l \in h_i$, and $k < l$, then $e_i^k \to e_i^l$
	- If $e_i = \text{send}(m)$, and $e_j = \text{receive}(m)$, then $e_i \to e_j$
	- If $e \to e^\prime$ and $e^\prime \to e^{\prime\prime}$, then $e \to e^{\prime \prime}$
- Concurrent relation $e \parallel e^\prime$: neither $e \to e^\prime$ nor $e^\prime \to e$
- Local state $\sigma_i^k$: the state of $p_i$ immediately after executing event $e_i^k$ 
- Global state: $\sum = (\sigma_1, \dots, \sigma_n)$
- Run $R$: a total ordering of all events in $H$ consistent with each local history ($R = e_1^1 e_3^1 e_2^1 e_3^2 e_1^2 e_3^3 \dots$); a single distributed computation can have many possible runs
- Cut $C = (c_1, \dots, c_n)$: a subset of global history $H$ containing an initial prefix of each of the local histories (i.e. $C = h_1^{c_1} \cup \dots \cup h_n^{c_n}$) corresponding to freezing the observation of a global state $\sum$ for the sake of evaluating some global predicate

We can use a delivery rule to decide when received messages are to actually be presented to a process.
We can choose between different delivery rules:
- FIFO delivery rule
- Casual delivery rule

