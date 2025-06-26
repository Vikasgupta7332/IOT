/*
 * GET THE MAC Address of ESP32
 * GET it Registered with ACTS AP
 *
 * This code demonstrates how to correctly retrieve the ESP32's factory-assigned MAC address,
 * connect to a specified Wi-Fi network, and control the built-in LED
 * based on the Wi-Fi connection status.
 */

#include <WiFi.h> // Include the WiFi library for ESP32 functionality

// Define your Wi-Fi credentials here
const char* ssid = "acts";         // REPLACE WITH YOUR WIFI NETWORK NAME
const char* password = ""; // REPLACE WITH YOUR WIFI PASSWORD

// Define the pin for the built-in LED
// Common ESP32 boards have the built-in LED on GPIO2 (NodeMCU, ESP32-DevKitC)
// Some boards might have it on GPIO16, or not at all. Check your board's pinout.
#define LED_BUILTIN 2 

void setup() {
  // Initialize serial communication for debugging output
  Serial.begin(115200);
  Serial.println(); // Print a newline for cleaner output

  // Set the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);
  // Turn off the LED initially
  digitalWrite(LED_BUILTIN, LOW); 

  // --- WiFi Connection and MAC Address Retrieval ---
  // Set the WiFi mode to Station. This is crucial for initializing the WiFi hardware.
  // This step brings up the necessary components to get the MAC address.
  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to WiFi network: ");
  Serial.println(ssid);

  // Attempt to connect to the Wi-Fi network.
  // Calling WiFi.begin() is vital as it fully initializes the Wi-Fi module
  // and makes its factory-assigned MAC address available.
  WiFi.begin(ssid, password);

  // Wait for connection to be established, with a timeout
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Try for about 10 seconds (20 * 500ms)
    delay(500); // Wait for 500 milliseconds before retrying
    Serial.print("."); // Print a dot to show progress
    attempts++;
  }
  Serial.println(); // Newline after connection attempts

  // Now that WiFi.begin() has been called and the module is active,
  // WiFi.macAddress() should return the board's unique, factory-assigned MAC address.
  Serial.print("ESP Board System MAC Address: ");
  Serial.println(WiFi.macAddress()); 

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // Turn on the LED if connected to WiFi
    digitalWrite(LED_BUILTIN, HIGH); 
  } else {
    Serial.println("Failed to connect to WiFi.");
    Serial.println("Please check your SSID and password.");
    // If connection fails, the LED remains off.
  }
}

void loop() {
  // The loop remains mostly empty for this example,
  // as the primary actions (MAC address retrieval, WiFi connection, LED on/off based on connection)
  // are handled in the setup.
  // In a real application, you might continuously check WiFi status here
  // or perform other tasks.
}
