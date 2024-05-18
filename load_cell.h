//Lucas Srigley (20LSS6)

#include "HX711.h"
#ifndef LOAD_CELL_H
#define LOAD_CELL_H

#include "Arduino.h"

class LoadCell {
public:
    LoadCell(int pin);
    void setup();
    void readAndPrintForce();

private:
    int loadCellPin;
};

#endif