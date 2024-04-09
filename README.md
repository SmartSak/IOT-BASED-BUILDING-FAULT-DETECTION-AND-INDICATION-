# IOT BASED FAULT DETECTION
IOT BASED BUILDING FAULT DETECTION AND INDICATION SYSTEM
# ABSTRACT
  Fault in power systems is one of the greatest problems that cause power disruptions. It can occur from generation, distribution, and consumer systems. This project will focus mainly on the Building line fault Building wires are used more often in urban areas than overhead lines. It is difficult to locate a fault when it occurs, and the process may be time-consuming and costly. The proposed system will find the exact location of the fault and facilitate timely maintenance. The concept of a potential divider network connected across the Building line will be used. IoT will allow the authority to check faults over the internet while in their respective Transformers. Therefore, they can alert the technicians who are near the particular location for repair. A set of resistors represents the length of the cable in floors, and faults are created at predefined distances using switches. In case of a fault, there will be a change in current drops, which will be sent to the microcontroller. The ADC in the microcontroller interprets the data and conveys the information to the user in terms of distance in floors. This is then displayed over the LCD and shared online using the IoT platform.
  # INTRODUTION
     This project is to determine the distance of Building cable fault from the base station in kilometres and displayed over the internet. Building cable system is a common followed in major areas in Metro cities. While a fault occurs for some reason, at that time the fixing process related to that particular cable is difficult due to exact unknown location of the fault in the cable. This Technology is used to find out the exact location of the fault and to send data in graphical format to our website using a GSM module at the same time it display on the LCD screen.
The project uses the standard theory of Ohms law, i.e., when a low DC voltage is applied at the feeder end through a series resistor (Cable lines),then the current would vary depending upon the location of the fault in the cable as the resistance is proportional to the distance. In case there is a short circuit (Line to Ground), the voltage across series resistors changes according to the resistance that changes with distance .This is then fed to an ADC to develop precise digital data which the programmed microcontroller of the 8051 family displays in kilometres.  Whenever a fault gets created at a point shorting two lines together, a specific voltage gets generated as per the resistors network combination. This voltage is sensed by the microcontroller and is updated to the user. The information conveyed to the user is the information regarding faults detection.
  # ADVANTAGES
* Work in real time response inter 
* Coverage area in large compared to existing system 
* cost efficient
* Devices enable by wireless communication 
* Number of components are used
* Economically reliable and low cost
  # 1. Open Circuit Fault:
    Open Circuit can be detected by measuring the capacitance between two wires. Capacitance of wires changes according to the length. The length of cable varies based on the location of cable cut (open). As the wire is open parallel wire capacitance gets reduced based on this, we can calculate the fault location.
  # 2. Short Circuit Fault:
     Short circuit can be determined by measuring resistance between two cables at one end (base station). The value of resistance tells us the exact location of short circuit.

The proposed system is to find the exact location of the fault. The project uses the standard concept of Ohms law i.e., when a low DC voltage is applied at the feeder end through a Wires lines, then current would vary depending upon the location of fault in the cable. In case there is a short circuit (Line to Ground), the voltage across series resistors changes accordingly, which is then fed to inbuilt ADC of Arduino board to develop precise digital data for display in kilometers. The fault occurring at a particular distance and the respective phase is displayed on a LCD interfaced to the Arduino board.
  # IMPLEMENTATION PROTOTYPE IMAGES:
  




