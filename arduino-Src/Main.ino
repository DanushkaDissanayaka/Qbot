#include "distanceSensor.h"
#include "indicators.h" // no need to include allradey in QTRSensor.h
#include "motor.h" // no need to include allradey in lineFollow.h
#include "QTRSensor.h" // no need to include allradey in lineFollow.h
#include "lineFollow.h"
#include "wallFollow.h"
#include "keyPad.h"
#include "dispaly.h"
#include "menu.h"

void setup() {
    sensorInit();
    indicatorsInit();
    Serial.begin(115200);
    keypadInit();
    dispalyInit();
    displayMainMenu();
    //calibrateSensorArray();
    //delay(5000);
}

void loop() {
  //testIndicators();
  //testDistanceSensor();
 //testMotors();
 //testSensorArray();
 //fullSpeedLineFollowBlackStrip();
 //fullSpeedRightWallFollow();
 //displayTest();

 /*while(1){
    //do nothing...
 }*/
 char key = getKey();

 if(key != 'n'){
     if(key == 's' ){
         displayLIneFllow();
         LineFollowMenu();
         displayMainMenu();
     }

        if(key == 'u' ){
            displayText("Tuning");
            calibrateSensorArray();
            displayMainMenu();
        }
 }
 
}