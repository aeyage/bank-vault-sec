# Anti-theft System

## Project Overview

The system deploys a passive infrared (PIR) motion sensor and an MC-38 door magnetic sensor switch that are interfaced with the NodeMCU-32S WiFi Bluetooth BLE IoT Dev Board to detect unauthorised access through the use of those sensors by providing alerts in near-real-time.

When the PIR sensor senses movement or the door sensor detects an opening, it sends the data to the NodeMCU-32S board. The board will then activate the buzzer, which sounds an alarm and blinks the LED as a visual alert signal.

To communicate with the cloud, the NodeMCU-32S uses the MQTT protocol to publish the intrusion event data to the Google Cloud Platform. Google Cloud enables the collection of intrusion event data and stores it in a MongoDB for data persistence. Finally, the intrusion events data from the MongoDB Atlas (cloud database) to visualise the ingested data using the Atlas dashboard.

> If using `uv` prefix all commands with `uv run` to use the environment created by default in `.venv`, e.g.,
> `uv run torchrun --standalone`.
> Alternatively, you can activate the environment once and for all with `source .venv/bin/activate`.

## System Architecture
