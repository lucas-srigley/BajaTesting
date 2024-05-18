#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Adafruit_LIS3DH.h>
#include <SD.h>
#include <SPI.h>
#include "Accelerometer.h"
#include "suspension_tracker.h"
#include "HallEffect.h"
#include "load_cell.h"
#include "HX711.h"

#define calibration_factor -7050.0
#define DT 38
#define SCK 37

#define MAXSET A9
#define MINSET A4

Accelerometer accel1;
suspension_tracker* rotEncode;
HallEffect* hall;
HX711 scale;

char* dataToSD;
char* accelData;
char** rotPos;
char** rpm;
const int chipSelect = BUILTIN_SDCARD;

void setup(){
  Serial.begin(9600);
  accel1.setup();
  scale.begin(DT, SCK);
  scale.set_scale(calibration_factor); 
  scale.tare();

  rotEncode = (suspension_tracker*)malloc(4 * sizeof(suspension_tracker));
  hall = (HallEffect*)malloc(1 * sizeof(HallEffect));

  // SD
  dataToSD = (char*)malloc(32 * 6 * sizeof(char));
  if (!SD.begin(chipSelect)){
    Serial.println("SD card initialization failed.");
    return;
  }
  Serial.println("SD card initialized successfully.");

  accelData = (char*)malloc(32 * sizeof(char));

  rotPos = (char**)malloc(4 * sizeof(char*));
  for(int i = 0; i < 4; i++){
      rotPos[i] = (char*)malloc(32 * sizeof(char));
  }

  rpm = (char**)malloc(32 * sizeof(char*));
  for(int i = 0; i < 1; i++){
    rpm[i] = (char*)malloc(32 * sizeof(char));
  }

  String str = "Time (\u03BCs)\tAcceleration (m/s\u00B2)\tWheel RPM\tPressure (kg)\tRotary 1 Angle (\u00B0)\tRotary 2 Angle (\u00B0)\tRotary 3 Angle (\u00B0)\tRotary 4 Angle (\u00B0)\n";
  Serial.print(str);
}

void centerAlignPrint(String text, int columnWidth) {
  int padding = max(0, columnWidth - text.length());
  int leftPadding = padding / 2;
  int rightPadding = padding - leftPadding;
  
  for (int i = 0; i < leftPadding; i++) {
    Serial.print(' ');
  }
  
  Serial.print(text);
  
  for (int i = 0; i < rightPadding; i++) {
    Serial.print(' ');
  }
}

void loop() {
  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile){
      // test in serial monitor
      centerAlignPrint(String(micros()), 10);
      Serial.print("\t");
      centerAlignPrint(String(accel1.getXYAccel(), 2), 20);
      Serial.print("\t");
      centerAlignPrint(String(hall->getRPM()), 10);
      Serial.print("\t");
      centerAlignPrint(String(scale.get_units(), 1), 10);
      for(int i = 0; i < 4; i++){
        int analogValue = analogRead(rotEncode[i].getPin()); 
        double currentAngle = rotEncode[i].getAnalogToAngle(analogValue);
        double currentPosition = rotEncode[i].getAngleToPosition(currentAngle);
        centerAlignPrint(String(currentPosition, 2), 24);
      }

      // print to file
      // dataFile.print(micros());
      // dataFile.print("\t");
      // dataFile.print(accel1.getXYAccel());
      // dataFile.print("\t");
      // dataFile.print(hall[1].getRPM());
      // dataFile.print("\t");
      // dataFile.print(scale.get_units(), 1);
      // for (int i = 0; i < 4; i++) {
      //   int analogValue = analogRead(rotEncode[i].getPin());
      //   double currentAngle = rotEncode[i].getAnalogToAngle(analogValue);
      //   double currentPosition = rotEncode[i].getAngleToPosition(currentAngle);
      //   dataFile.print("\t");
      //   dataFile.print(currentPosition);
      // }
      Serial.println();
      dataFile.println();
      dataFile.close();
  }
  delay(100);
}
