/*
 * GET THE MAC Address of ESP32
 * GET it Registered with ACTS AP
 *
 * This code demonstrates how to correctly retrieve the ESP32's MAC address.
 * The WiFi module needs to be initialized before its MAC address can be read.
 */

#include <WiFi.h> // Include the WiFi library for ESP32 functionality

void setup() {
  // Initialize serial communication for debugging output
  Serial.begin(115200);
  Serial.println(); // Print a newline for cleaner output
  // Setting the mode to STATION (WIFI_STA).
  WiFi.mode(WIFI_STA);
  // --- IMPORTANT FIX END ---

  Serial.print("Initializing WiFi...");
  WiFi.begin("dummy_ssid", "dummy_password"); // Replace with actual credentials if connecting to a real AP
  
  // Give the WiFi module a moment to initialize.
  // In some cases, a small delay helps the MAC address become available.
  delay(100); // Wait for 100 milliseconds
  Serial.println(" Done.");

  // Now, after WiFi initialization, the MAC address should be available
  Serial.print("ESP Board MAC Address: ");
  Serial.println(WiFi.macAddress()); // Print the retrieved MAC address
}

void loop() {
  // This loop remains empty as the task is only to get and print the MAC address once.
  // Any ongoing tasks would go here.
}
