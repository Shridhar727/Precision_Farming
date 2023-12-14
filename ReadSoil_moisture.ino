#include <Arduino.h>
#include <driver/adc.h>
#include<esp_log.h>

const int soilMoisturePin = 34;  
const int dryValue = 800;       
const int wetValue = 4095;          

void setup() {
  Serial.begin(115200);  
  pinMode(soilMoisturePin, INPUT);  
}

void loop() {
  int sensorValue = analogRead(soilMoisturePin);  
  int moisturePercentage = map(sensorValue, wetValue, dryValue, 0, 100);

  Serial.print("Sensor Value: "); 
  Serial.print(sensorValue);
  Serial.print(" Moisture Percentage: ");
  Serial.print(moisturePercentage);
  Serial.println("%");


  delay(1000);  
}
