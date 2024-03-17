#include "watering.h"
#include <RTClib.h>

 const int PIN_WATERING_PUMP = 13;   //Pin rele bomba
 const int PIN_WATERING_WATCHDOG = 2; //Pin led bomba
 const int PIN_WATERING_FORCED = 3; //Pin led Bomba manual
 const int PIN_WATERING_BUTTON_FORCED = 4; //Pin boton inicio bomba forzado
 const int PIN_WATERING_BUTTON_STOP_FORCED = 5; //Pin boton stop bomba forzado
 
 RTC_Millis rtc;     //Reloj por software
 //RTC_DS3231 rtc;   //Reloj con DS3231;

Watering watering(PIN_WATERING_PUMP, PIN_WATERING_FORCED);
//int riegoSettings[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,1};
// 0 - off
// 1 - 0 /15 min
// 2 - 15/30 min
// 4 - 30/45 min
// 8 - 45/60 min

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  pinMode(PIN_WATERING_PUMP, OUTPUT);
  pinMode(PIN_WATERING_WATCHDOG, OUTPUT);
  pinMode(PIN_WATERING_FORCED, OUTPUT);
  pinMode(PIN_WATERING_BUTTON_FORCED, INPUT);
  pinMode(PIN_WATERING_BUTTON_STOP_FORCED, INPUT);

  //watering.setWatering(riegoSettings);
  
  
}

void loop() {
 // Evaluate if its time to watering (start/stop)
 Serial.println("- ");
 watering.evaluate( rtc.now());

//Read buttons for start/stop manual watering
if (digitalRead(PIN_WATERING_BUTTON_FORCED)== HIGH){
  watering.setForcedOn();
}
if (digitalRead(PIN_WATERING_BUTTON_STOP_FORCED) == HIGH){
  watering.setForcedOff();
}


delay(1000);  // wait

                    


}
