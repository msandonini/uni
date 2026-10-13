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

![[Pasted image 20261013095748.png]]

After each static and dynamic segment there are 2 more small segments:
- symbol window: is typically used for network maintenance and signaling for starting the network
- network idle time: a known quiet time used to maintain synchronization between node clocks

Also in this case we need to solve the contention on the bus. While CAN uses bitwise arbitration, FlexRay uses Time Division Multiple Access (TDMA), so all nodes sync with the same clock and each node waits its turn to write (this is the mechanism which implements time consistency, and so the one which make FlexRay deterministic).

While CAN nodes only needed to know the correct baud rate to communicate, nodes on a FlexRay network must know how all the pieces of the network are configured in order to communicate. This is because of the TDMA constraint.
This constraint means that the system works while in a closed configuration where no changes are made after the installation (so an embedded scenario).

For a TDMA network to work correctly, all nodes must be configured correctly, with a static network configuration. This makes the system really reliable, but removes flexibility and needs advanced planning ahead, in order to decide a-priori all of the configuration:
- data-rate
- deterministic data volume
- dynamic data volume
- topology

![[Pasted image 20261013100757.png]]

TDMA, while having many benefits, also has many limitations, as if an ECU goes down (not necessarily a fail) its reserved slot will simply not be used, so we are losing resources (time), as the other ECUs cannot use the free slots (each ECU configured in the system reduces the total bandwidth, and if it goes down the bandwidth is lost).

TDMA is also implemented in the dynamic slot, and it works by dividing the slot in many mini slots reserved for each ECU. If an ECU finds the bus free during a mini-slot reserved for him, it can transmit, and all the others must wait (even during their mini-slots).
If all ECUs are synced (and they are because of the network idle time slot), there is no way to collide.

