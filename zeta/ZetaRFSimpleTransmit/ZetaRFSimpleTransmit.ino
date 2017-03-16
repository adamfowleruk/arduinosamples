
/*
 * Zeta Simple Transmit example
 * 
 * DOES NOT use the optional CODEC chip. Uses the Zeta directly via the Arduino ZetaRF library
 *  - You can get this library from: https://github.com/GIPdA/ZetaRF
 * Performs same function as PIC example provided by supplier.
 */

#include <SPI.h> // REQUIRED in latest Arduino IDE to prevent compilation errors due to 'missing' SPI.h file
//#define VARIABLE_LENGTH_ON // Somewhat buggy
#define FREQ_433 1
#include <ZetaRF.h>

#define ZETARF_PACKET_LENGTH 16

int pinZetaSleep = 6;
int pinInterrupt = 8; // NOT The Arduino board's Interrupt pin - we don't use hardware interrupts for this
int pinZetaSPISelect = 10; // Can be any Digital IO pin


ZetaRF zeta(pinZetaSPISelect,pinZetaSleep,pinInterrupt);

void setup() {
  // put your setup code here, to run once:

  pinMode(pinInterrupt,INPUT); // Interrupt is an input PIN from zeta to tell us it has data
  pinMode(pinZetaSleep,OUTPUT); // Sleep pin for Zeta
  pinMode(pinZetaSPISelect,OUTPUT); // Ensure that the Arduino is SPI MASTER not Slave
  digitalWrite(pinZetaSleep,LOW); // LOW means that Zeta is turned ON
  digitalWrite(pinZetaSPISelect,LOW); // LOW means we've not sent a command to the Zeta chip yet
  
  Serial.begin(9600);
  Serial.println("In setup()");
  
  bool success = zeta.begin(2,ZETARF_PACKET_LENGTH);
  if (success) {
    Serial.println("Initialised successfully");
  } else {
    Serial.println("Failed to initialise");
  }
  Serial.println("Begin has been called");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  
  sendPacket();
}

void sendPacket() {
  Serial.println("Entering sendPacket()");
  //uint8_t data[12] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12};
  //uint8_t data[8] = {1,2,3,4,5,6,7,8};
  char data[ZETARF_PACKET_LENGTH] = "1234567890ABCDE"; // 16th character is \0 in C strings
  zeta.sendPacket((const uint8_t*)data); // actually send the data (size set in setup() call to zeta.begin())
  delay(10);
  if (zeta.checkTransmitted()) {
    Serial.println("Transmitted");
  } else {
    Serial.println("Not transmitted");
  }
  Serial.println("Leave sendPacket()");
}

