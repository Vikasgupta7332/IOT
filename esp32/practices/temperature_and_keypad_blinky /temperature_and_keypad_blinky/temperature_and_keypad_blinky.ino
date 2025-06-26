// DHT11 and 4x4 Keypad

#define BLYNK_TEMPLATE_ID "TMPL3jUEjQ-lL"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "GG1x0wlMxamn6Jn-bVgruRxQ15j5oWgV"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Keypad.h>

char ssid[] = "acts";      // Your WiFi SSID
char pass[] = "";         // Your WiFi password

#define DHTPIN 4           // DHT11 data pin connected to GPIO4
#define DHTTYPE DHT11      // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//IR sensor
#define IR_SENSOR_PIN 15 // IR sensor OUT to GPIO 15

//keypad
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

// Function to check WiFi connection and reconnect if needed
void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Attempting reconnection...");
    WiFi.disconnect();
    WiFi.reconnect();
    int wifi_attempts = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      wifi_attempts++;
      if (wifi_attempts > 40) { // 20 seconds timeout
        Serial.println("\nFailed to reconnect WiFi. Restarting...");
        ESP.restart();
      }
    }
    Serial.println("\nWiFi reconnected. IP address: ");
    Serial.println(WiFi.localIP());
  }
}

// Function to check Blynk connection and reconnect if needed
void checkBlynk() {
  if (!Blynk.connected()) {
    Serial.println("Blynk disconnected! Attempting reconnection...");
    Blynk.connect(10000); // Try to connect for 10 seconds
    if (!Blynk.connected()) {
      Serial.println("Failed to reconnect to Blynk.");
    } else {
      Serial.println("Blynk reconnected.");
    }
  }
}

// Function to send sensor data to Blynk and Serial Monitor
void sendSensor()
{
  checkWiFi();
  checkBlynk();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor! Check wiring.");
    return;
  }

  // Send to Blynk Virtual Pins
  Blynk.virtualWrite(V0, t); // Temperature to V0
  Blynk.virtualWrite(V1, h); // Humidity to V1
 

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // Show connection status
  Serial.print("WiFi: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
  Serial.print("Blynk: ");
  Serial.println(Blynk.connected() ? "Connected" : "Disconnected");
}

void setup()
{
  Serial.begin(115200);
  delay(1000); // Give time for Serial Monitor to open

  dht.begin();
  
  pinMode(IR_SENSOR_PIN, INPUT);

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  int wifi_attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_attempts++;
    if (wifi_attempts > 40) { // 20 seconds timeout
      Serial.println("\nFailed to connect to WiFi. Restarting...");
      ESP.restart();
    }
  }
  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(10000L, sendSensor); // Send sensor data every 10 seconds
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED) {
    checkWiFi();
  }
  if (!Blynk.connected()) {
    checkBlynk();
    sendSensor();
  }
//keypad
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    Blynk.virtualWrite(V2, String(key)); // Send key to Blynk Virtual Pin V0
  }

//IR sensor 

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
  timer.run();
}
