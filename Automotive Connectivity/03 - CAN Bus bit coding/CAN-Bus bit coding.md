---
date:
  - 2026/09/29
  - 2026/10/01
---
In order to encode bits, [[CAN-Bus]] used 2 techniques:
- NRZ
- Manchester

![[Pasted image 20260929102914.png]]

Both methods need the use of a clock in order to know how to read the data.
In NRZ we wait a period before each reading, while in MC we read when we have a rising edge.

CAN-Bus is plagued by a problem of clock drifting, as with the engine heat and some other problems depending on real-world physics <!--damn physics--> and environmental changes the clock speed can drift from an ECU to another.
In order to avoid this, all receivers not only look at the bus but also try to re-adjust bit timing continuously.
Commonly, we use rising/falling signal edges in order to re-adjust bit timing.

When using NRZ, sending many identical bits leaves no signal edges that could be used to compensate for clock drift, so what we do is to insert extra stuffing bits after n consecutive identical bits (while the image below inserts stuffing after 3 identical bits, real world CAN-Bus uses 5 bits)

![[Pasted image 20260929105048.png]]

> [!WARNING] Problem with bit stuffing
> If we have a message like `0100011001100`, what happens is that the message gets incredibly big, as after reading the initial 3 `0`s we need to start stuffing, but the stuffing makes all the couples after it to become triplets, so we obtain a final message like `010001110001110001`

Even with this problem, we still prefer NRZ with bit stuffing over MC, since MC by its nature needs to operate on higher frequencies

A single bit time segment is actually composed of a set number of different time quanta (4 to 25), divided in 4 different segments:
- Synchronization segment
	- Used to synchronize the various bus nodes
	- Segment where the receivers expect the bus state change to occur
- Propagation time segment
	- Programmable length of 1 to 8 time quanta
	- Segment used to wait
- Buffer segment 1
	- Programmable length of 1 to 8 time quanta
	- Only segment that may grow in length during resync
	- At the end of this segment the bus state is sampled
- Buffer segment 2
	- Programmable length of 1 to 8 time quanta
	- Only segment that may shrink in length during resync

If a receiver notices that it is desynchronized of at least one time quanta it resyncs (if it is desynced by less than one it waits until it is desynced by at least 1)

