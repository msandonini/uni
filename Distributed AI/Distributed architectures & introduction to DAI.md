 Some keywords:
>[!Info] Context
> What surrounds an entity and its existence, also known as the environment where an entity is situated. There can be different types of contexts:
> - Physical context: different rooms, different streets, ...
> - Logical context: different social communities, different stakeholders, different VMs, ...

>[!Info] Distributed
>Something composed of different entities located in different contexts

---

A distributed architecture is a set of connected computational hardware elements ("nodes") with no shared context (no shared memory / clock / space).
Examples of a distributed architecture can be:
- a computer network
- an IoT network
- a group of robots
- an ensemble of cars

Each node has different contexts:
- One processor (at least)
- Its own memory
- Its own clock

Distributed architectures can take different forms

>[!Info] Process
>A process is the instance of a software program in execution.
>When launching a program in execution, the OS
>- Creates a new process
>- Assigns to it a private working memory space
>- Schedules its execution on the CPU

Each process can spawn multiple concurrent execution flows (threads) related to its execution

A distributed system is a network of processes interacting with each other. The study of dist systems is usually transparent relative to the physical network of how processes interact (so the network structure is somewhat hidden and ignored).

Distributed AI is a form of distributed computing, as there is not a sharp distinction between DAI and distributed computing, it can be a matter of:
- Degree of goal oriented autonomy
- Degree of adaptability
- Flexibility
