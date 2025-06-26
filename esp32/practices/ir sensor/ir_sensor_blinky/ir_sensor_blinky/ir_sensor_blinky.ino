#define BLYNK_TEMPLATE_ID "TMPL3jUEjQ-lL"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "GG1x0wlMxamn6Jn-bVgruRxQ15j5oWgV"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "acts";
char pass[] = "";

#define IR_SENSOR_PIN 15 // IR sensor OUT to GPIO 15

void setup()
{
  Serial.begin(115200);
  pinMode(IR_SENSOR_PIN, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  int sensorValue = digitalRead(IR_SENSOR_PIN);

  // Send sensor value to Blynk (V0)
  Blynk.virtualWrite(V3, sensorValue);

  // Optional: Print to Serial Monitor
  if (sensorValue == LOW) {
    Serial.println("Obstacle Detected");
  } else {
    Serial.println("No Obstacle");
  }

  Blynk.run();
  delay(500); // Adjust as needed
}
