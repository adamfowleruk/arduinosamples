//
// Distance Sensing and Intruder circuit program
//
// See blog entry for details: http://wp.me/p2KEyC-fn
//
// Uses the Sharp IR distance sensor GP2Y0A21YK and a single Arduino Pro Mini ADC Analog pin
//
// This work is licensed under The Unlicense.
//

int distanceSensorPin = A3;

int distanceReadingsLimit = 200;

float initialReading = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  initialReading = getReading(distanceSensorPin);

  Serial.println("Distance sensor activated");

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  float distanceReading = getReading(distanceSensorPin);

  Serial.print("Distance value: ");
  Serial.println(distanceReading);

  // now for a crude intruder alarm!
  if ((distanceReading < (0.95 * initialReading)) || (distanceReading > (1.05 * initialReading))) {
    Serial.println("BUZZ!!! Intruder spotted!");
  }

  delay(50);
}

float getReading(int pin) {
  float distanceReading = 0;
  for (int distanceReadingsCount = 0;distanceReadingsCount < distanceReadingsLimit;distanceReadingsCount++) {
    distanceReading += analogRead(pin);
  }
  distanceReading = distanceReading / distanceReadingsLimit;
  return distanceReading;
}

