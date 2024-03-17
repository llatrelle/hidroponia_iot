#include <Wire.h>
#include <RTClib.h>

#include "Arduino.h"
#include "watering.h"

Watering::Watering(byte pinPump, byte pinLedForced){
    this->pinPump = pinPump;
    this->pinLedForced = pinLedForced;
    


}
 
bool Watering::mustContinueWatering() {
  return true;
}

void Watering::setOn(){
  if (!this->isWatering){
    this->isWatering = true;
    digitalWrite(this->pinPump,HIGH);
    digitalWrite(this->pinLedWatchdog,HIGH);
  }

}

void Watering::setOff(){
  if (this->isWatering){
    this->isWatering = false;
    digitalWrite(this->pinPump,LOW);
    digitalWrite(this->pinLedWatchdog,LOW);
  }

}

void Watering::evaluate(DateTime dt){
 

    Serial.print(dt.year(), DEC);
    Serial.print('/');
    Serial.print(dt.month(), DEC);
    Serial.print('/');
    Serial.print(dt.day(), DEC);
    Serial.print(' ');
    Serial.print(dt.hour(), DEC);
    Serial.print(':');
    Serial.print(dt.minute(), DEC);
    Serial.print(':');
    Serial.print(dt.second(), DEC);
    Serial.print(" - HourValue: ");
    Serial.print( this->wateringSettings[dt.hour()]);
    Serial.println();
 


  if (this->isForced){
    return;
  }
  
  int hourPos=dt.hour();
  int mins= dt.minute();
 Serial.print( this->wateringSettings[hourPos]);
    Serial.println();
  if (mins >=00 && mins<15){
   if  ((this->wateringSettings[hourPos] & 1) != 0){
    this->setOn();
    return;
   }
  
  }else if (mins >=15 && mins<30){
     if  ((this->wateringSettings[hourPos] & 2) != 0){
    this->setOn();
    return;
   }
   
  }else if (mins >=30 && mins<45){
     if  ((this->wateringSettings[hourPos] & 4) != 0){
    this->setOn();
    return;
   }
   
  }else if (mins >=45 && mins<60){
    Serial.println(hourPos);
    Serial.println(this->wateringSettings[hourPos]);
    Serial.println(this->wateringSettings[hourPos] & 8);
    if  ((this->wateringSettings[hourPos] & 8) != 0){
    this->setOn();
    return;
   }
  }

  this->setOff();
  return;
  
}

void Watering::setWatering(int settings[24]){
 
}

void Watering::setForcedOn(){
  if(!this->isForced){
    this->isForced=true;
     digitalWrite(this->pinLedForced,HIGH);
    this->setOn();
  }
}

void Watering::setForcedOff(){
  if(this->isForced){
    this->isForced=false;
     digitalWrite(this->pinLedForced,LOW);
    this->setOff();
  }
}