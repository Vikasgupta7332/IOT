#ifndef MQTT_CONFIG_H
#define MQTT_CONFIG_H

#define LED_BUILTIN_PIN 2  // Built-in LED pin for ESP32

// WiFi credentials
#define WIFI_SSID "acts"             // Replace with your WiFi SSID
#define WIFI_PASSWORD ""     // Replace with your WiFi password

// MQTT TOPICS

#define TELEMETRY_TOPIC "cdac/desd/device_01/telemetry" // Publish telemetry data
#define COMMAND_TOPIC "cdac/desd/commands" // Subscribe for command messages

// MQTT broker details
#define MQTT_BROKER "192.168.76.243"         // Replace with your MQTT broker IP address
#define MQTT_PORT 1883                       // MQTT port (default for most brokers)

// MQTT authentication credentials
#define MQTT_CLIENT_ID "ESP32_Client"        // Unique client ID for the MQTT broker
#define MQTT_USERNAME "desd"     // Replace with your MQTT username, if required
#define MQTT_PASSWORD "desd"     // Replace with your MQTT password, if required

// Custom MAC address for the ESP32
//#define CUSTOM_MAC_ADDRESS {0xF4, 0x96, 0x34, 0x9D, 0xE6, 0x2B}  // Replace with your custom MAC address

// Publish interval in milliseconds
#define PUBLISH_INTERVAL 15000              // Telemetry data publish interval (15 seconds)

#endif // MQTT_CONFIG_H
