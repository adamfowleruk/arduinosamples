
/*
 * Zeta Simple Transmit example
 * 
 * DOES NOT use the optional CODEC chip.
 * Performs same function as PIC example provided by supplier.
 */

#include <SPI.h>
#include <ZetaRaw.h>


//int pinLED = 13; // on board arduino LED pin
int pinInterrupt = 2; // The Arduino board's Interrupt pin. Most boards are Pin 2, some either pin 2 or 3
int pinZetaSPISelect = 7; // Can be any Digital IO pin
int pinZetaCTS = 6; // Can be any Digital IO pin
int pinZetaGpio1 = 6; // Can be any Digital IO pin (same as CTS as it turns out)

ZetaRaw zeta;

void setup() {
  // put your setup code here, to run once:
  //pinMode(pinLED,OUTPUT);
  //digitalWrite(pinLED,HIGH);
  
  Serial.begin(9600);
  Serial.println("In setup()");
  
  zeta.setup(pinInterrupt,pinZetaSPISelect,pinZetaCTS,pinZetaGpio1,true);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(pinLED,LOW);

  delay(100);

  //digitalWrite(pinLED,HIGH);
  sendPacket();
}

void sendPacket() {
  byte data[12] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12};
  zeta.sendPacket(data,0,12); // data array pointer, startPos, length (inclusive)
}

