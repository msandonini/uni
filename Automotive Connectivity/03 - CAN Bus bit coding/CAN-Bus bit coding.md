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

CAN-Bus is plagued by a problem of clock drifting, as with the engine heat and some other problems depending on real-world physics <!--damn physics--> the clock speed can drift from an ECU to another

