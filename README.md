A real-time IoT-based home automation system that enables remote control of household appliances through a web dashboard. The system uses ESP32 microcontroller, MQTT protocol, and relay modules to control multiple devices including motors, lights, and other AC appliances over WiFi.
✨ Key Features

Remote Control: Control 4 appliances from anywhere via web dashboard
Real-time Feedback: Instant status updates displayed on the dashboard
MQTT Protocol: Lightweight and efficient communication
Relay Isolation: Optocoupler-isolated relay module for safety
Scalable Architecture: Easy to expand to more devices
Responsive UI: Works seamlessly on mobile and desktop browsers

🛠️ Technologies Used

Microcontroller: ESP32 DevKit (WiFi enabled)
Communication Protocol: MQTT (Message Queuing Telemetry Transport)
MQTT Broker: HiveMQ Public Broker
Programming Language: C++ (Arduino IDE)
Frontend: HTML, CSS, JavaScript, MQTT.js
Hardware: 4-Channel Relay Module with optocoupler isolation
Appliances Controlled: Motors, LEDs, and other AC devices

🔧 Hardware Components

ESP32 Development Board
4-Channel 5V Relay Module (10A/250V AC)
DC Motors (for testing)
LEDs with 220Ω resistors
Jumper wires
Breadboard
5V Power Supply

📡 System Architecture
Mobile/Web Dashboard → HiveMQ Broker → ESP32 → Relay Module → Appliances (Motors/LEDs)
                         ↑                ↓
                         └────────────────┘
                         (Bidirectional MQTT Communication)
🎯 How It Works

User clicks ON/OFF button on web dashboard
Dashboard publishes MQTT message to HiveMQ broker (e.g., test/led1/command: ON)
ESP32 subscribes to command topics and receives the message
ESP32 triggers corresponding GPIO pin (25, 26, 27, or 14)
Relay module switches the appliance (motor/LED) ON or OFF
ESP32 publishes status back to broker (e.g., test/led1/status: ON)
Dashboard receives status update and displays real-time feedback

🔌 Circuit Connections
ESP32 to Relay Module:

VIN (5V) → Relay VCC
GND → Relay GND
GPIO 25 → Relay IN1
GPIO 26 → Relay IN2
GPIO 27 → Relay IN3
GPIO 14 → Relay IN4

Relay to Appliances:

Each relay COM → Power supply positive
Each relay NO → Motor/LED positive terminal
Common ground for all devices

🌐 MQTT Topics
DeviceCommand TopicStatus TopicMotor 1test/led1/commandtest/led1/statusMotor 2test/led2/commandtest/led2/statusMotor 3test/led3/commandtest/led3/statusMotor 4test/led4/commandtest/led4/status
🚀 Setup & Installation
Prerequisites

Arduino IDE with ESP32 board support
PubSubClient library
WiFi credentials

Steps

Clone this repository
Open ESP32_Four_Motor_Control.ino in Arduino IDE
Update WiFi credentials in the code
Upload code to ESP32
Open dashboard.html in any web browser
Control your appliances remotely!

📊 Project Demo

Real-time motor control via web interface
Visual indicators showing device status
Instant command execution with feedback
Connection status monitoring

🔒 Safety Features

Optocoupler isolation between ESP32 and high voltage
Relay module rated for 10A at 250V AC
Proper enclosure recommended for production use
Circuit breaker protection for AC mains

🎓 Learning Outcomes

Understanding of IoT communication protocols (MQTT)
ESP32 WiFi programming
Relay module interfacing
Web-based dashboard development
Pub-Sub messaging architecture
Real-time bidirectional communication

🔮 Future Enhancements

Voice control integration (Alexa/Google Assistant)
Mobile app development (Android/iOS)
Timer and scheduling features
Energy consumption monitoring
Add authentication for secure access
Cloud database for logging device states



Email:kumardcs888@gmail.com

🙏 Acknowledgments

HiveMQ for providing free MQTT broker
Arduino and ESP32 community
Open-source libraries used in this project


⭐ If you found this project helpful, please give it a star!
#IoT #ESP32 #HomeAutomation #MQTT #Arduino #SmartHome #EmbeddedSystems
