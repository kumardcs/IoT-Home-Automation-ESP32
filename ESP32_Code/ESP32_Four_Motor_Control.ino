#include <WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "";
const char* password = "";

// MQTT Broker settings (using free HiveMQ broker)
const char* mqtt_server = "";
const int mqtt_port = 8883;
const char* mqtt_client_id = "ESP32_LED_Controller";

// MQTT Topics
const char* topic_command = "home/led/command";  // Subscribe to receive commands
const char* topic_status = "home/led/status";    // Publish LED status

// Relay/LED pins
const int LED1_PIN = 25;
const int LED2_PIN = 26;
const int LED3_PIN = 27;
const int LED4_PIN = 14;

// LED states
bool led1_state = false;
bool led2_state = false;
bool led3_state = false;
bool led4_state = false;

WiFiClient espClient;
PubSubClient client(espClient);

// Connect to WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  // Parse command: format "LED1:ON" or "LED1:OFF"
  if (message.startsWith("LED1:")) {
    led1_state = message.endsWith("ON");
    digitalWrite(LED1_PIN, led1_state ? HIGH : LOW);
  }
  else if (message.startsWith("LED2:")) {
    led2_state = message.endsWith("ON");
    digitalWrite(LED2_PIN, led2_state ? HIGH : LOW);
  }
  else if (message.startsWith("LED3:")) {
    led3_state = message.endsWith("ON");
    digitalWrite(LED3_PIN, led3_state ? HIGH : LOW);
  }
  else if (message.startsWith("LED4:")) {
    led4_state = message.endsWith("ON");
    digitalWrite(LED4_PIN, led4_state ? HIGH : LOW);
  }
  else if (message == "ALL:ON") {
    led1_state = led2_state = led3_state = led4_state = true;
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
  }
  else if (message == "ALL:OFF") {
    led1_state = led2_state = led3_state = led4_state = false;
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
  }

  // Publish updated status
  publishStatus();
}

// Reconnect to MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect(mqtt_client_id)) {
      Serial.println("connected");
      client.subscribe(topic_command);
      publishStatus();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Publish LED status as JSON
void publishStatus() {
  String status = "{\"led1\":\"" + String(led1_state ? "ON" : "OFF") + 
                  "\",\"led2\":\"" + String(led2_state ? "ON" : "OFF") +
                  "\",\"led3\":\"" + String(led3_state ? "ON" : "OFF") +
                  "\",\"led4\":\"" + String(led4_state ? "ON" : "OFF") + "\"}";
  
  client.publish(topic_status, status.c_str());
  Serial.print("Status published: ");
  Serial.println(status);
}

void setup() {
  Serial.begin(115200);
  
  // Initialize relay pins
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  
  // Set initial state to OFF
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Publish status every 30 seconds
  static unsigned long lastPublish = 0;
  if (millis() - lastPublish > 30000) {
    publishStatus();
    lastPublish = millis();
  }
}
