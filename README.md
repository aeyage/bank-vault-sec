# Bank Vault Security

![bank_vault_security](https://github.com/user-attachments/assets/dd7d8b47-196b-4420-a8e0-b1c59b37a4cb)

## Project Overview

The system deploys a passive infrared (PIR) motion sensor and an MC-38 door magnetic sensor switch that are interfaced with the NodeMCU-32S to detect unauthorised access to the bank vault through the use of those sensors by providing alerts in near-real-time. When the PIR sensor senses movement or the door sensor detects an opening, it sends the data to the NodeMCU-32S board. The board will then activate the buzzer, which sounds an alarm and blinks the LED as a visual alert signal.

To communicate with the cloud, the NodeMCU-32S uses the MQTT protocol to publish the intrusion event data to the Google Cloud Platform. Google Cloud enables the collection of intrusion event data and stores it in a MongoDB for data persistence. Finally, the intrusion events data from the MongoDB Atlas (cloud database) to visualise the ingested data using the Atlas dashboard.

> [!NOTE]
> Some working knowledge in physics and electronic circuits will be useful didactically albeit not necessarily required.
> Prerequisites before getting started with IoT projects are basic knowledge on sensors and low-level electronic components,
> some idea about System on a Chip (SoC), microcontrollers & microprocessors, protocols and network, and wireless tech such as
> WiFi, Zigbee, BLE, LoRa, etc. Finally, extensive knowledge on cloud computing and programming languages like C++ and Python.


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

[TBA]

## Setup Guidance

### Hardware Setup

### Software Setup



