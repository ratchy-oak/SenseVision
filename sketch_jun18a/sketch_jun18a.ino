#include <WiFi.h>

const char* ssid     = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
}