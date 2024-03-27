#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Network credentials
const char* ssid = "Emerald Lab";
const char* password = "DNArev0luti0n";

// Server settings
WiFiServer server(12345); // Choose a port number

float lastTemperature = 0.0; // Variable to store the last received temperature

void setup() {
    Serial.begin(9600);
    delay(100);

    // Connect to Wi-Fi
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    
    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the IP address of the server
    Serial.print("Server IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Check if a client has connected
    WiFiClient client = server.available();
    if (client) {
        // Wait until the client sends some data
        Serial.println("New client connected");
        String request = client.readStringUntil('\n'); // Read the client request
        Serial.println(request);
        // Check if the request contains temperature data from Arduino
        if (request.startsWith("Temperature: ")) {
            // Extract the temperature value from the request
            float temperature = request.substring(13).toFloat();
            // Update the last temperature variable
            lastTemperature = temperature;
            // Display the temperature value in Serial Monitor
            Serial.print("Last Temperature: ");
            Serial.println(lastTemperature);
        }

        // Respond to the client with the last temperature value
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.print("Last Temperature: ");
        client.print(lastTemperature);
        client.println(" °C");

        // Close the connection to allow multiple clients
        client.stop();
    }
}
