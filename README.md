# IoT Smart Gas Alert System with Edge-to-Cloud Integration

An intelligent, real-world safety solution built with an **ESP32** microcontroller that monitors environmental data in real-time. The system processes localized gas levels and climate metrics on-edge, alerts users locally via an I2C LCD and hardware buzzer, and pushes telemetry data to a cloud dashboard via the **Blynk IoT platform**.

## 🚀 Key Features
* **Real-time Edge Analysis:** Instant local threshold monitoring for hazardous gases via the MQ2 sensor.
* **Dual LCD & Cloud Telemetry:** Visual indicators for temperature ($^\circ$C) and humidity (%) fed to both an on-site I2C 16x2 LCD display and the Blynk mobile/web application.
* **Multi-Layered Alert System:** Concurrent visual (blinking LED), audible (buzzer), and remote push notifications triggered when thresholds are breached.
* **Optimized Network Logic:** Integrated non-blocking asynchronous timers (`BlynkTimer`) to prevent data packet flooding and server dropouts.

## 🛠️ Hardware Components
* **Microcontroller:** ESP32 (NodeMCU)
* **Gas Sensor:** MQ2 (Smoke, LPG, Propane)
* **Climate Sensor:** DHT11 (Temperature & Humidity)
* **Display:** 16x2 LCD with I2C module interface
* **Indicators:** Piezo Buzzer, Status LEDs (Normal / Alert)

## 💻 Tech Stack
* **Language:** C++ (Arduino IDE)
* **IoT Platform:** Blynk Cloud API
* **Protocols:** Wi-Fi (802.11 b/g/n), I2C, Virtual Pin Data Streaming

## ⚙️ How It Works
1. **Data Acquisition:** The ESP32 continuously polls the sensors using non-blocking architecture.
2. **Threshold Verification:** If `Gas Value > 2000`, the firmware transitions from `NORMAL_MODE` to `ALERT_MODE`.
3. **Cloud Broadcast:** Telemetry loops stream data to Virtual Pins (`V0`, `V1`, `V2`) to map variables directly onto the cloud UI.
