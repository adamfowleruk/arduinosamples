
/*
 * Zeta Simple Receive example
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

char data[ZETARF_PACKET_LENGTH] = "Wotcha World!";

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
  zeta.startListening();
  Serial.println("Started listening for data");
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(100);

  if (zeta.checkReceived()) {
    zeta.readPacket((uint8_t*)data);
    Serial.print("> ");
    Serial.write(data, ZETARF_PACKET_LENGTH);
    Serial.println();
    // Now get the RSSI (Signal Strength)
    int rssi = zeta.readCurrentRSSI();
    Serial.print("RSSI Currently: ");
    Serial.print(rssi,OCT);
    Serial.println();
  } else {
    Serial.println("No data received");
  }
}
