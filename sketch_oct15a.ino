#define BLYNK_TEMPLATE_ID "TMPL3nIJM4WYV"
#define BLYNK_TEMPLATE_NAME "smart moisture monitoring esp32"
#define BLYNK_AUTH_TOKEN "goAwH16SgRwtzXjRABzaAsPrRFg2tY-1"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Ombiko myre";
char pass[] = "12345678";

#define SOIL_PIN 34
#define RELAY_PIN 23

int threshold = 1800; // Adjust based on testing

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  int moisture = analogRead(SOIL_PIN);
  Serial.print("Moisture: ");
  Serial.println(moisture);

  // Send sensor value to Blynk app
  Blynk.virtualWrite(V1, moisture);

  // Control relay based on soil moisture
  if (moisture > threshold) {
    digitalWrite(RELAY_PIN, LOW);   // Turn ON relay (soil dry)
    Blynk.virtualWrite(V2, 1);       // Send relay status to app
    Serial.println("Soil is Dry → Relay ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH);    // Turn OFF relay (soil wet)
    Blynk.virtualWrite(V2, 0);
    Serial.println("Soil is Wet → Relay OFF");
  }

  delay(2000);
}
