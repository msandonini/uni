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
- Snapshot (or proactive) architecture: $P_0$ proactively sends each process a state enquiry message
