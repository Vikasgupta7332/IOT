/*
 * 
 * This is sample code written for CDAC students of ACTS Batch to work with MQTT protocol
 * Install Library PubSubClient by Nick O'Leary
 * How to Install -> Go to Sketch -> Include Library -> Manage Libraries -> Filter your search -> PubSubClient
 * https://www.arduino.cc/reference/en/libraries/pubsubclient/
 * 
 */
#include <WiFi.h>
#include <PubSubClient.h>  
//#include <esp_wifi.h>  
#include <ArduinoJson.h>

// Set the custom MAC address in case your ESP32 is not regsitered with the acts network - wifi spoofing
uint8_t newMACAddress[] = {0xc8, 0xb2, 0x9b, 0x70, 0x8a, 0xeb};  // a8:6d:aa:0e:61:f9

DynamicJsonDocument sensor_data_payload(1024);

char sensor_data_format_for_mqtt_publish[1024];

const char* ssid =   "acts";                          //ssid - service set Identifier (Replace it with your ssid name)

const char* password =  "";                     // replace with ssid paasword

const char* mqttBroker = "demo.thingsboard.io";                  // broker address - replace it with your broker address/cloud broker - test.mosquitto.org

const int   mqttPort = 1883;                            // broker port number

const char* clientID = "iotnode-01";                   // client-id --> replace it in case willing to connect with same broker
 
//const char* mqtt_topic_for_publish = "cdac/room/data"; // topic names
const char* mqtt_topic_for_publish = "v1/devices/me/telemetry";

WiFiClient MQTTclient;

PubSubClient client(MQTTclient);

long lastReconnectAttempt = 0;
boolean reconnect()
{
  //boolean connect (clientID, [username, password], [willTopic, willQoS, willRetain, willMessage], [cleanSession])
   if (client.connect(clientID),"WGzpEYcZm9BAunwYM95J","") {

    Serial.println("Attempting to connect broker");
    
  }
  return client.connected();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Attempting to connect...");
  WiFi.mode(WIFI_STA);      
  //esp_wifi_set_mac(WIFI_IF_STA, &newMACAddress[0]); // for wifi spoofing
  WiFi.begin(ssid, password); // Connect to WiFi.
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Couldn't connect to WiFi.");
  }
  Serial.print("ESP32 IP ADDRESS : ");
  Serial.println(WiFi.localIP());
  //Add details for MQTT Broker
  client.setServer(mqttBroker, mqttPort); // Connect to broker
  lastReconnectAttempt = 0;
}
void loop() {
  if (!client.connected())
  {
    long now = millis();  // Returns the number of milliseconds passed since the Arduino board began running the current program
    if (now - lastReconnectAttempt > 5000) { // Try to reconnect.
      lastReconnectAttempt = now;
      if (reconnect())
      { 
        lastReconnectAttempt = 0;
      }
    }
  }
  else 
  { 
    Serial.println("Connected to Broker --- !!");
    client.loop();
    
    float h = random(0,100);
    float t = random(-16,56);

    sensor_data_payload["temperature"] = t;
    sensor_data_payload["humidity"]   = h;

    serializeJson(sensor_data_payload, sensor_data_format_for_mqtt_publish);
    
    delay(2000);
    Serial.println(h);
    Serial.println(t);   
    client.publish(mqtt_topic_for_publish,sensor_data_format_for_mqtt_publish);  //(topicname, payload)
    Serial.println("sensor data sent to broker");
    delay(5000);
  }
}
