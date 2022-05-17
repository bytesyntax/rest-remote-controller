/*
  ESP8266 Awning controller to connect to existing remote control
  and send UP, DOWN and STOP commands (replacing button presses)
*/

#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

#define UP 16                   // GPIO16 send UP command
#define STOP 14                 // GPIO14 send STOP command
#define DOWN 12                 // GPIO12 send DOWN command
#define WIFI_SSID "<WiFi_SSID>" // WiFi SSID
#define WIFI_PASS "<WiFi_pwd>"  // WiFi Password
#define PRESS_DELAY 1000        // Time for pressing button

AsyncWebServer server(80);
uint8_t command = ' ';

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
  Serial.print("Connecting to SSID ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Handle the HTTP GET requests
  server.on("/up", HTTP_GET, [] (AsyncWebServerRequest * request){
    Serial.print("Got command UP");
    command = 'U';
    request->send(200, "text/plain", "OK");
  });
  server.on("/stop", HTTP_GET, [] (AsyncWebServerRequest * request){
    Serial.print("Got command STOP");
    command = 'S';
    request->send(200, "text/plain", "OK");
  });
  server.on("/down", HTTP_GET, [] (AsyncWebServerRequest * request){
    Serial.println("Got command DOWN");
    command = 'D';
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
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
