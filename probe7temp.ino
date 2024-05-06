#include <OneWire.h>
#include <WiFiNINA.h>

#define MAX31850_PIN 7 // Change this to the pin you've connected to DQ

const char *ssid = "Emerald Lab";
const char *password = "DNArev0luti0n";
char server[] = "10.0.1.166"; // Change this to your server's IP address
int port = 80; // Change this to the port your server is listening on

OneWire oneWire(MAX31850_PIN);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // Attempt to connect to WiFi network
  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("Attempting to connect to WiFi...");
    delay(1000);
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  if (client.connect(server, port)) {
    Serial.println("Connected to server");

    byte data[9];
    int temp; // Change float to int

    oneWire.reset();
    oneWire.write(0xCC); // Skip ROM command
    oneWire.write(0x44); // Convert T command

    delay(750); // Wait for conversion to complete

    oneWire.reset();
    oneWire.write(0xCC); // Skip ROM command
    oneWire.write(0xBE); // Read Scratchpad command

    for (int i = 0; i < 9; i++) {
      data[i] = oneWire.read();
    }

    // Extract temperature data from scratchpad
    int16_t raw = (data[1] << 8) | data[0];
    temp = float(raw) / 16.0; // Convert temp to integer without rounding

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");

    // Send temperature data to server
    client.println("T_R7," + String(temp));
    client.println();
    
    delay(5000); // Wait before sending the next reading
  } else {
    Serial.println("Unable to connect to server");
  }
}
