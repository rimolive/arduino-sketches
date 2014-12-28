#include "Ultrasonic.h"

Ultrasonic ultrasonic(12,13);

void setup() {
  Serial.begin(9600
  Serial.print("testing...");
}

void loop() {
  Serial.print(ultrasonic.Ranging(CM));
  Serial.print("cm");
  Serial.print("\n);
  delay(100);
}
