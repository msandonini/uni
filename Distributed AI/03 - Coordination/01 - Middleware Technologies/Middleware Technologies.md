---
date:
  - 2026/10/20
---
Modern distributed systems need to have a set of fixed properties:
- Transparency: they don't need to know network and distribution details (unlike with what happens with network details)
- Scalability: they need to be able to scale up to a large number of components
- Openness: components may be developed with heterogeneous technologies
- Adaptivity: new components and services need to be able to join the system, while others may leave, and each time this happens it's needed to not re-configure and re-design the whole system
- Context-awareness: some info about the actual environment must be dynamically retrieved at deployment time or at run-time

To do so we need to either integrate such capabilities within each component ([[intelligent autonomous agents]]), or integrate them in the operational environment of the distributed components (middleware).

Basically, a middleware job is to act as a shadowing layer between the distributed applications' processes so that each process can work without having to know the system on which it is installed.

An example of middleware are network file systems, which enable applications and processes to transparently access remote files as if they were local.

There are different middleware models:
- Client-server
	- Supports distributed object applications and service-oriented systems
- Event-based
	- Rooted on interactive computing models
	- Supports reactive context-aware models
- Shared dataspaces
	- Rooted on shared memory models
	- Supports sorts of stigmeric interactions between components

Shared dataspaces and event-based models can be collapsed into a single model.
Most middleware technologies handle objects, shared memories, and events.
These models, more than interaction models, are best known as coordination models, since they provide communication, synchronization of activity, and orchestration between components.
