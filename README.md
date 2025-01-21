# Bank Vault Security #

<p align="center">
<img src="https://github.com/user-attachments/assets/dd7d8b47-196b-4420-a8e0-b1c59b37a4cb" width="50%">
</p>

- - - -

Author: Aiman Hakimi

## Project Overview ##

The system deploys a passive infrared (PIR) motion sensor and an MC-38 door magnetic sensor switch that are interfaced with the NodeMCU-32S to detect unauthorised access to the bank vault through the use of those sensors by providing alerts in near-real-time. When the door and the PIR sensors detect an opening or movement in close proximity, the data will be transmitted to the NodeMCU-32S board which will then engage the buzzer to sound the alarm and blink the LED to provide a visual alert signal.

Subsequently, NodeMCU-32S interfaces with Google Cloud via MQTT protocol to publish the intrusion event data to the cloud. Google Cloud enables the ingestion of the data and stores it in MongoDB for data persistence. [connect with Atlas via URI] Finally, the intrusion events data from MongoDB Atlas to visualise the ingested data using the Atlas dashboard.

> [!NOTE]
> Some working knowledge in physics and electronics will be useful didactically albeit not necessarily required.
>> Good-to-haves before getting started with IoT projects are basic knowledge on sensors and electronic components
>> including System on a Chip, microcontrollers & microprocessors, networking protocols, and wireless connectivity such as
>> WiFi, Zigbee, BLE, LoRa, etc. Finally, extensive knowledge in cloud computing and programming languages like C++, Python, and Lua (non-exhaustive list).


## System Architecture ##

### Components ###

Hardware  | Software
------------- | -------------
NodeMCU-32S WiFi Bluetooth BLE IoT Dev Board  | Google Cloud Platform
Passive Infrared Motion Sensor  | Arduino IDE
MC-38 Door Magnetic Sensor | MongoDB Atlas
Active Buzzer - PCB Mount | \|
LED 5mm | \|
Resistor 0.25W 5% 1M2 Ohm | \|
Male-to-Male Jumper Wires | \|

### Schematic Diagram<a name="DIAG"></a>

<p align="center">
<img src="https://github.com/user-attachments/assets/018c6123-b557-465e-a160-82bed9491b87" width="50%">
</p>

## Setup Guide

### Hardware Setup

We may commence setting up the project by wiring each component on the NodeMCU-32S board before interfacing it with the software.

>[!IMPORTANT]
> The NodeMCU-32S board has several GPIO pins. For a clearer understanding of the available pins on the board, please refer to
>[pinout diagram](https://wiki.geekworm.com/NodeMCU-32S) or [the schematic diagram](#DIAG).


  - Active Buzzer - PCB Mount
    - GPIO12 -> +ve leg
    - GND -> -ve leg

  - PIR Motion Sensor
    - VCC -> 3.3V
    - GND -> GND
    - OUT -> GPIO14

  - MC-38 Door Magnetic Sensor
    - One end -> GND
    - Another end -> GPIO16

  - LED 5mm
    - Anode -> GPIO18 through the resistor 0.25W 5% 1M2 Ohm
    - Cathode -> GND

>[!NOTE]
> You may use M-M, M-F, F-F jumper wires to connect the components to any available GPIO pin.
> Please take care to match the pin number with the value defined in the source code
> to ensure that the data can be ingested and read successfully in the software section later on.

### Software Setup



