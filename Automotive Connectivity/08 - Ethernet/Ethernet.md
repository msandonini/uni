---
date:
  - 2026/10/15
---
<!-- We skip MOST -->

Created in 1973, CSMA/CD Ethernet had a speed of 3 Mbit/s, with a max of 256 nodes and 1 km coax cable.
In 1980 it was modified to become IEEE standard 802.3

Ethernet's goal, from the very beginning, has been to standardize the concept of Local Area Network and its key points:
- Independency
	- No master/slave approach
- Unlicensed / open domain
	- No space limitation, no rules
- Single channel
	- Shared single channel for all devices
- High bit-rate
	- No TDMA, get the access and use it at full speed

Ethernet has multiple physical standards:
- Coaxial cable (3 Mbps)
- Twisted pair (100 Mbps)
- Fiber optic (400 Gbps)

The key concept of Ethernet success is its CSMA/CD mechanism:
- CS (Carrier Sensing)
	- If the bus is busy, do not transmit
- MA (Multiple Access)
	- Once the communication starts, collisions may happen
- CD (Collision Detection)
	- Listen while speaking, if a collision is detected send a jamming sequence

When detecting a collision, Ethernet's CSMA/CD mechanism tosses a coin and waits before retrying


