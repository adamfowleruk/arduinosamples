
/*
 * Zeta Simple Receive example
 * 
 * DOES NOT use the optional CODEC chip.
 * Performs same function as PIC example provided by supplier.
 */

#include <SPI.h>
#include <ZetaRaw.h>


//int pinLED = 13; // on board arduino LED pin
int pinZetaSleep = 9;
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
  
  zeta.setup(pinZetaSleep,pinInterrupt,pinZetaSPISelect,pinZetaCTS,pinZetaGpio1,true);
  zeta.changeStateRx();
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(pinLED,LOW);

  delay(100);

  //digitalWrite(pinLED,HIGH);
  if (zeta.hasData()) {
    Serial.print("Received data: ");
    zeta.writeDataToSerial();
  }
}
