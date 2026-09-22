## ISO/OSI Layers

Layers are a set of rules and guideline on how to manage and implement the communication.

I layer sono come gli orchi, e gli orchi sono come le cipolle

1. Physical layer
	- Specifies mechanical, electrical properties to transmit bits
	- Time sync, coding, modulation
2. Data Link layer
	- Checked transmission of frames
	- Frame sync, error checking, flow control
3. Network layer
	- Transmission of packets
	- Connection setup, routing, resourc management
4. Transport layer
	- Reliable end to end transport of segments
5. Session layer
6. Presentation layer
7. Application layer

In the course we will focus just on Physical and Data Link layers

The automotive ISO/OSI stack is simply composed of the Application layer and a Communication layer (composed of Data Link and Physical layers), where the Communication layer uses 2 physical blocks:
- Communication controller
	- Layer 1/2
- Transceiver block
	- Only layer 1

In reality, also layer 4 is used, but usually only for debugging (the OBD is considered layer 4)

## CAN-Bus

CAN-Bus, being a very low-level (nearly physical) protocol, is a broadcast-based protocol, so we need ways to filter out the messages we don't care about, and we need a congestion control mechanism.
Each CAN-Bus functionality is divided between layer 1 and 2:
1. Physical, where we find physical characteristics and functionalities
	- Physical Signaling (PLS)
		- Bit encoding/decoding
		- Bit time sync
	- Physical Medium attachment (PMA)
		- Driver/Receiver characteristics
	- Media Dependant Interface (MDI)
		- Connectors
			- Can be either electrical or optical
2. Data Link, where we find logical characteristics and functionalities
	- Logical Link Control (LLC)
		- Acceptance filtering
		- Overload notification
		- Recovery management
	- Medium Access Control (MAC)
		- Data encapsulation/decapsulation
		- Frame coding
		- Error detection/signaling/handling

There are various motives on why bus systems (and CAN-Bus between them) became popular:
- Lower cost
	- Material
	- Weight
	- Volume
- Higher modularity
	- Customizability of vehicles
	- Cooperation with Original Equipment Manufacturers (OEMs)
- Shorter development cycles


