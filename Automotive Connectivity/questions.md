- Which are the fundamental blocks of a CAN Bus node?
    - MCU / MPU
    - CAN Controller (layer 2)
    - CAN Transceiver (layer 1)
- Without the Control block of a CAN message, which kind of problem would we have?
    - We would not know the size of the data block, so we wouldn't be able to know where data block ends and CRC starts, or when CRC ends and ACK starts, and so on.
- True/False
    - Only a group of ECUs can read the bus
        - False
    - All the ECUs can write on the bus
        - True
    - Every ECU can start the transmission as soon as it has data to send
        - False
	- If the bus is busy, every ECU should wait the EOF and then start to transmit
		- True
	- In steady state, the CAN bus is low (ground level, logical 0)
		- False
	- The dominant value on the bus is 0
		- True
	- The CAN Bus is a logical wired XOR
		- False (it's a logical AND)
- 3 nodes start to transmit together, who wins?
	1. ECU1 ID: `11001011101`
	2. ECU2 ID: `11001110110`
	3. ECU3 ID: `11001011001` <--
- Compute the CRC for the message `110010`. The generator $G(x)$ is $x^3 + 1$
$$
\begin{array}{rll}
110010 \phantom{0}| \underline{1001} \\
\underline{1001 \phantom{000} |}\phantom{0000} \\
10110 \phantom{0} | \phantom{0000} \\
\underline{1001 \phantom{00} |} \phantom{0000} \\
100 \phantom{|00000}
\end{array}
$$
- Check the correctness of the message `10101001111`. The generator $G(x)$ is $x^3 + x + 1$
$$
\begin{array}{rll}
10101001111 \phantom{0}| \underline{1011} \\
\underline{1011 \phantom{00000000} |}\phantom{0000} \\
11001111 \phantom{0} | \phantom{0000} \\
\underline{1011 \phantom{00000} |} \phantom{0000} \\
1111111 \phantom{0} | \phantom{0000} \\
\underline{1011 \phantom{0000}|}\phantom{0000} \\
100111\phantom{0}|\phantom{0000} \\
\underline{1011\phantom{000}|}\phantom{0000} \\
1011\phantom{0}|\phantom{0000} \\
\underline{1011\phantom{0}|}\phantom{0000} \\
0\phantom{|00000}
\end{array}
$$
	- The message is correct
- Destuff the following CAN Bus bit stream: `11111001010100000111110`
	- `11111010101000001111`
- If we have a transmitter slower than the receiver who re-synchronizes?
	- The receiver
- Which are the exceptions allowed for a transmitting node (only write 1 read 0 examples)?
	- Start of transmission in CAN-ID and RTR (RTR still has arbitration), and ACK and EOF
		- In the case of ID we defer the message
		- In the case of RTR is a message loss
		- In the case of ACK is an ACK
		- In the case of EOF is 
- Why is the amplitude not constant?
	- Different nodes may have small differences in current