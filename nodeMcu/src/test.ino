#include "Arduino.h"

#define LED_PIN    2

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_PIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_PIN, LOW);

   // wait for a second
  delay(1000);
}
