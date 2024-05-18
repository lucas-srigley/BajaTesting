#ifndef HallEffect_h
#define HallEffect_h

#include "Arduino.h"

class HallEffect{
  public:
     HallEffect(byte interruptPin);
     unsigned int getRPM();
     void setup();
     void magnetDetect();
  private:
     const byte pin;
     unsigned int revs;
     unsigned int rpm;
     unsigned long lastTime;
};

#endif
		
	
