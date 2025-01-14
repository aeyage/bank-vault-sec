#include <WiFi.h>
#include <PubSubClient.h>

const int pirPin = 14;        // PIR sensor (Maker: Pin 4, NodeMCU: Pin 14)
const int ledPin = 18;        // Red LED (Maker: Pin 10, NodeMCU: Pin 18)
const int doorSensor = 16;    // Door switch
const int buzzer = 12;        // Buzzer (Relay: Pin 39, NodeMCU: Pin 32)

const char* WIFI_SSID = "cslab";          // Your WiFi SSID
const char* WIFI_PASSWORD = "aksesg31";   // Your WiFi password
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

  // If door is closed (LOW), set DoorValue to 0, else set to 1
  DoorValue = (DoorValue == LOW) ? 0 : 1;    // Door closed (LOW) gives 0, open (HIGH) gives 1

  if (PIRvalue == HIGH || DoorValue == 0) {
    digitalWrite(ledPin, HIGH);     // LED ON
    tone(buzzer, 1000, 500);        // Buzzer ON
    char payload[100];
    snprintf(payload, sizeof(payload), "{\"PIR\":%d,\"Door\":%d}", PIRvalue, DoorValue);
    client.publish(MQTT_TOPIC, payload); // Send data via MQTT
    delay(2000); // Delay to avoid repeated triggering
  } else {
    digitalWrite(ledPin, LOW);      // LED OFF
  }
}
