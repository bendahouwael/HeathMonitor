/********************************************************************/
// First we include the libraries
//#define USE_ARDUINO_INTERRUPTS false
#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "PubSubClient.h" // Connect and publish to the MQTT broker
//#include <PulseSensorPlayground.h>
// Code for the ESP32
#include "WiFi.h" // Enables the ESP32 to connect to the local network (via WiFi)
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 17
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
//PulseSensorPlayground pulseSensor;  // Creates an object
const int PulseWire = 32;
int Threshold = 250;
/********************************************************************/
// WiFi
const char* ssid = "Supcom20";                 // Your personal network SSID
const char* wifi_password = "keepitsecret"; //Your personal network password
// MQTT
const char* mqtt_server = "192.168.4.132";  // IP of the MQTT broker
const char* temperature_topic = "home/patient/temperature";
const char* bpm_topic = "home/patient/bpm";
const char* mqtt_username = "healthmonitorgateway"; // MQTT username
const char* mqtt_password = "healthmonitorgateway"; // MQTT password
const char* clientID = "patient_telemetry"; // MQTT client ID
// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);
// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}
void setup(void)
{
  // start serial port
  Serial.begin(115200);
 /* pulseSensor.analogInput(PulseWire);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  // Start up the library
  pulseSensor.begin();*/
  sensors.begin();
}
void loop(void)
{
  connect_MQTT();
  Serial.setTimeout(2000);
  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);
  //int myBPM = pulseSensor.getBeatsPerMinute();
  int randBPM = random(60,120);
  String ts = "Temp: " + String((float)t) + " C ";
  // PUBLISH to the MQTT Broker (topic = Temperature, defined at the beginning)
  if (client.publish(temperature_topic, String(t).c_str())) {
    Serial.println("Temperature sent!");
    Serial.println(ts);
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("Temperature failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    if (client.publish(temperature_topic, String(t).c_str())) {
      Serial.println("Temperature sent!");
      Serial.println(ts);
    }
  }
  /*if (pulseSensor.sawStartOfBeat()) {
    // PUBLISH to the MQTT Broker (topic = BPM, defined at the beginning)
    if (client.publish(bpm_topic, String(myBPM).c_str())) {
      Serial.println("BPM sent!");
      Serial.println(myBPM);
    }
    // Again, client.publish will return a boolean value depending on whether it succeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("BPM failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(clientID, mqtt_username, mqtt_password);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      if (client.publish(bpm_topic, String(myBPM).c_str())) {
        Serial.println("BPM!");
        Serial.println(myBPM);
      }
    }

  }*/
  if (client.publish(bpm_topic, String(randBPM).c_str())) {
      Serial.println("BPM sent!");
      Serial.println(randBPM);
    }
    // Again, client.publish will return a boolean value depending on whether it succeded or not.
    // If the message failed to send, we will try again, as the connection may have broken.
    else {
      Serial.println("BPM failed to send. Reconnecting to MQTT Broker and trying again");
      client.connect(clientID, mqtt_username, mqtt_password);
      delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
      if (client.publish(bpm_topic, String(randBPM).c_str())) {
        Serial.println("BPM!");
        Serial.println(randBPM);
      }
    }
  client.disconnect();  // disconnect from the MQTT broker
  delay(1000 * 1);     // print new values every 1 Minute

  /*
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus
    /********************************************************************/
  /* Serial.print(" Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperature readings
    Serial.println("DONE");
    /********************************************************************/
  /*Serial.print("Temperature is: ");
    Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?
    // You can have more than one DS18B20 on the same bus.
    // 0 refers to the first IC on the wire
    delay(1000);

}
