![[Pasted image 20260924164937.png]]
Electrically, CAN-Bus works by two wires giving noise resistance and increase resiliency.
These 2 wires are CAN High and CAN Low, and are twisted (to avoid EMI to go outside); also, if one of the 2 breaks the other still can send data.
They have a $R_T$ impedance of $220\ohm$ at the ends


Each ECU attached to the bus must follow the CAN interface (consisting of a CAN controller and a CAN transceiver)
![[Pasted image 20260924165330.png]]

The CAN message contains very much overhead (a frame with 64 bits of data is composed of a total of 126 bits), so it's characterized by an efficiency of nearly 0.5 (against the high efficiency of other telecom protocols, like ethernet which has 0.98 efficiency)
![[Pasted image 20260924165404.png]]

All the overhead is caused by the amount of blocks
- SOF
	- 1 bit
	- A *dominant 0* to tell the other ECUs that a message is coming
- CAN-ID
	- 29 bits (there also exists a CAN version with 11 bits of CAN-ID)
	- Contains the message identifier (lower values have higher priority)
	- Used for the arbitration
- RTR
	- 1 bit
	- Deprecated
	- Allows the 
- Control
	- 6 bits
	- Informs the length of data in bytes (0 to 8)
- Data
	- 0-64 bits
	- The actual data
- CRC
	- 16 bits
	- Cyclic redundancy check used o ensure data integrity
- ACK
	- 2 bits
	- Indicates if the CRC process is ok
- EOF
	- 7 bits
	- Marks the end of the message

Each ECU reads the wire (through a buffer) and can write on the line (through a transistor)

Base state of CAN bus:
- Transistor in non-conductive state
- Base state is up (+5V, Bit logical value of 1)
When one or more ECUs have to write they turn transistor conductive (diode), which connects the bus to ground, meaning that the bus level goes to low (0V ground, bit logical value of 0) independently from each other ECU (in this configuration the 0 bit is called the **dominant** level)
