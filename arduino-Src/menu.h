#include "keyPad.h"
#include "dispaly.h"

char pressedKey = 'n';

void changeKp(){
     while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 'd' ){
            FULL_SPEED_Kp += 0.001;
            printValues(FULL_SPEED_Kp);
        }
    }
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
    }
}


void LineFollowMenu(){
    pressedKey = getKey();
    
    while(pressedKey != 'b'){
    pressedKey = getKey();
        if(pressedKey != 'n'){

            if(pressedKey == 's' ){
                displayText("Line Fllowing now");
                fullSpeedLineFollowBlackStrip();
                LineFollowMenu();
            }
            if(pressedKey == 'd' ){
                displayChangePID();
                changePID();
                displayLIneFllow();
                LineFollowMenu();
            }
        }
    }
    
}