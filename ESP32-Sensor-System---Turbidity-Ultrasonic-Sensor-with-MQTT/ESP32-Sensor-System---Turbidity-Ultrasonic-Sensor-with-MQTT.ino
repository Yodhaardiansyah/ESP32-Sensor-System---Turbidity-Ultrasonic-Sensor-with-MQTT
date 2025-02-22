/*
 * ESP32 Sensor System - Turbidity & Ultrasonic Sensor with MQTT
 * 
 * Developed by: Yodha Ardiansyah
 * Website: https://arunovasi.my.id
 * 
 * Description:
 * This program reads data from a turbidity sensor and an ultrasonic sensor, then sends the data to an MQTT broker.
 * 
 * Features:
 * - Reads turbidity sensor data (NTU & Voltage)
 * - Measures distance using an ultrasonic sensor
 * - Sends data to an MQTT broker
 * - Maintains MQTT connection
 */

#include <WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT configuration (Sensitive data is hidden)
const char* ssid = "YOUR_WIFI_SSID";          // Replace with your WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your WiFi Password
const char* mqttServer = "YOUR_MQTT_SERVER";  // Replace with your MQTT broker address
const int mqttPort = 1883;
const char* mqttUser = "YOUR_MQTT_USER";      // Replace if broker requires a username
const char* mqttPassword = "YOUR_MQTT_PASS";  // Replace if broker requires a password

WiFiClient espClient;
PubSubClient client(espClient);

// Turbidity sensor pin configuration
const int turbidityPin = 35;  // Analog pin connected to the turbidity sensor

// Ultrasonic sensor pin configuration
#define TRIG_PIN 25
#define ECHO_PIN 26

void setup() {
  // Start Serial Communication
  Serial.begin(115200);
  Serial.println("Initializing Ultrasonic and Turbidity Sensors...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

long measureDistance() {
  // Ensure TRIG_PIN is LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10µs pulse to trigger
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  long distance = duration * 0.034 / 2;

  return distance;
}

void loop() {
  // Read data from the turbidity sensor
  int sensorValue = analogRead(turbidityPin);
  float voltage = sensorValue * (3.3 / 4095.0);  // ESP32 uses a 3.3V reference
  float NTU = map(sensorValue, 0, 3700, 100, 0);

  // Measure distance with the ultrasonic sensor
  long distance = measureDistance();

  // Print data to Serial Monitor
  Serial.print("NTU: ");
  Serial.print(NTU);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" | Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send data to MQTT broker
  String payload = "{";
  payload += "\"NTU\": ";
  payload += NTU;
  payload += ", \"voltage\": ";
  payload += voltage;
  payload += ", \"distance\": ";
  payload += distance;
  payload += "}";

  client.publish("your_topic/sensor/data", payload.c_str());

  // Keep MQTT connection alive
  client.loop();

  // Delay before next reading
  delay(2000);
}
