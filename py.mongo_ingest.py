import json 
import pymongo 
import paho.mqtt.client as mqtt 

from datetime import datetime, timezone 
from pymongo.mongo_client import MongoClient 
from pymongo.server_api import ServerApi

uri = "mongodb+srv://sham:1234@project357.2awiz.mongodb.net/?retryWrites=true&w=majority&appName=Project357"
client = MongoClient(uri, server_api=ServerApi('1'))

# Test connection to MongoDB Atlas
try:
    client.admin.command('ping')
    print("Pinged your deployment. You successfully connected to MongoDB!")
except Exception as e:
    print(f"Failed to connect to MongoDB: {e}")

# Select the database and collection
db = client["smarthome"]
collection = db["iot"]

# MQTT configuration
mqtt_broker_address = ""
mqtt_topic = ""

# Define the callback function for connection
def on_connect(client, userdata, flags, reason_code):
    if reason_code == 0:
        print("Successfully connected")
        client.subscribe(mqtt_topic)

# Define the callback function for ingesting data into MongoDB
def on_message(client, userdata, message):
    payload = message.payload.decode("utf-8")
    print(f"Received message: {payload}")
    
    try:
        # Parse the JSON payload
        data = json.loads(payload)
        pir_value = data.get("PIR") 
        door_value = data.get("Door")

        # Get the current timestamp
        timestamp = datetime.now(timezone.utc)

        # Create the document to insert into MongoDB
        document = {
            "timestamp": timestamp,
            "pir_value": pir_value,
            "door_value": door_value
        }

        # Insert the document into MongoDB
        collection.insert_one(document)
        print("Data ingested into MongoDB")
        
    except json.JSONDecodeError as e:
        print(f"Failed to decode JSON: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

# Create a MQTT client instance
client_mqtt = mqtt.Client()

# Attach the callbacks
client_mqtt.on_connect = on_connect
client_mqtt.on_message = on_message

# Connect to MQTT broker
client_mqtt.connect(mqtt_broker_address, , 60)

# Start the MQTT loop
client_mqtt.loop_forever()
