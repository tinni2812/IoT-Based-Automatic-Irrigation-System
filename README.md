# IoT-Based Automatic Irrigation System

## Overview
The IoT-Based Automatic Irrigation System is a smart farming solution that automates irrigation using real-time soil moisture monitoring. The system uses an ESP32 microcontroller to monitor soil conditions and control a water pump automatically through a relay module. Integration with the Blynk app enables remote monitoring and control.

---

## Features
- Real-time soil moisture monitoring
- Automatic water pump control
- Remote monitoring using Blynk app
- Wi-Fi enabled IoT system
- Efficient water conservation
- Low-cost smart irrigation solution

---

## Technologies Used
- ESP32
- Arduino IDE
- Blynk IoT Platform
- Embedded C/C++

---

## Components Used
- ESP32 Development Board
- Soil Moisture Sensor
- Relay Module
- DC Water Pump
- Jumper Wires
- Power Supply

---

## Working Principle
The soil moisture sensor continuously checks the moisture level in the soil. When the moisture level drops below a predefined threshold, the ESP32 activates the relay module, which turns on the water pump automatically. Once sufficient moisture is detected, the pump is switched off. The Blynk app enables remote monitoring and control over the irrigation system through Wi-Fi connectivity.

---

## Project Structure

```bash
IoT-Based-Automatic-Irrigation-System/
│
├── code/
│   └── irrigation_system.ino
│
├── results/
│   ├── system_setup.jpg
│   ├── working_demo.jpg
│   └── circuit_diagram.png
│
├── README.md
└── .gitignore
