#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN pins
const uint64_t address = 0xE8E8F0F0E1LL;  // Same address as transmitter

const int ledPin = 3;  // LED pin

void setup() {
  pinMode(ledPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();  // Receiver mode
}

void loop() {
  if (radio.available()) {
    bool receivedState;
    radio.read(&receivedState, sizeof(receivedState));  // Receive data
    digitalWrite(ledPin, receivedState);  // Control LED
  }
}

