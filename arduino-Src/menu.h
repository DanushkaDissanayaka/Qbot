#include "keyPad.h"
#include "dispaly.h"

char pressedKey = 'n';

void changeKp(){
     while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 'd' ){
            FULL_SPEED_Kp -= 0.001;
            printValues(FULL_SPEED_Kp);
        }
        if(pressedKey == 's' ){
            fullSpeedLineFollowBlackStrip();
            printValues(FULL_SPEED_Kp);
        }
        if(pressedKey == 'u' ){
            FULL_SPEED_Kp += 0.001;
            printValues(FULL_SPEED_Kp);
        }
    }
    pressedKey = getKey();
}

void changeKd(){
     while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 'd' ){
            FULL_SPEED_Kd -= 0.01;
            printValues(FULL_SPEED_Kd);
        }
        if(pressedKey == 'u' ){
            FULL_SPEED_Kd += 0.01;
            printValues(FULL_SPEED_Kd);
        }
        if(pressedKey == 's' ){
            fullSpeedLineFollowBlackStrip();
            printValues(FULL_SPEED_Kd);
        }
    }
    pressedKey = getKey();
}



void changePID (void){
    pressedKey = getKey();

    while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 's' ){
            displayKp();
            changeKp();
            displayChangePID();
        }

        if(pressedKey == 'd' ){
            displayKd();
            changeKd();
            displayChangePID();
        }
    }
    pressedKey = getKey();
}


void LineFollowMenu(){
    pressedKey = getKey();
    
    while(pressedKey != 'b'){ 
    pressedKey = getKey();
        if(pressedKey != 'n'){

            if(pressedKey == 's' ){
                displayText("Line Fllowing now");
                fullSpeedLineFollowBlackStrip();
                displayLIneFllow();
            }
            if(pressedKey == 'd' ){
                displayChangePID();
                changePID();
                displayLIneFllow();
            }
        }
    }
    
}