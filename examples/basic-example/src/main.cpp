#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "ThingsBoard.h"


#define WIFI_SSID             "YOUR_WIFI_AP"
#define WIFI_PASSWORD       "YOUR_WIFI_PASSWORD"

// See https://thingsboard.io/docs/getting-started-guides/helloworld/
// to understand how to obtain an access token
#define TOKEN               "YOUR_ACCESS_TOKEN"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"

WiFiClient wifi;
ThingsBoard tb(wifi);
int status = WL_IDLE_STATUS;

void setup() {
  // initialize serial for debugging
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to AP");
}

void loop() {
  delay(1000);

  if (!tb.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  Serial.println("Sending data...");

  // Uploads new telemetry to ThingsBoard using MQTT.
  // See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api
  // for more details

  tb.sendTelemetryInt("temperature", 22);
  tb.sendTelemetryFloat("humidity", 42.5);

  tb.loop();
}
