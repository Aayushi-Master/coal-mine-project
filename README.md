⛏️ **Smart Coal Mine Safety & Monitoring System**

An IoT-based coal mine safety monitoring system that continuously detects hazardous gas levels and wirelessly transmits real-time data for remote monitoring. The project uses ESP32/NodeMCU, an MQ-2 gas sensor, and ThingSpeak to improve miner safety through continuous environmental monitoring and instant alerts.

📌 **Overview**

Underground coal mines are hazardous due to the presence of toxic and combustible gases and limited communication. This project provides a low-cost monitoring solution that continuously measures gas concentration, sends the data wirelessly to a receiver node, uploads it to ThingSpeak, and generates alerts whenever unsafe conditions are detected.

🚀 **Features**

* 🌡️ Real-time hazardous gas monitoring using the MQ-2 sensor
* 📡 Wireless communication between ESP32/NodeMCU devices
* ☁️ Live data visualization on ThingSpeak
* 🚨 Automatic alerts when gas levels exceed the safety threshold
* 📈 Continuous monitoring with real-time graphs
* 💰 Low-cost and easy-to-implement IoT solution

🛠️ **Hardware Used**

* ESP32 / NodeMCU
* MQ-2 Gas Sensor
* Breadboard
* Jumper Wires
* LEDs
* Buzzer
* USB Cable

💻 **Software Used**

* Arduino IDE
* ESP32 / ESP8266 Board Package
* ThingSpeak
* Git & GitHub

⚙️ **Working Principle**

1. The MQ-2 sensor continuously measures gas concentration.
2. The ESP32/NodeMCU reads the sensor data.
3. The data is transmitted wirelessly to the receiver node.
4. The receiver uploads the readings to ThingSpeak.
5. Users can monitor live sensor data through ThingSpeak graphs, and alerts are generated when gas levels become unsafe.

⚡ **Before Uploading the Code**

Before uploading the code to your ESP32/NodeMCU, replace the placeholder values in the source code with your own credentials:

* 📶 Wi-Fi SSID
* 🔒 Wi-Fi Password
* ☁️ ThingSpeak Channel ID
* 🔑 ThingSpeak Write API Key
* 🌐 Server IP Address (if applicable)
* 📝 Any other configuration values marked in the code

The project will not function correctly until these values are updated.

🔮 **Future Enhancements**

* 📶 LoRa communication for longer-range transmission
* 🌡️ Additional sensors (temperature, humidity, flame, CO, methane, etc.)
* 📱 Mobile application for remote monitoring
* 🔔 SMS, email, or push notifications
* 🧠 AI-based prediction of hazardous conditions
* 🗺️ Miner location tracking with an emergency SOS feature
* 🔒 Secure encrypted communication
* ☁️ Advanced cloud dashboard with analytics
* 💾 Local data logging during internet outages

👩‍💻 **Author**

Aayushi Master

Electronics & Communication Engineering Student with an interest in IoT and Embedded Systems.
