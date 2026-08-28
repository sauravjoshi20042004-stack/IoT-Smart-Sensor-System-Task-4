# 🌐 Smart Automation System – Task 4

## Cloud-Connected IoT System Using ESP32, LDR Sensor and ThingSpeak

A cloud-connected **Smart Automation System** developed using **ESP32, LDR Sensor, LED, Wokwi Simulator, and ThingSpeak IoT Cloud Platform**.

This project upgrades the Task-3 Smart Automation System by adding **Wi-Fi connectivity and real-time cloud monitoring**.

---

## 📌 Project Overview

The system automatically controls an LED according to the surrounding light intensity detected by an **LDR (Light Dependent Resistor)**.

The ESP32 reads the LDR sensor value and makes an automatic lighting decision.

At the same time, the ESP32 connects to Wi-Fi and sends the sensor data to **ThingSpeak Cloud** using an HTTP request.

The data can then be monitored through the ThingSpeak web dashboard.

### IoT Communication Flow

~~~text
LDR Sensor
     ↓
ESP32
     ↓
Wi-Fi
     ↓
ThingSpeak Cloud
     ↓
Web Dashboard
~~~

---

## 🎯 Objectives

The main objectives of this project are:

- Upgrade the Task-3 automation system into an IoT-enabled system.
- Use ESP32 for sensor processing and Wi-Fi connectivity.
- Interface an LDR sensor with ESP32.
- Automatically control an LED according to light conditions.
- Connect ESP32 to a Wi-Fi network.
- Send sensor readings to ThingSpeak Cloud.
- Display real-time sensor data using a cloud dashboard.
- Understand device-to-cloud communication.
- Gain practical experience in Embedded Systems and IoT.

---

## 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| ESP32 | Microcontroller and Wi-Fi connectivity |
| LDR / Photoresistor | Light intensity detection |
| LED | Automatic lighting indicator |
| 220Ω Resistor | LED current limiting |
| Wokwi | Circuit simulation |
| ThingSpeak | IoT cloud platform |
| Arduino C/C++ | Programming |
| HTTP | Cloud data transmission |

---

## 🔌 Components Required

- ESP32 DevKit
- LDR / Photoresistor
- LED
- 220Ω Resistor
- Jumper Wires
- Wokwi Simulator
- ThingSpeak Account

---

## 🔗 Pin Connections

| Component | Pin | ESP32 Connection |
|---|---|---|
| Photoresistor | VCC | 3.3V |
| Photoresistor | GND | GND |
| Photoresistor | AO | GPIO 34 |
| Photoresistor | DO | Not Connected |
| LED | Anode (+) | GPIO 2 |
| LED | Cathode (-) | 220Ω Resistor → GND |

---

## ⚙️ Working Principle

The system works in the following steps:

### 1. Light Detection

The LDR detects the surrounding light intensity.

### 2. Sensor Reading

The ESP32 reads the analog value from the LDR through **GPIO 34**.

~~~cpp
int lightValue = analogRead(ldrPin);
~~~

### 3. Automatic LED Control

The sensor reading is compared with a predefined threshold.

~~~text
Low Light    → LED ON
Bright Light → LED OFF
~~~

### 4. Wi-Fi Connection

The ESP32 connects to the Wokwi Wi-Fi network.

~~~text
SSID: Wokwi-GUEST
Password: Empty
~~~

### 5. Cloud Communication

The ESP32 sends the sensor reading and LED status to ThingSpeak using an HTTP GET request.

### 6. Cloud Dashboard

ThingSpeak receives and stores the data and displays it using graphical charts.

---

## ☁️ ThingSpeak Cloud Integration

ThingSpeak is used as the cloud IoT platform for this project.

### Channel Details

~~~text
Channel Name: Smart Automation System
Channel ID: 3468746
Platform: ThingSpeak
~~~

### Channel Fields

| Field | Data |
|---|---|
| Field 1 | Light Intensity |
| Field 2 | LED Status |

### LED Status Values

~~~text
1 → LED ON
0 → LED OFF
~~~

---

## 📡 Data Transmission

The ESP32 sends data to ThingSpeak using an HTTP GET request.

The request contains:

~~~text
API Key
Field 1 → Light Sensor Value
Field 2 → LED Status
~~~

The communication process is:

~~~text
LDR Sensor
     ↓
ESP32
     ↓
Wi-Fi
     ↓
HTTP GET Request
     ↓
