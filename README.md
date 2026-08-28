# Smart Automation System Using Arduino and LDR

## Internship Task 3 - Embedded Systems & IoT

### Project Overview

This project is an upgraded version of the Smart Lighting System developed in Task 2.

The system uses an Arduino UNO and an LDR sensor to automatically control an LED according to the surrounding light intensity.

The project also uses the Serial Monitor to display live sensor readings and the current LED status.

---

## Objective

The main objective of this project is to convert a basic sensor prototype into a smart automation system.

The project demonstrates:

- Sensor-based decision making
- IF/ELSE automation logic
- Automatic LED control
- Real-time sensor monitoring
- Basic IoT-style system behavior

---

## Components Used

- Arduino UNO
- LDR Sensor
- 10k Ohm Resistor
- LED
- 220 Ohm Resistor
- Breadboard
- Jumper Wires
- USB Cable

---

## Software Used

- Tinkercad Circuits
- Arduino IDE
- Embedded C/C++

---

## Working Principle

The LDR sensor detects the surrounding light intensity and sends an analog value to the Arduino through analog pin A0.

The Arduino continuously reads the sensor value and compares it with a predefined threshold of 500.

- If the LDR value is greater than 500, the system considers the environment dark and turns the LED ON.
- If the LDR value is 500 or below, the system considers the environment bright and turns the LED OFF.

The sensor value and LED status are displayed on the Serial Monitor for real-time monitoring.

---

## Automation Logic


IF Light Value > 500
    LED = ON
    Status = DARK

ELSE
    LED = OFF
    Status = BRIGHT

---
    
## Arduino Source Code

const int ldrPin = A0;
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(ldrPin);

  Serial.print("Light Value: ");
  Serial.println(lightValue);

  if (lightValue > 500) {
 
    digitalWrite(ledPin, HIGH);
    Serial.println("Status: DARK - LED ON");
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("Status: BRIGHT - LED OFF");
  }

  Serial.println("--------------------");

  delay(1000);
}

---

## Serial Monitor Output

Dark Condition
Light Value: 969
Status: DARK - LED ON
--------------------
Bright Condition
Light Value: 49
Status: BRIGHT - LED OFF
--------------------
The actual LDR values may vary during simulation depending on the light intensity.

---

## Circuit Diagram

The circuit consists of an Arduino UNO, LDR sensor, resistors and LED.
The same sensor prototype from Task 2 has been upgraded with automation logic and monitoring functionality for Task 3.
Circuit Diagram file:
Circuit_Diagram.jpg

---

## Monitoring

The Serial Monitor provides real-time feedback from the system.
It displays:
Current LDR sensor value
Detected light condition
LED status
This helps in monitoring the system while the simulation is running.

---

## Applications

This smart automation system can be used in:
Smart home lighting
Automatic street lighting
Office lighting systems
Parking areas
Gardens and outdoor lighting
Energy-saving lighting systems

---

## Advantages

Automatic operation
Simple and low-cost design
Reduces unnecessary power consumption
Real-time monitoring
Easy to understand and implement
Can be extended with IoT connectivity

---

## Future Improvements

The project can be further improved by:
Adding an LCD or OLED display
Connecting the system to an ESP32
Adding Wi-Fi connectivity
Sending sensor data to a cloud dashboard
Adding mobile monitoring and control

---

## Project Deliverables

Circuit Diagram
Arduino Source Code
Serial Monitor Output
Project Report
Working Explanation

---

## Conclusion

The Task 3 project successfully upgrades the previous Smart Lighting System into a basic Smart Automation System.
The Arduino reads the LDR sensor value, makes an automatic decision using IF/ELSE logic, controls the LED according to the surrounding light condition, and displays the sensor data through the Serial Monitor.
This project provides a basic understanding of automation, decision-making and monitoring in embedded systems and IoT applications.

---

##Author

Saurav Joshi
Internship Domain: Embedded Systems & IoT
Task: 3 - Smart Automation System