<!-- 2026/09/22 -->

<!-- Professor had a strange weekend (he didn't get drunk) -->

Bus system:
- Before 80s
	- Cars' control units are isolated, non-networked; to exchange data dedicated wires connected sensors and actuators
- Starting with the 90s
	- Digital bus systems, the one which is still used is CAN-Bus
- Today
	- Rising demands on bus systems (as CAN-Bus is not sufficient anymore because of the bandwidth constraints)
	- Networked functionality requires more than one control unit
	- Real time constraints
	- Multimedia

Traditionally, a dedicated ECU was added for each task, but nowadays the trend is to update the already present ECU in order to make them able to work on more tasks simultaneously.

There are 2 different types of architectures:
- Domain architecture
	- Central domain controller (high performance computer)
	- Ability to handle more complex functions
- Zonal architecture
	- Local ethernet gateway per-zone

Today, we have very different radio technologies working with the microprocessors via to the automotive ethernet (STP):
- TV/Radio
- WiFi ax/ad
- LTE/5G (sub-6 GHz 4x4 MIMO)
- V2X (5G NR/DSRC)
- GNSS (L1/L2 or L1/L5)
The big problem of having so many antennas on a single vehicle is EMI (Electromagnetic Interference), so each protocol and antenna power must be fine tuned in order to remain into different limits.
This is also why we have limited bandwidth constraints.

As of today, a car is composed of:
- Up to 100 ECUs
- Up to 3 km of wiring for power and data
- From 10 kg to 150 kg of cables (for both power and data)
- Up to 3800 interface points (each interface is a point of failure)


