#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN pins
const uint64_t address = 0xE8E8F0F0E1LL;  // Unique address for communication

const int buttonPin = 2;  // Push button pin
bool buttonState = 0; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Internal pull-up resistor
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();  // Transmitter mode
}

void loop() {
  buttonState = digitalRead(buttonPin); // Read button state
  bool ledState = (buttonState == LOW) ? HIGH : LOW;  // Button pressed → LED ON
  
  radio.write(&ledState, sizeof(ledState));  // Send LED state
  delay(100);  // Small delay to stabilize communication
}

