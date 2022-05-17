/*
  ESP8266 Awning controller to connect to existing remote control
  and send UP, DOWN and STOP commands (replacing button presses)
*/

#include "WiFiManager.h"
#include <ESP8266WebServer.h>

#define UP 16                       // GPIO16 send UP command
#define STOP 14                     // GPIO14 send STOP command
#define DOWN 12                     // GPIO12 send DOWN command
#define PRESS_DELAY 1000            // Time for pressing button
#define SERVER_PORT 80              // REST API port
#define WIFI_SETUP_SSID "WifiSetup" // Name of WiFi setup network

uint8_t command = ' ';
ESP8266WebServer server(SERVER_PORT);

void setup() {
  Serial.begin(115200);

  // Pin mode and intial value
  pinMode(DOWN, OUTPUT);
  digitalWrite(DOWN, HIGH);
  pinMode(STOP, OUTPUT);
  digitalWrite(STOP, HIGH);
  pinMode(UP, OUTPUT);
  digitalWrite(UP, HIGH);

  // WiFi connect
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res;
  res = wm.autoConnect(WIFI_SETUP_SSID);
  if(!res) {
    Serial.println("Failed to connect.");
  }
  else {
    Serial.print("Connected to ");
    Serial.println(WiFi.localIP());
  }

  // Handle the HTTP GET requests
  server.on("/up", []() {
    command = 'U';
    server.send(200, "text/plain", "OK");
  });
  server.on("/stop", []() {
    command = 'S';
    server.send(200, "text/plain", "OK");
  });
  server.on("/down", []() {
    command = 'D';
    server.send(200, "text/plain", "OK");
  });
  server.onNotFound([]() {
    server.send(404, "text/plain", "Not found");
  });

  server.begin();
  Serial.print("Server started on port ");
  Serial.println(SERVER_PORT);
}

void loop() {
  server.handleClient();

  // Check if 'command' set and act accordingly
  // (delay does not seem to work in setup section)
  if(command == 'U') {
    Serial.println("Sending command UP");
    digitalWrite(UP, LOW);
    delay(PRESS_DELAY);
    digitalWrite(UP, HIGH);
  }
  else if(command == 'S') {
    Serial.println("Sending command STOP");
    digitalWrite(STOP, LOW);
    delay(PRESS_DELAY);
    digitalWrite(STOP, HIGH);
  }
  else if(command == 'D') {
    Serial.println("Sending command DOWN");
    digitalWrite(DOWN, LOW);
    delay(PRESS_DELAY);
    digitalWrite(DOWN, HIGH);
  }
  command = ' ';
}
