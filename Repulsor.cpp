#include "Repulsor.h"
#include "Math.h"

Repulsor::Repulsor(byte indicatorLED, byte flashLED, byte speaker) {
  this->indicatorLED = indicatorLED;
  this->flashLED = flashLED;
  this->speaker = speaker;
  init();
}

void Repulsor::init() {
  // LED digital output pins
  pinMode(indicatorLED, OUTPUT);
  pinMode(flashLED, OUTPUT);
}

void Repulsor::refresh() {
  analogWrite(indicatorLED, energy);
  analogWrite(flashLED, flashValue);

  if (energy > 0) {
    tone(speaker, int(energy) * 20 + 200);
  } else {
    // no energy then mute
    noTone(speaker);
  }
}

//int Repulsor::getEnergy() {
//  if (isCharging) {
//    return 50 * (1 - exp(-float(energy) / 100));
//  } else {
//    return 255 * exp(float(energy - 255) / 10);
//  }
//}

void Repulsor::charge() {
  if (energy < 100) {
    double distance = 100 - energy;
    double speed = (distance / 200) + 0.2;
    energy += speed;
  }

  // update LEDs and speaker
  refresh();
}

void Repulsor::discharge() {
  if (energy > 0) {
    energy -= 1;
  }

  // update LEDs and speaker
  refresh();
}

void Repulsor::repulse() {
  if (energy >= 100) {
    while (flashValue < 255) {
      flashValue += 5;
      energy = flashValue;
      delay(1);
      
      refresh();
    }

    while (flashValue > 0) {
      double speed = (flashValue / 100) + 0.2;
      flashValue -= speed;
      energy = flashValue;
      delay(1);

      refresh();
    }
  }
}
