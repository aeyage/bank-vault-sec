#include <WiFi.h>
#include <PubSubClient.h>

const int pirPin = 14;        // Passive infrared sensor 
const int ledPin = 18;        // Red LED 
const int doorSensor = 16;    // Magnetic Contact Switch Sensor
const int buzzer = 12;        // Buzzer 

const char* WIFI_SSID = "";          // WiFi SSID
const char* WIFI_PASSWORD = "";   // WiFi password
const char* MQTT_SERVER = "";  // VM instance external IP address
const char* MQTT_TOPIC = "";           // MQTT topic for subscription
const int MQTT_PORT = ;               // MQTT port

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
  pinMode(pirPin, INPUT);              // PIR sensor

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
  int DoorValue = digitalRead(doorSensor);   // Magnetic contact switch sensor reading

  // If door is closed (LOW), set DoorValue to 0, else set to 1
  // Door closed (LOW) gives 0, open (HIGH) gives 1
  DoorValue = (DoorValue == LOW) ? 0 : 1;    

  if (PIRvalue == HIGH || DoorValue == 0) {
    digitalWrite(ledPin, HIGH);     // LED ON
    tone(buzzer, 1000, 500);        // Buzzer ON
    char payload[100];
    snprintf(payload, sizeof(payload), "{\"PIR\":%d,\"Door\":%d}", PIRvalue, DoorValue);
    client.publish(MQTT_TOPIC, payload); // Send data via MQTT
    delay(2000);                         // Delay to avoid repeated triggering
  } else {
    digitalWrite(ledPin, LOW);      // LED OFF
  }
}
