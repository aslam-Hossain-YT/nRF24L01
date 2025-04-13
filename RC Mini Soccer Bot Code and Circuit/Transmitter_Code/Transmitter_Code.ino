#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// RF24 setup
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

// Joystick pins
const int xPin = A1;
const int yPin = A0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); // Transmitter mode
}

void loop() {
  int xAxis = analogRead(xPin); // 0–1023
  int yAxis = analogRead(yPin); // 0–1023

  // Construct message: "590,620"
  String message = String(xAxis) + "," + String(yAxis);

  // Send data as C-style string
  radio.write(message.c_str(), message.length() + 1);
}
