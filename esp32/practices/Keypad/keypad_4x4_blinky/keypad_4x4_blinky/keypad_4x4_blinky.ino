#define BLYNK_TEMPLATE_ID "TMPL3jUEjQ-lL"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "GG1x0wlMxamn6Jn-bVgruRxQ15j5oWgV"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Keypad.h>

// WiFi credentials
char ssid[] = "acts";         // Replace with your WiFi SSID
char pass[] = "";     // Replace with your WiFi password

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {18, 19, 21, 22};
byte colPins[COLS] = {23, 5, 17, 16};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    Blynk.virtualWrite(V2, String(key)); // Send key to Blynk Virtual Pin V0
  }
}
