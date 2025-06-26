#include <DHT.h>

#define DHTPIN 4      // GPIO pin connected to DHT11 data
#define DHTTYPE DHT11 // DHT sensor type

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
  Serial.begin(115200);
  dht.begin(); // Start sensor
}

void loop() {
  delay(2000); // Minimum 1s delay between measurements
  
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  // Validate readings
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print formatted output
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\tTemperature: ");
  Serial.print(tempC);
  Serial.print("°C (");
  Serial.print(tempF);
  Serial.println("°F)");
}
