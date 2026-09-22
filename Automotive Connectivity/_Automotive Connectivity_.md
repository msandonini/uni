Corrected schedule:
- Tuesday: 09:00 - 11:00
- Thursday: 16:00 - 18:00

www.netlab.unimore.it

Written test on everything:
- Examples / exercises based on lessons ones
- 11 questions, 3 points each, 2h of time
Non-mandatory oral test about everything
Non-mandatory lab project about a chosen argument
Exam is held in english

2026/12/17 there is an informal exam session (during the lesson time)

Oral test cannot decrease the evaluation

Laboratory is hands-on on 802.11p (similar to WiFi but for automotive scenarios) using professors' Arduino-Yun

Course is divided in 3 modules:
- Inside the car (more about hardware)
	- Intra-vehicular communications (nodes, sensors, ECU)
	- Signal busses (CAN, CAN FD, LIN, FlexRay, A2B, Ethernet T1/T1S)
	- Car domains and OS
- Outside the car (more about data)
	- Inter-vehicular communications (V2V, V2X), where the car is a node
	- Wireless technologies: Bluetooth, LoRa, C-V2X, IEEE 802.11p (or 11bd)
	- Extra (apps, messages, broadcast, GPS)
- Hands on hardware
	- Practical inter-vehicular communications
	- IEEE 802.11p (or 11bd)
	- Arduino-Yun
	- Multi-hop communications, broadcast messages, security

Differences between 802.11n:

| 802.11n                               | 802.11p OCB                        |
| ------------------------------------- | ---------------------------------- |
| Indoor                                | Outdoor                            |
| SSID                                  | No SSID                            |
| 2.4 / 5 GHz                           | 5.9 GHz specific reserved channels |
| Up to 20 MHz channel                  | 10 MHz channel                     |
| Up to 300 Mbps (higher with ac or ax) | 3 - 27 MBps                        |
| Auth time                             | No auth                            |

Why Arduino-Yun:
- Pros: 
	- Cheap (50$ all-inclusive)
	- IoT oriented
- Cons:
	- only 2.4 GHz
	- coverage (integrated antenna)
