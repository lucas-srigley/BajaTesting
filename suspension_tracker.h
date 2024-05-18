#ifndef SUSPENSION_TRACKER_H
#define SUSPENSION_TRACKER_H

#define ANALOG_MAX 913

class suspension_tracker {
    double lastTenPositionValues[10][2] = {{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0},{-1,0}};
    int currentPositionValueIndex; //Used for index Cyclying
    double getAngleFromAnalog(int AnalogValue);
    double getPositionFromAngle(double angle);
    double getAveragePosition();
    double getAverageVelocity();
    double getAverageAcceleration();

    int pin;
    double maximumAngle; 
    int averagePositionAmount;
    int averageVelocityAmount;
    int averageAccelerationAmount;

    int analogMax = ANALOG_MAX;


  public:
    void update();
    suspension_tracker(int pin, double maximumAngle = 90, int averagePositionAmount = 5, int averageVelocityAmount = 5, int averageAccelerationAmount = 5);
    double averagePosition;
    double averageVelocity;
    double averageAcceleration;
    double position;
      
    int getPin() {
      return pin;
    }

    double getAnalogToAngle(int analogValue) {
      return getAngleFromAnalog(analogValue);
    }

    double getAngleToPosition(double angle) {
      return getPositionFromAngle(angle);
    }
};

#endif 