ThingSpeak Cloud
     ↓
Dashboard Graph
~~~

The program waits approximately **16 seconds** between updates to maintain the required ThingSpeak update interval.

---

## 💻 Source Code

> **Security Warning:** Never publish your real ThingSpeak Write API Key on GitHub.

Replace:

~~~cpp
YOUR_WRITE_API_KEY
~~~

with your actual API key only in your local Wokwi code.

~~~cpp
#include <WiFi.h>
#include <HTTPClient.h>

const int ldrPin = 34;
const int ledPin = 2;

// Wokwi Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ThingSpeak
const char* apiKey = "YOUR_WRITE_API_KEY";
const char* server = "http://api.thingspeak.com/update";

void setup() {

  Serial.begin(115200);

  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Smart Automation System Started");
}

void loop() {

  // Read LDR sensor value
  int lightValue = analogRead(ldrPin);

  // Low light = LED ON
  // Bright light = LED OFF

  if (lightValue > 500) {

    digitalWrite(ledPin, HIGH);

    Serial.println("Low Light - LED ON");
  }

  else {

    digitalWrite(ledPin, LOW);

    Serial.println("Enough Light - LED OFF");
  }

  // Display sensor value
  Serial.print("Light Value: ");
  Serial.println(lightValue);

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    // 1 = LED ON
    // 0 = LED OFF
    int ledStatus = (lightValue > 500) ? 1 : 0;

    String url = String(server) +
                 "?api_key=" + apiKey +
                 "&field1=" + String(lightValue) +
                 "&field2=" + String(ledStatus);

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("ThingSpeak Response: ");
    Serial.println(httpCode);

    http.end();
  }

  // ThingSpeak update interval
  delay(16000);
}
~~~

---

## 📊 ThingSpeak Dashboard

The ThingSpeak dashboard is used to monitor the sensor data received from the ESP32.

The dashboard contains:

- Light intensity graph
- LED status data
- Changing sensor readings
- Cloud-based data visualization

### Dashboard Screenshot

Add your ThingSpeak dashboard screenshot here.

**Screenshot:** ThingSpeak Dashboard

---

## 🧪 Testing and Results

The system was tested under different light conditions.

| Test Condition | Expected Result | Result |
|---|---|---|
| Low Light | LED ON | ✅ Passed |
| Bright Light | LED OFF | ✅ Passed |
| Wi-Fi Connection | ESP32 Connected | ✅ Passed |
| Cloud Upload | Data Sent to ThingSpeak | ✅ Passed |
| HTTP Communication | Response 200 | ✅ Passed |
| Graph Update | Data Visible on Dashboard | ✅ Passed |

---

## 🔦 Low-Light Test

When the light intensity is reduced:

~~~text
Low Light
    ↓
ESP32 Detects Condition
    ↓
LED ON
    ↓
Data Sent to ThingSpeak
~~~

**Screenshot:** Low-Light / LED ON

---

## 💡 Bright-Light Test

When sufficient light is detected:

~~~text
Bright Light
     ↓
ESP32 Detects Condition
     ↓
LED OFF
     ↓
Data Sent to ThingSpeak
~~~

**Screenshot:** Bright-Light / LED OFF

---

## 🖥️ Serial Monitor

The Serial Monitor displays important system information such as:

~~~text
Connecting to WiFi...
WiFi Connected!
IP Address: xxx.xxx.xxx.xxx

Smart Automation System Started

Light Value: XXXX
Low Light - LED ON

ThingSpeak Response: 200
~~~

A successful HTTP response of **200** indicates that the cloud request was successfully processed.

---

## 📈 Cloud Monitoring

The sensor value changes according to the LDR input.

The changing values are transmitted to ThingSpeak and displayed on the cloud graph.

~~~text
Sensor Reading
      ↓
ESP32 Processing
      ↓
Wi-Fi
      ↓
ThingSpeak
      ↓
Graph / Dashboard
~~~

---

## 📁 Project Structure

~~~text
Smart-Automation-System-Task-4/
│
├── README.md
│
├── smart_automation_system.ino
│
├── Circuit_Diagram.png
│
├── ThingSpeak_Dashboard.png
│
├── Low_Light_LED_ON.png
│
├── Bright_Light_LED_OFF.png
│
└── Task_4_Project_Report.pdf
~~~

---

## 🚀 How to Run the Project

### Step 1 – Open Wokwi

Open the ESP32 project in the Wokwi simulator.

