//
// Soil Sensor advanced sample
//
// Licensed under The Unlicense.
//
// Tested on an Arduino Pro Mini 3.3V
//
// Described here: http://wp.me/p2KEyC-fg
// 

int thresholdUp = 510; // narrow window for testing - you WILL have to change these two values
int thresholdDown = 502;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:

int sensorPin = A0;
int sensorOnPin = 13; // Using pin 13 so we get the light on the Arduino Pro Mini when sensing
int pumpPin = 11;

int pumpDurationLimit = 5;
int pumpPauseLimit = 5;
int indivReadingLimit = 10; // ten readings each second, and averaged
int groupReadingLimit = 5; // sixty seconds apart

int sensorValue = 0;
int groupReadingCount = 0;
bool pumpOn = false;
int pumpDuration = 0;
int pumpPauseCount = 0;

void setup() {
  Serial.begin(9600);
  
  //pinMode(A0, INPUT); DEFAULT
  pinMode(A1, OUTPUT);
  pinMode(sensorOnPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(sensorOnPin,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(pumpPin,LOW);

  Serial.println("Water monitor activated");
  
  delay(1000);
  
}

void loop() {

  // 1. POWER ON BOTH PROBE PINS (D10 and A1)
  digitalWrite(A1,HIGH);
  digitalWrite(13,HIGH);
  delay(100);

  // 2. READ PIN INFO
  
  // Read multiple times to get an accurate reading

  int newSensorValue = 0;
  for (int i = 0;i < indivReadingLimit;i++) {
    newSensorValue += analogRead(sensorPin);
  }
  sensorValue += newSensorValue / indivReadingLimit;

  // 3. POWER OFF PROBE PINS
  digitalWrite(A1,LOW);
  digitalWrite(13,LOW);

  groupReadingCount++;

  if (groupReadingCount == groupReadingLimit) {
    groupReadingCount = 0;

    sensorValue /= groupReadingLimit;

    // 4. OUTPUT DATA
    Serial.write("Water Level: ");
    Serial.println(sensorValue);

    // Check water level

    if (sensorValue <= thresholdDown) {
      Serial.println("Dry, watering");

      if (pumpOn) {
        pumpDuration += 1;
        if (pumpDuration >= pumpDurationLimit) {
          Serial.println("Pump duration exceeded - Pump pin turned off");
          digitalWrite(pumpPin,LOW); // reached time limit
          pumpPauseCount++;
          if (pumpPauseCount > pumpPauseLimit) {
            pumpPauseCount = 0;
            pumpDuration = 0; // effectively it's still dry, so turn it back on
          }
        } else {
          Serial.println("Pump pin turned on");
          digitalWrite(pumpPin,HIGH);
          pumpPauseCount = 0;
        }
      } else {
        pumpOn = true;
      }
    
    } else if (sensorValue >= thresholdUp) {
      Serial.println("Wet, not watering");
    } else {

      Serial.println("In between, waiting for environment to change");
      pumpOn = false;
      pumpDuration = 0;
      digitalWrite(pumpPin,LOW);
      //Serial.println("(Pump pin turned off)");
    }

    sensorValue = 0;

  } // end if check

  // 5. SLEEP
  
  delay(1000); 

}
