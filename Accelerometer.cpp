#include "Accelerometer.h"

bool Accelerometer::setup(uint8_t lsbOfAdress, lis3dh_range_t range, lis3dh_dataRate_t dataRate){
  accelerometerObj = Adafruit_LIS3DH();

  //returns false if startup fails
  if(!accelerometerObj.begin(0x18 + lsbOfAdress)) return false;

  accelerometerObj.setRange(range);
  accelerometerObj.setDataRate(dataRate);

  return true;
}

xyz_float Accelerometer::getData(){
  sensors_event_t event;
  accelerometerObj.getEvent(&event);

  xyz_float outputData = {
    event.acceleration.x,
    event.acceleration.y,
    event.acceleration.z
  };

  return outputData;
}

float Accelerometer::getXYAccel(){
  xyz_float accel1data = getData();
	return sqrt(pow(accel1data.x, 2) + pow(accel1data.y, 2));
}

