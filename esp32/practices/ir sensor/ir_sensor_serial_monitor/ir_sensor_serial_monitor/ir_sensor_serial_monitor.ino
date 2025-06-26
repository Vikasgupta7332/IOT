// Define IR sensor pin (adjust to D2 or D15)
#define IR_SENSOR_PIN 15  // Use 2 for D2, or 15 for D15

void setup() {
  Serial.begin(115200);         // Initialize serial monitor
  pinMode(IR_SENSOR_PIN, INPUT); // Set pin as input
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN); // Read sensor state

  if (sensorState == LOW) {    // LOW = obstacle detected
    Serial.println("Obstacle detected!");
    // Add actions (e.g., trigger motor/alert)
  } else {                      // HIGH = no obstacle
    Serial.println("No obstacle.");
  }
  delay(500); // Stabilize readings
}
