---
date:
  - 2026/09/29
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


