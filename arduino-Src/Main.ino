#include "distanceSensor.h"
#include "indicators.h" // no need to include allradey in QTRSensor.h
#include "motor.h" // no need to include allradey in lineFollow.h
#include "QTRSensor.h" // no need to include allradey in lineFollow.h
#include "lineFollow.h"
#include "wallFollow.h"
#include "keyPad.h"
#include "dispaly.h"
#include "menu.h"
#include "irSensor.h"

void setup() {
    sensorInit();
    indicatorsInit();
    Serial.begin(115200);
    keypadInit();
    dispalyInit();
    displayMainMenu();
    irSensorInit();
    //calibrateSensorArray();
    //delay(5000);
}

void loop() {
    //testparts();
    withMenu();
}

void doTask(){

    fullSpeedLineFollowBlackStrip();
    delay(100);
    Stop();
    fullSpeedLineFollowWhiteStrip();
    fullSpeedLineFollowWhiteStrip();
    Stop();
    speedControl(255,255);
    turnLeft();
    delay(150);
    Stop();
    fullSpeedLineFollowWhiteStrip();
}

void testparts(void){
    /*testIndicators();
    testDistanceSensor();
    testMotors();
    testSensorArray();
    fullSpeedLineFollowBlackStrip();
    fullSpeedRightWallFollow();
    displayTest();*/
    testIrSensor();
}

void withMenu(void){
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

        if(key == 'b' ){
            displayText("Task");
            doTask();
            displayMainMenu();
        }

        if(key == 'd' ){
            displayText("Wall Fllowing");
            fullSpeedRightWallFollow();
            displayMainMenu();
        }
 }
}