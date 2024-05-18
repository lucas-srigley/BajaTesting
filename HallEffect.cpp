#include "Arduino.h"
#include "HallEffect.h"

HallEffect::HallEffect(byte interruptPin) : pin(interruptPin) {
  //interruptPin = 24;
	revs = 0;
	rpm = 0;
  lastTime = 0;
}

void HallEffect::magnetDetect() {
	revs++;
}

unsigned int HallEffect::getRPM() {
  unsigned long currentTime = micros();
  unsigned long timeSinceLastDetection = currentTime - lastTime;
  
  if (timeSinceLastDetection > 0) {
    rpm = (revs * 60000000) / timeSinceLastDetection;
  }

  lastTime = currentTime;
  revs = 0;
  
  return rpm;
}

HallEffect* hallEffectInstance; 

void staticMagnetDetect() {
    hallEffectInstance->magnetDetect();
}

void HallEffect::setup(){
  hallEffectInstance = this;
  pinMode(24, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pin), staticMagnetDetect, RISING);
	lastTime = micros();
}
