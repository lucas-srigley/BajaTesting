//Lucas Srigley (20LSS6)

#include "HX711.h"
#include "load_cell.h"
#include "Arduino.h"

LoadCell::LoadCell(int pin) {
    loadCellPin = pin;
}

void LoadCell::setup() {
    pinMode(loadCellPin, INPUT);
}

void LoadCell::readAndPrintForce() {
    int loadCellInput = analogRead(loadCellPin);
    float force = (loadCellInput / 1023.0);
    Serial.print("Load Cell Pressure: "); 
    Serial.print(force, 2);
    Serial.println(" kg");
}