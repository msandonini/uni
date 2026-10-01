---
date:
  - 2026/10/01
---
CAN-Bus can be subjected to different errors:
- bit errors
	- happens when a transmitting ECU detects an opposite bit level on the CAN Bus 
		- ECU writes 1 and reads 0 is reasonable
		- ECU writes 0 and reads 1 is very bad
- bit stuffing errors
	- happens when after 5 identical bits the ECU does not detect a state change
	- last 2 blocks after CRC don't have bit stuffing
	- error frame transmitted by each receiving node that received a message which breaks the bit stuffing
- format errors
	- happens when there is a form error in CRC, ACK or EOF fields
	- transmitted by receiving nodes
- CRC errors
	- happens when the reminder of message+CRC divided by the generator is $\neq0$
- ACK errors
	- happens when the transmitter does not receive a 0 while transmitting the ACK field
	- when it happens, the transmitter will send the message again

The receivers have to transmit during specific frame slots (the ACK field is one example, but not the only one). The EOF field also acts as a means to communicate errors:
- `ACK=0`, `EOF=1`: best case scenario (no error)
- `ACK=0`, `EOF=0`: at least one ok, at least on error
- `ACK=1`, `EOF=1`: complete silence, probably there is only one ECU connected to the bus
- `ACK=1`, `EOF=0`: no one says ok, there is at least an error
In the `ACK=0` `EOF=0` case the message is not re-transmitted automatically.
Assuming A was the tx, B and C triggered ACK, and D triggered EOF, but the message was for D, D can ask A to re-transmit, by transmitting a remote frame using A id and the same control block as before, with no data, and RTR set to `REGRESSIVE`

![[Pasted image 20261001180058.png]]


