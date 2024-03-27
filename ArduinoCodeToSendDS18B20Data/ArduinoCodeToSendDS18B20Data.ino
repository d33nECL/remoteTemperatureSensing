#include <WiFiNINA.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Network credentials
char ssid[] = "Emerald Lab";
char password[] = "DNArev0luti0n";

// Server settings
char server[] = "10.0.0.220"; // IP address of your ESP8266 server
int port = 12345; // Choose a port number

// Data wire is connected to pin 2 on the Arduino
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiClient client;

void setup() {
    Serial.begin(9600);

    // Connect to Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        
        delay(5000); // Adjust delay as needed
    }
    Serial.println("Connected to WiFi!");
    
    // Print IP address obtained from WiFi module
    Serial.print("Arduino IP Address: ");
    Serial.println(WiFi.localIP());

    // Start temperature sensor
    sensors.begin();
}

void loop() {
    // Print the temperature in Celsius
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");

    // Connect to the server and send temperature data
    if (client.connect(server, port)) {
        Serial.println("Connected to server!");

        // Send temperature data to the server
        client.print("Temperature: ");
        client.println(temperatureC); // Send temperature data

        Serial.println("Temperature data sent to server.");

        client.stop(); // Close the connection
    } else {
        Serial.println("Connection to server failed!");
    }

    delay(10000); // Adjust delay as needed before sending the next temperature reading
}
