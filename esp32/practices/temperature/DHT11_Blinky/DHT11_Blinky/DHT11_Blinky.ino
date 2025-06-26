#define BLYNK_TEMPLATE_ID "TMPL3jUEjQ-lL"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "GG1x0wlMxamn6Jn-bVgruRxQ15j5oWgV"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "acts";      // Your WiFi SSID
char pass[] = "";         // Your WiFi password
//char ssid[] = "POCO X4 Pro 5G";      // Your WiFi SSID
//char pass[] = "Vikas1234";         // Your WiFi password

#define DHTPIN 4           // DHT11 data pin connected to GPIO4
#define DHTTYPE DHT11      // DHT 11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

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
  Blynk.run();
  timer.run();
}
