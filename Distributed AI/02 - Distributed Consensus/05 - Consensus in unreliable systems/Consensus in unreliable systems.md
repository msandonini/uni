---
date:
  - 2026/10/19
---
Lesson by prof. Mariani

In distributed computing we have 3 classes of problems:
- Link failure: a link fails and remains inactive, so the network may get disconnected
- Processor crash: at some point a processor stops taking steps
- Byzantine processor: a processor starts behaving in a casual way (so the messages have arbitrary content)

Link failure and processor crash are not so easy to distinguish, as in both cases there is at least an unresponding node, while with the byzantine processor problem the node responds but in an unreliable way.

In the consensus problem, processes have to agree on the value of a variable.
Each process can propose a value using a request of type `Request: <Propose, v>`, where `v` can be a variable, an input, or the value of an expression.
Eventually, processes receive an indication of what the decided value `v'` is, in the form of `Indication: <Decide, v'>`.

In order to work correctly, a consensus algorithm must follow some rules:
1. Validity
	- Any decided value is a proposed value
	- If everybody starts with the same value, then all non faulty processes must decide that value
2. Agreement
	- No two correct processes decide differently
	- If a process decides a value different from any other node, it's probably faulty
3. Termination
	- Every correct process eventually decides
4. Integrity
	- No process decides twice

Slide 21: explanation of the byzantine problem. There are 2 generals of the byzantine army who are encamped a short distance apart, and their objective is to capture a hill, but they can succeed only if they attack simultaneously. The 2 generals can only communicate by sending messengers, which is not reliable.
Basically there is no way for the 2 to be 100% sure that the other agreed to the plan, as there is no way for the message sender to know that the messenger arrived to the other except by sending agreement messages (but, in turn, they cannot be sure that the agreement arrived correctly).

It's impossible to reach consensus in case of failures, even if one only wants to tolerate a single failure of any nature.
The leader election and aggregation algorithms so far all follow the properties cited before, as we assumed the system was reliable.
This impossibility results apply to asynchronous systems (local clocks, no synchronization on message exchanges), but considering synchronous systems (shared clocks, each process can synchronize its computations with other processes), we can conceive some ways of tolerating faults (only for crashes or byzantine failures, as link failures are impossible to tolerate in any case).

>[!INFO] Simple consensus algorithm
>Example in slides from 26 to 30
>
>Each processor:
>1. Broadcasts its input to all processors
>2. Decide on the minimum
>
>(only one round is needed)
>
>If everybody starts with the same initial value, everybody decides on that value
>
>Problem: this algorithm does not work with crash or link failures (examples in slides from 32 to 35)

We can't do anything to solve link failures, but we can solve the problems of crashes and byzantine failures by organizing multiple rounds of value exchanges.
This is called $f$-resilient consensus algorithm, and it can tolerate the failure of at most $f$ processors, requiring $f+1$ rounds of information exchange.

>[!INFO] $f$-resilient consensus algorithm
>Example in slides from 39 to 48
>
>Round 1: broadcast my value
>Round 2 to $f+1$: broadcast any new received values
>End of round $f+1$: decide on the minimum value received

Similar $f$-resilient algorithms with $f+1$ rounds can be conceived for byzantine failures (only in the case of synchronous systems).
However, there is no $f$-resilient algorithm for $n$ processes where $f \geq n/3$.


