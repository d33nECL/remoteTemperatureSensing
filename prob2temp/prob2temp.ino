#include <SPI.h>
#include <WiFiNINA.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// WiFi parameters
char ssid[] = "Emerald Lab";
char pass[] = "DNArev0luti0n";
int status = WL_IDLE_STATUS;

// Data wire is connected to pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WiFi: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000); // Wait 5 seconds for connection
  }
  
  // Initialize DS18B20 sensor
  sensors.begin();
}

void loop() {
  // Call sensors.requestTemperatures() to issue a global temperature request to all devices on the bus
  sensors.requestTemperatures();

  // Read temperature in Celsius
  float tempC = sensors.getTempCByIndex(0);

  // Print temperature to serial monitor
  Serial.print("probe2_Temperature: ");
  Serial.println(tempC);

  // Send temperature data over WiFi
  WiFiClient client;
  if (client.connect("10.0.1.251", 80)) {
    client.print("GET /Probe2Temperature/");
    client.print(tempC);
    client.stop();
  }

  delay(5000); // Delay for 5 seconds before next reading
}