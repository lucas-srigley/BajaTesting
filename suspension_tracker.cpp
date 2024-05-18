#include "core_pins.h"
#include "suspension_tracker.h"
#include <Arduino.h>

suspension_tracker::suspension_tracker(int pin, double maximumAngle, int averagePositionAmount, int averageVelocityAmount, int averageAccelerationAmount){
  pinMode(pin, INPUT);
  currentPositionValueIndex = 0;

  this->pin = pin;
  this->maximumAngle = maximumAngle;
  this->averagePositionAmount = averagePositionAmount;
  this->averageVelocityAmount = averageVelocityAmount;
  this->averageAccelerationAmount = averageAccelerationAmount;

}

double suspension_tracker::getAngleFromAnalog(int analogValue) {
  return map(analogValue, 0, analogMax, 0, maximumAngle);
}

double suspension_tracker::getPositionFromAngle(double angle){
  return angle;
}

double suspension_tracker::getAveragePosition(){
  double total_position = 0;
  for(int i = 0; i<averagePositionAmount; i++){
    if (lastTenPositionValues[(i+currentPositionValueIndex)%10][0] == -1) return -1;
    total_position += lastTenPositionValues[(i+currentPositionValueIndex)%10][0];
  }
  return total_position / averagePositionAmount;
}

void suspension_tracker::update(){
  int analogInput = analogRead(pin);
  double currentAngle = getAngleFromAnalog(analogInput);
  position = getPositionFromAngle(currentAngle);

  lastTenPositionValues[currentPositionValueIndex][0] = position;
  lastTenPositionValues[currentPositionValueIndex][1] = millis();

  averagePosition = getAveragePosition();
  currentPositionValueIndex = (currentPositionValueIndex+1) % 10;

}