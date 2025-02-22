Here’s a **professional and engaging README** for your project:  

---

# **ESP32 Sensor System - Turbidity & Ultrasonic Sensor with MQTT**  

## **Project Overview**  
This project utilizes an **ESP32** microcontroller to monitor **water turbidity** and **distance measurements** using:  
- A **turbidity sensor** (measuring NTU & voltage)  
- An **ultrasonic sensor** (measuring distance)  

The collected data is sent to an **MQTT broker**, enabling real-time monitoring and data integration with cloud platforms or IoT dashboards.

## **Features**  
✅ **WiFi Connectivity** - Connects ESP32 to the internet via WiFi.  
✅ **MQTT Communication** - Sends sensor data to an MQTT broker.  
✅ **Turbidity Measurement** - Converts sensor readings into NTU (Nephelometric Turbidity Units).  
✅ **Ultrasonic Distance Measurement** - Provides real-time distance readings.  
✅ **Serial Output** - Displays sensor data on the Serial Monitor for debugging.  

## **Hardware Requirements**  
🔹 **ESP32** (WiFi-enabled microcontroller)  
🔹 **Turbidity Sensor** (e.g., SEN0189)  
🔹 **Ultrasonic Sensor** (e.g., HC-SR04)  
🔹 **Jumper Wires & Breadboard**  

## **Software Requirements**  
🛠 **Arduino IDE** (or PlatformIO)  
🛠 **PubSubClient Library** (for MQTT)  
🛠 **WiFi Library** (for ESP32)  

## **Circuit Diagram**  
*(Ensure proper wiring before running the code.)*  

| Component          | ESP32 Pin  |
|-------------------|------------|
| Turbidity Sensor | **GPIO 35** |
| Ultrasonic Trig  | **GPIO 25** |
| Ultrasonic Echo  | **GPIO 26** |

## **Installation & Setup**  
1️⃣ Install the **Arduino IDE** and ESP32 board support.  
2️⃣ Add the required **libraries** in the Arduino Library Manager:  
   - `PubSubClient`  
   - `WiFi`  
3️⃣ Update the `ssid`, `password`, and MQTT credentials in the code.  
4️⃣ Connect ESP32 to your sensors according to the **circuit diagram**.  
5️⃣ Upload the code to ESP32 and open the Serial Monitor.  
6️⃣ Monitor real-time data via **MQTT Dashboard** or **Cloud Server**.  

## **Code Explanation**  
### **WiFi & MQTT Setup**  
The ESP32 connects to WiFi and then establishes a connection with an MQTT broker.  
```cpp
const char* ssid = "YOUR_WIFI_SSID";  
const char* password = "YOUR_WIFI_PASSWORD";  
const char* mqttServer = "YOUR_MQTT_SERVER";
```

### **Turbidity Sensor Data Conversion**  
The analog signal is converted into NTU (Nephelometric Turbidity Units):  
```cpp
int sensorValue = analogRead(turbidityPin);
float voltage = sensorValue * (3.3 / 4095.0);
float NTU = map(sensorValue, 0, 3700, 100, 0);
```

### **Ultrasonic Distance Measurement**  
The `measureDistance()` function calculates the distance based on pulse duration:  
```cpp
long distance = duration * 0.034 / 2;
```

### **Sending Data to MQTT Broker**  
The collected data is formatted into a JSON-like string and published to an MQTT topic:  
```cpp
String payload = "{ \"NTU\": " + String(NTU) + ", \"voltage\": " + String(voltage) + ", \"distance\": " + String(distance) + "}";
client.publish("your_topic/sensor/data", payload.c_str());
```

## **MQTT Data Format**  
The data sent to the MQTT broker follows this JSON structure:  
```json
{
  "NTU": 45.7,
  "voltage": 1.89,
  "distance": 15
}
```

## **Future Enhancements**  
🚀 Add **Blynk Integration** for mobile monitoring.  
🚀 Implement **Cloud Storage** (e.g., Firebase, ThingsBoard).  
🚀 Improve **Calibration for Turbidity Sensor**.  

## **Credits**  
👨‍💻 **Developed by:** Yodha Ardiansyah  
🌐 **Website:** [arunovasi.my.id](https://arunovasi.my.id)  

---

This **README** ensures clarity, professional formatting, and easy-to-follow instructions. 🚀 Let me know if you need modifications! 😊
