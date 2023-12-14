#include <Arduino.h>
#include <LoRa.h>

const int ssPin = 10; // NSS (Chip Select)
const int resetPin = 7; // RST (Reset)
const int dio0Pin = 2; // DIO0 (Interrupt)

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize LoRa module
  LoRa.setPins(ssPin, resetPin, dio0Pin);

  if (!LoRa.begin(433E6)) { // Adjust the frequency to match the transmitter
    Serial.println("LoRa initialization failed. Check your connections.");
    while (1);
  }

  Serial.println("LoRa receiver initialized");

  // Set the LoRa receive callback
  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void loop() {
  // The code in the loop function is intentionally left empty
  // LoRa messages are handled in the onReceive callback
}

void onReceive(int packetSize) {
  if (packetSize == 0) return; // No message received

  // Read the received message
  while (LoRa.available()) {
    String receivedMessage = LoRa.readString();
    Serial.print("Received message: ");
    Serial.println(receivedMessage);
  }

  // Continue listening for the next message
  LoRa.receive();
}
