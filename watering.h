#ifndef Watering_h
#define Watering_h
#include "Arduino.h"
#include <RTClib.h>


class Watering{
private:
  /* Pins */
  byte pinPump;
  byte pinLedWatchdog;
  byte pinLedForced;
  
  bool isWatering= false;
  bool isForced= false;
  bool serialPrint = false;
  int wateringSettings[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,8,3};
  bool mustContinueWatering();
  void setOn();
  void setOff();
public:
    Watering(byte pinPump, byte pinLedForced);
    void evaluate(DateTime);
    void setWatering(int settings[24]);
    void setForcedOn();
    void setForcedOff();
};
#endif