### Step 2 – Check the Circuit

Make sure the following connections are correct:

~~~text
LDR AO → ESP32 GPIO 34
LED → ESP32 GPIO 2
~~~

### Step 3 – Configure ThingSpeak

Create a ThingSpeak channel and configure:

~~~text
Field 1 → Light Intensity
Field 2 → LED Status
~~~

### Step 4 – Add API Key

Copy the ThingSpeak **Write API Key** into the code.

~~~cpp
const char* apiKey = "YOUR_WRITE_API_KEY";
~~~

### Step 5 – Run Simulation

Start the Wokwi simulation.

### Step 6 – Check Serial Monitor

Verify:

~~~text
WiFi Connected!
~~~

and:

~~~text
ThingSpeak Response: 200
~~~

### Step 7 – Check ThingSpeak

Open the ThingSpeak dashboard and verify that the graph is updating.

---

## 🔐 Security

The ThingSpeak Write API Key should be treated as a private credential.

### Do Not:

- Upload the real API key to GitHub.
- Share the API key in screenshots.
- Post the API key on LinkedIn.
- Include the real API key in a public README.

### Recommended

Use:

~~~cpp
const char* apiKey = "YOUR_WRITE_API_KEY";
~~~

in publicly shared code.

---

## 🌍 Real-World Applications

This project can be used as a basic model for:

- 🏠 Smart Home Lighting
- 🏫 Smart Classroom Automation
- 🏢 Smart Building Systems
- 💡 Energy-Saving Lighting
- 🌐 IoT Monitoring Systems
- 🏭 Industrial Automation
- 🔬 IoT Education and Prototyping

---

## ⭐ Advantages

- Simple and low-cost IoT prototype.
- ESP32 provides built-in Wi-Fi.
- Automatic LED control.
- Cloud-based monitoring.
- Real-time graphical visualization.
- Easy to expand with additional sensors.
- Suitable for embedded systems and IoT learning.
- Can be converted from simulation to real hardware.

---

## ⚠️ Limitations

- The current implementation uses simulation.
- LDR ADC values are relative readings and are not calibrated physical lux measurements.
- Cloud monitoring requires Wi-Fi connectivity.
- ThingSpeak has update-rate limitations.
- The current system uses a single main sensor.

---

## 🔮 Future Scope

The system can be further improved by adding:

- Temperature and humidity sensors.
- PIR motion sensor.
- Automatic fan control.
- Multiple lighting zones.
- Mobile notifications.
- Email alerts.
- Configurable threshold values.
- Energy consumption monitoring.
- Multiple IoT sensors.
- Real ESP32 hardware.
- AI-based automation and prediction.

---

## 📚 Learning Outcomes

Through this project, the following concepts were learned:

- ESP32 programming
- LDR sensor interfacing
- Analog sensor reading
- LED control
- Wi-Fi connectivity
- HTTP communication
- IoT cloud platforms
- ThingSpeak data visualization
- Real-time sensor monitoring
- Device-to-cloud communication

---

## 🏆 Project Outcome

The Task-4 project successfully demonstrates a **cloud-connected Smart Automation System**.

The complete IoT workflow is:

~~~text
SENSING
   ↓
PROCESSING
   ↓
AUTOMATION
   ↓
WI-FI CONNECTIVITY
   ↓
CLOUD TRANSMISSION
   ↓
DATA VISUALIZATION
~~~

The project provides practical experience in **Embedded Systems, ESP32, IoT, Wi-Fi communication and cloud-based monitoring**.

---

## 👨‍💻 Author

**Saurav Joshi**

B.Tech – Electronics and Communication Engineering

Bipin Tripathi Kumaon Institute of Technology (BTKIT), Dwarahat

---

## 📌 Internship Task

**Task:** Task-4 – Cloud-Connected IoT System

**Domain:** Embedded Systems & IoT

**Cloud Platform:** ThingSpeak

**Simulator:** Wokwi

**Project:** Smart Automation System

---

## 📄 Project Report

The complete project documentation is available in:

~~~text
Task_4_Project_Report.pdf
~~~

---

## 🔗 ThingSpeak Channel

**Channel Name:** `Smart Automation System`

**Channel ID:** `3468746`

---

## 📜 License

This project is created for **educational and internship purposes**.

You are free to study and modify the project for learning purposes.

---

# ⭐ Thank You

Thank you for visiting this project repository!

If you found this project useful, consider giving the repository a ⭐.