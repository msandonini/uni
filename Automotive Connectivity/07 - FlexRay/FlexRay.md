---
date:
  - 2026/10/13
---
Problems of CAN-Bus:
- "prone" to failures
	- line topology
	- no redundant links
- slow
- too much non-deterministic (no firm events schedule)
These problems make CAN-Bus not a good choice for Drive-by-Wire purposes, so we need a new protocol.

For this purpose, FlexRay needs certain features to be implemented:
- more resilient topology
- redundancy (boost error tolerance)
- different message class (to allow latency constraints)
- determinism (protocol design)


