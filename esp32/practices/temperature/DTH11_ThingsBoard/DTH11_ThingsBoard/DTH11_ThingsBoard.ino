#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ------------------ USER SETTINGS ------------------
#define WIFI_SSID     "POCO X4 Pro 5G"
#define WIFI_PASSWORD "Vikas1234"
#define TOKEN         "YOUR_DEVICE_ACCESS_TOKEN" // From ThingsBoard
#define DHTPIN        4                          // GPIO for DHT11 data
#define DHTTYPE       DHT11

// Use IP address of demo.thingsboard.io for reliability
IPAddress mqttServerIP(52, 28, 118, 176); // Update if IP changes
// ---------------------------------------------------

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Waiting...");
    delay(1000);
  }
  // Attempt to connect to MQTT broker
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), TOKEN, NULL)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqttServerIP, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  String payload = "{\"temperature\":";
  payload += t;
  payload += ",\"humidity\":";
  payload += h;
  payload += "}";

  Serial.print("Sending payload: ");
  Serial.println(payload);

  client.publish("v1/devices/me/telemetry", payload.c_str());

  delay(5000); // Send every 5 seconds
}
