#include <Arduino.h>
#include <LoRa.h>
#include<WiFi.h>


const int soilMoisturePin = 34;
const int wetValue = 800;     // Update according to actual sensor readings
const int dryValue = 4000;  // Update according to actual sensor readings

SPIClass spi = SPIClass(HSPI);

void setup() {
  Serial.begin(115200);

  spi.begin(5, 23, 18);  // MISO, MOSI, SCK (adjust according to your connections)
  LoRa.setPins(5, 14, 18); // NSS, RST, SCK (adjust according to your connections)

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }

  Serial.println("LoRa transmitter initialized");

  pinMode(soilMoisturePin, INPUT);
}

void loop() {
  int sensorValue = analogRead(soilMoisturePin);
  int moisturePercentage = map(sensorValue, wetValue, dryValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100); // Constrain values to 0-100

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" Moisture Percentage: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  char message[20]; // Increase buffer size according to the message length
  snprintf(message, sizeof(message), "Soil Moisture: %d%%", moisturePercentage);

  // Print the message before sending it
  Serial.print("Sending Message: ");
  Serial.println(message);

  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  delay(1000);  // Adjust the delay according to your needs
}
