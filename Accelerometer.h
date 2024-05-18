/*
This Library is used to communicate with an Adafruit LIS3DH Accelerometer using I2C

This library is designed to ease the flow of the main DAQ software and uses a pre-existing library Adafruit Library
It will ensure that all default paramaters are set correctly
As the needs of the team do not require functions beyond setup and read, those will be the only 2 available

This Library will utilise Adafruit's Unified Driver Library so hopefully any supported adafruit accelerometer would work with some tweaking in the setup/constructer function

If Paramaters need to be changed it is reccomend to change them in the definitions here unless needed for debugging purposes

This library also includes a custom struct to store xyz float values in a single object

Created October 2023
Contact:
21tap8@queensu.ca
tpriftakis@gmail.com
*/

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <math.h>


#define DEFAULT_ADRESS_LSB 0
#define DEFAULT_RANGE LIS3DH_RANGE_8_G
#define DEFAULT_REFRESH_RATE LIS3DH_DATARATE_100_HZ

//This will the return type of the read function
struct xyz_float{
  float x;
  float y;
  float z;
};

class Accelerometer{
  public:
    /* Setup, call in setup function
    PARAMS:
      uint8_t lsbOfAdress (optional)  Will take LSB of adress, as defined by the LIS3DH datasheet
      lis3dh_range_t range (optional) Range of data setting max and min
      lis3dh_dataRate_t dataRate (optional) Data refresh rate of device
    */
    bool setup(
      uint8_t lsbOfAdress=DEFAULT_ADRESS_LSB, 
      lis3dh_range_t range=DEFAULT_RANGE, 
      lis3dh_dataRate_t dataRate=DEFAULT_REFRESH_RATE
    );

    xyz_float getData();
    float getXYAccel();

  private:
    Adafruit_LIS3DH accelerometerObj;
};


#endif