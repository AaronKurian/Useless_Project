#include <WiFi.h>
#include <ArduinoWebsockets.h>

using namespace websockets;

const char* ssid = "Pixel 6A";                             // Replace with your WiFi SSID
const char* password = "123456785";                        // Replace with your WiFi Password
const char* wsServerUrl = "ws://192.168.130.236:8000/ws";  // Replace with your WebSocket server URL

int motorPinLB = 2;   // GPIO pin connected to the LED
int motorPinLF = 4;   // GPIO pin connected to the LED
int motorPinRB = 5;   // GPIO pin connected to the LED
int motorPinRF = 18;  // GPIO pin connected to the LED

WebsocketsClient client;

// Function to handle messages from the WebSocket server
void onMessageCallback(WebsocketsMessage message) {
  String response = message.data();
  response.trim();  // Trim whitespace for accurate comparison

  Serial.println("Server response: " + response);

  if (response == "stop") {
    digitalWrite(motorPinLB, LOW);
    digitalWrite(motorPinRB, LOW);
    digitalWrite(motorPinLF, LOW);
    digitalWrite(motorPinRF, LOW);
  } else if (response == "backward") {
    digitalWrite(motorPinLB, HIGH);
    digitalWrite(motorPinRB, HIGH);
    digitalWrite(motorPinLF, LOW);
    digitalWrite(motorPinRF, LOW);
  } else if (response == "forward") {
    digitalWrite(motorPinLB, LOW);
    digitalWrite(motorPinRB, LOW);
    digitalWrite(motorPinLF, HIGH);
    digitalWrite(motorPinRF, HIGH);
  } else if (response == "right") {
    digitalWrite(motorPinLB, LOW);
    digitalWrite(motorPinRB, HIGH);
    digitalWrite(motorPinLF, HIGH);
    digitalWrite(motorPinRF, LOW);
  } else if (response == "left") {
    digitalWrite(motorPinLB, HIGH);
    digitalWrite(motorPinRB, LOW);
    digitalWrite(motorPinLF, LOW);
    digitalWrite(motorPinRF, HIGH);
  }
  else {
    digitalWrite(motorPinLB, LOW);
    digitalWrite(motorPinRB, LOW);
    digitalWrite(motorPinLF, LOW);
    digitalWrite(motorPinRF, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("\nConnecting to WiFi");

  pinMode(motorPinLB, OUTPUT);
  pinMode(motorPinRB, OUTPUT);
  pinMode(motorPinLF, OUTPUT);
  pinMode(motorPinRF, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Connect to WebSocket server
  do {
    client.onMessage(onMessageCallback);
    client.connect(wsServerUrl);

    if (client.available()) {
      Serial.println("Connected to WebSocket server");
    } else {
      Serial.println("WebSocket connection failed");
    }
  } while (!client.available());
}

void loop() {
  // Keep the connection alive and process incoming messages
  client.poll();
}
