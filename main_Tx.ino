
#include <SPI.h>
#include <LoRa.h>
#include "DHT.h"
#define DHTPIN A1     
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int sensorPin = A0; 
int sensorValue;
float moisture_percentage; 
int hum;
float temp;

void setup() {    
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  dht.begin();
  while (!Serial);
  Serial.println("LoRa Sender");
 
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  sensorValue = analogRead(sensorPin);
  moisture_percentage = ( 100 - ( (sensorValue/1023.00) * 100 ) );
  Serial.println("Sending packet: ");
  
  // send packet
  LoRa.beginPacket();
  LoRa.print("Humidity: ");
  LoRa.print(hum);
  LoRa.print("%");
  LoRa.print(" Temperature:");
  LoRa.print(temp);
  LoRa.print("C");
  LoRa.print(" Moisture:");
  LoRa.print(moisture_percentage);                                                                            
  LoRa.print("%");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.print(" Temperature:");
  Serial.print(temp);
  Serial.println("C");
  Serial.println("Moisture Percentage = ");
  Serial.println(moisture_percentage); 

  LoRa.endPacket();
  delay(1000); 
}