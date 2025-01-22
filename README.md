# Bank Vault Security #

<p align="center">
<img src="https://github.com/user-attachments/assets/dd7d8b47-196b-4420-a8e0-b1c59b37a4cb" width="50%">
</p>

Authored by Aiman Hakimi, 2025.

- - - -

## Project Overview ##

The system deploys a passive infrared (PIR) motion sensor and an MC-38 door magnetic sensor switch that are interfaced with the NodeMCU-32S to detect unauthorised access to the bank vault through the use of those sensors by providing alerts in near-real-time. When the door and the PIR sensors detect an opening or movement in close proximity, the data will be transmitted to the NodeMCU-32S board which will then engage the buzzer to sound the alarm and blink the LED to provide a visual alert signal.

Subsequently, NodeMCU-32S interfaces with Google Cloud via MQTT protocol to publish the intrusion event data to the cloud. Google Cloud enables the ingestion of the data and stores it in MongoDB for data persistence. Finally, the intrusion events data from MongoDB Atlas to visualise the ingested data using the Atlas dashboard.

> [!NOTE]
> Some working knowledge in physics and electronics will be useful didactically albeit not necessarily required.
>> Good-to-haves before getting started with IoT projects are basic knowledge in electronic components
>> including microcontrollers, sensors, actuators, and servo, alongside with networking protocols, and wireless connectivity such as
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
> The NodeMCU-32S board has several GPIO pins. For a clearer understanding of the available pins on the board, kindly refer to
> [pinout diagram](https://wiki.geekworm.com/NodeMCU-32S) or the [schematic diagram](#DIAG).

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
> to ensure that the data can be ingested and read successfully in the software section below.

### Software Setup

#### 1. Arduino IDE 

Download the latest release of [Arduino IDE](https://www.arduino.cc/en/software) and set it up by installing all necessary libraries such as `Arduino_JSON`, `EspMQTTClient` and configure the board by installing and including `esp32` library in the IDE through board manager. 

Connect your machine to the NodeMCU-ESP32 via serial port (COMx) before compiling `intru_det.ino` sketch.

#### 2. Google Compute Engine Virtual Machine

Create a VM instance on the cloud console. 

<p align="center">
<img src="https://github.com/user-attachments/assets/81bc6f4c-819d-4b70-aa8d-0fc6f09e519b" width="50%">
</p>

Upon completion, spin up the instance and SSH into the newly created VM to install the MQTT broker to ensure that the publishers and subscribers route the messages correctly.

```sh
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo apt-get install mosquitto
$ sudo apt-get install mosquito-clients
```

>[!TIP]
> By default, most cloud vendors block all ingress traffic to ensure maximum security. This includes Google
> Cloud Platform (GCP). To expose your service to external machines or users, particularly for MQTT, you
> have to explicitly open the required ports. In this regard, MQTT uses port 1883 for non-TLS communications.

Configure Virtual Private Cloud (VPC) network and set up the firewall rules accordingly to allow ingress traffic on TCP port 1883 to traverse on the network.

> [!IMPORTANT]
> Note that setting the source IP ranges to **0.0.0.0/0** will allow access from anywhere, which is not recommended for
> production environments. As for the priority, VPC firewall rules with lower numbers have higher priority and
> will be applied first.

#### 3. MongoDB Atlas

A persistent data storage is required for this use case instead of ingesting and storing the event data in localhost to preserve information across multiple instances.

Create an Atlas cluster and configure it accordingly. Upon completion, authenticate and set up the connection with MongoDB Driver to retrieve the URI for database deployment.

#### 4. MQTT and Database Configurations

Check on the current state and status of the Mosquitto MQTT broker service to ensure that the
service is functioning as expected. In this regard, we want to determine if the Mosquitto service is running (active), stopped (inactive), or has failed.

```sh
$ sudo systemctl status mosquitto
```
If the Mosquitto service is disabled/ not running, execute the following commands to enable and start the service accordingly.

```sh
$ sudo systemctl enable mosquito
$ sudo systemctl start mosquito
```
In order to ingest data into the database through the MQTT client, Paho MQTT library for Python is required to allow Python applications to use MQTT for messaging.

```sh
$ sudo apt install python3-pip
$ pip install paho-mqtt
```
Install MongoDB and pymongo library which is a Python driver to allow interaction with MongoDB using Python.

```sh
$ sudo apt-get install -y mongodb
$ pip install pymongo
```
Extract the contents from `mongo_ingest.py` and nano into the script in the cloud VM CLI and paste the contents. Write out (<kbd>⌃</kbd> + O) the script and
exit the nano editor (<kbd>⌃</kbd> + X).

Run the data ingestion script.

```sh
$ python3 mongo_ingest.py
```

## Data Visualisation

The ingested data is visualised in MongoDB Atlas via Charts in near-real-time.

<p align="center">
<img src="https://github.com/user-attachments/assets/262cad02-8974-4d8a-a934-930075d00523" width="50%">
</p> 

<p align="center">
<img src="https://github.com/user-attachments/assets/6243f8f2-f071-40f0-b300-3a94855cd848" width="50%">
</p>
