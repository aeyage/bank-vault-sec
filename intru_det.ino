#include <WiFi.h>
#include <PubSubClient.h>

const int pirPin = 14;        
const int ledPin = 18;        
const int doorSensor = 16;    
const int buzzer = 12;        

const char* WIFI_SSID = "<Wifi Name>";          // Your WiFi SSID
const char* WIFI_PASSWORD = "<Wifi Password>";   // Your WiFi password
const char* MQTT_SERVER = "34.60.69.11";  // Your VM instance public IP address
const char* MQTT_TOPIC = "iot";           // MQTT topic for subscription
const int MQTT_PORT = 1883;               // MQTT port

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(doorSensor, INPUT_PULLUP);   // Door sensor with internal pull-up
  pinMode(pirPin, INPUT);               // PIR sensor

  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("NodeMCU32SClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int PIRvalue = digitalRead(pirPin);        // PIR sensor reading
  int DoorValue = digitalRead(doorSensor);   // Door switch reading

 
  DoorValue = (DoorValue == LOW) ? 0 : 1;  

  // Trigger buzzer and LED only when PIR detects motion or door is open
  if (PIRvalue == HIGH || DoorValue == HIGH) {
    digitalWrite(ledPin, HIGH);    
    tone(buzzer, 1000, 500);        
    char payload[100];
    snprintf(payload, sizeof(payload), "{\"PIR\":%d,\"Door\":%d}", PIRvalue, DoorValue);
    client.publish(MQTT_TOPIC, payload); 
    delay(2000); 
  } else {
    digitalWrite(ledPin, LOW);    
  }
}

