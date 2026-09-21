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

In order to enable 2 processes to interact with one another, from a programming perspective, knowledge of the architecture is needed, so it's not a transparent procedure.
To facilitate interactions between the processes and make the system transparent, middleware is needed.

Middleware acts as a middle layer between the OS and the application software.
To some extent, middleware can be considered as a sort of OS for distributed systems.
Basically, middleware solves the following problems:
- Transparency
- Scalability
- Heterogeneity
- App-level adaptivity
- Environment-level adaptivity

A widely used example of middleware is DNS, which translates human-comprehensible URLs to the destination IPs.

>[!Info] Adaptivity
>The capacity of intelligence of adapting to a situation

A distributed system can interact via different models:
- Client-server (master/slave)
- Message-passing (peer-to-peer)
- Event-based (pub/sub)

>[!Info] Intelligence
>The capability to act purposefully towards achievements of goals in an environment, where a goal is a specific desired situation in a specific environment (so we are not talking about AGIs, but situated finalized intelligence)

For intelligence, we can say that there are 3 things required:
- Perceiving
	- The capability for an entity of perceiving and understanding what happens around in the environment / context
	- This also typically includes the entity itself, so it is also about self-perception
- Reasoning
	- The capability of reasoning about what is perceived and previously deduced
- Acting
	- Having capabilities of acting an taking actions that can modify the current situation
All of these requirements are dependent on the central concept of adaptivity

These 3 requirements can be seen as a loop of perceiving, reasoning about what was perceived, acting accordingly to what reasoned modifying the surrounding environment (which in turn changes what is perceived in the subsequent iteration).
An entity working based on this loop is called an autonomous agent

How much intelligence is needed for a task is dependent on the goal and on the environment.
Sometimes even very trivial forms of perception and reasoning can be enough (e.g. a thermostat), while sometimes we require more complex activities of perception and reasonining (e.g. self-driving car or agentic AI code assistant)


