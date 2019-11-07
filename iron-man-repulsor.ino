#include <CapacitiveSensor.h>
#include "Repulsor.h"

// input pins
#define CAP_SEND 16
#define CAP_RECEIVE 17
#define POT_PIN A4

// output pins
#define INDICATOR_LED 10
#define FLASH_LED 9
#define SPEAKER 6

// 10M resistor between the two pins
CapacitiveSensor cs(CAP_SEND, CAP_RECEIVE);
Repulsor repulsor(INDICATOR_LED, FLASH_LED, SPEAKER);

void setup() {
  // turn off autocalibrate
//  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);

  // for debug
  Serial.begin(9600);
}

void loop() {
  // read the input on potentialPin
  int potValue = analogRead(POT_PIN);
  long capValue = cs.capacitiveSensor(30);

//  Serial.println(potValue);

  if (potValue > 850) {
    repulsor.charge(); 
  } else {
    repulsor.discharge();
  }

  if (capValue > 1000) {
    repulsor.repulse();
  }

  delay(1); // delay for stability
}
