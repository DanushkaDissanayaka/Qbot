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
            FULL_SPEED_Kd -= 0.1;
            printValues(FULL_SPEED_Kd);
        }
        if(pressedKey == 'u' ){
            FULL_SPEED_Kd += 0.1;
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


void changeWallKp(){
     while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 'd' ){
            WALL_FULL_SPEED_Kp -= 0.001;
            printValues(WALL_FULL_SPEED_Kp);
        }
        if(pressedKey == 's' ){
            fullSpeedWallFollow();
            printValues(WALL_FULL_SPEED_Kp);
        }
        if(pressedKey == 'u' ){
            WALL_FULL_SPEED_Kp += 0.001;
            printValues(WALL_FULL_SPEED_Kp);
        }
    }
    pressedKey = getKey();
}

void changeWallKd(){
     while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 'd' ){
            WALL_FULL_SPEED_Kd -= 0.10;
            printValues(WALL_FULL_SPEED_Kd);
        }
        if(pressedKey == 'u' ){
            WALL_FULL_SPEED_Kd += 0.10;
            printValues(WALL_FULL_SPEED_Kd);
        }
        if(pressedKey == 's' ){
            fullSpeedWallFollow();
            printValues(WALL_FULL_SPEED_Kd);
        }
    }
    pressedKey = getKey();
}



void changeWallPID (void){
    pressedKey = getKey();

    while (pressedKey != 'b'){
        pressedKey = getKey();
        if(pressedKey == 's' ){
            displayWallKp();
            changeWallKp();
            displayChangePID();
        }

        if(pressedKey == 'd' ){
            displayWallKd();
            changeWallKd();
            displayChangePID();
        }
    }
    pressedKey = getKey();
}




void WallFollowMenu(){
    pressedKey = getKey();
    
    while(pressedKey != 'b'){ 
    pressedKey = getKey();
        if(pressedKey != 'n'){

            if(pressedKey == 's' ){
                displayText("Wall Fllowing now");
                fullSpeedWallFollow();
                displayWallFllow();
            }
            if(pressedKey == 'd' ){
                displayChangePID();
                changeWallPID();
                displayWallFllow();
            }
        }
    }
    
}