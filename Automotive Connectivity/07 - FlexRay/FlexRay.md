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

For this purpose, FlexRay (which is both not flexible and not a ray) needs certain features to be implemented:
- more resilient topology
- redundancy (boost error tolerance)
- different message class (to allow latency constraints)
- determinism (protocol design)

In Flexray, the default operational value is logical 1 (like CAN).
The cables are twisted pairs (and very heavy), where the differential signaling on each pair reduces the effects of external noise on the network without the need of expensive shielding (in fact, cables are unshielded).
Each bus needs a termination at its ends, and it needs synchronized clocks in sender and receiver

![[Pasted image 20261013094727.png]]

The bus operates on a time cycle (schedule), with a static segment and a dynamic segment.
The static segment is preallocated into slices, allowing for a more master-slave, deterministic approach, which allows addressing time constraints.
The dynamic segment is what happens in the schedule holes, and it operates more like CAN, where nodes take control of the bus as available, allowing event-triggered behavior.

