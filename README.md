# Bank Vault Security

![bank_vault_security](https://github.com/user-attachments/assets/dd7d8b47-196b-4420-a8e0-b1c59b37a4cb)

## Project Overview

The system deploys a passive infrared (PIR) motion sensor and an MC-38 door magnetic sensor switch that are interfaced with the NodeMCU-32S to detect unauthorised access to the bank vault through the use of those sensors by providing alerts in near-real-time. When the PIR sensor senses movement or the door sensor detects an opening, it sends the data to the NodeMCU-32S board. The board will then activate the buzzer, which sounds an alarm and blinks the LED as a visual alert signal.

Subsequently, NodeMCU-32S interfaces with Google Cloud via MQTT protocol to publish the intrusion event data to the cloud. Google Cloud enables the ingestion of the data and stores it in MongoDB for data persistence. [connect with Atlas via URI] Finally, the intrusion events data from MongoDB Atlas to visualise the ingested data using the Atlas dashboard.

> [!NOTE]
> Some working knowledge in physics and electronics will be useful didactically albeit not necessarily required.
> Good-to-haves before getting started with IoT projects are basic knowledge on sensors and electronic components
> including System on a Chip, microcontrollers & microprocessors, networking protocols, and wireless tech such as
> WiFi, Zigbee, BLE, LoRa, etc. Finally, extensive knowledge in cloud computing and programming languages like C++ and Python (non-exhaustive list).


## System Architecture

### Components

#### Hardware

- NodeMCU-32S WiFi Bluetooth BLE IoT Dev Board
- Passive Infrared Motion Sensor
- MC-38 Door Magnetic Sensor
- Active Buzzer - PCB Mount
- LED 5mm

#### Software

- Google Cloud Platform
- Arduino IDE
- MongoDB Atlas

### Architecture Diagram
![iot_proj](https://github.com/user-attachments/assets/018c6123-b557-465e-a160-82bed9491b87)



## Setup Guidance

### Hardware Setup

### Software Setup



