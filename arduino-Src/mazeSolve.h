#include "lineFollow.h"
#include "indicators.h"
#include "irSensor.h"
#include "motor.h"
#include "QTRSensor.h"

#ifndef mazeSolve_h
    #define mazeSolve_h
    #define FORWARD_TIME        100
    #define MAZE_SOLVE_DEBUG    true
    #define LEFT_TURN           1
    #define RIGHT_TURN          2
    #define GO_STRIGHT          3
    #define BACK_TURN           4

    bool straightDetect = false;

    void solveMaze(void){

        while(1){

            fullSpeedLineFollowBlackStrip();
            freeforward(FORWARD_TIME);

            qtra.readLine(sensorValues); // before check condition read sensor values
            if(sensorValues[0] > MAX_VALUE &&sensorValues[1] > MAX_VALUE && sensorValues[2] > MAX_VALUE && sensorValues[3] > MAX_VALUE && sensorValues[4] > MAX_VALUE && sensorValues[5] > MAX_VALUE && sensorValues[6] > MAX_VALUE && sensorValues[7] > MAX_VALUE){
            break; // found our solution
            }

            if(MAZE_SOLVE_DEBUG){
                delay(1000);
                if(leftDetect){
                    beep(1,100); // detected left junction
                }

                delay(1000);
                if(rightDetect){
                    beep(2,100); // detected right junction
                }

                delay(1000);

                qtra.readLine(sensorValues); // before check stright line read sensor values
                if(sensorValues[0] > MAX_VALUE || sensorValues[1] > MAX_VALUE || sensorValues[2] > MAX_VALUE || sensorValues[3] > MAX_VALUE || sensorValues[4] > MAX_VALUE || sensorValues[5] > MAX_VALUE || sensorValues[6] > MAX_VALUE || sensorValues[7] > MAX_VALUE){
                    beep(3,100); // found a stright line
                }

                delay(1000);
            }
            else{

                straightDetect = false; // clear preveus detecttion
                qtra.readLine(sensorValues); // before check stright line read sensor values
                if(sensorValues[0] > MAX_VALUE || sensorValues[1] > MAX_VALUE || sensorValues[2] > MAX_VALUE || sensorValues[3] > MAX_VALUE || sensorValues[4] > MAX_VALUE || sensorValues[5] > MAX_VALUE || sensorValues[6] > MAX_VALUE || sensorValues[7] > MAX_VALUE){
                    straightDetect = true;
                }
                // make turn according to sensor detections
            } 
        }
    }

    uint8_t getTurn(uint8_t foundLeft, uint8_t foundRight, uint8_t foundStraight){
        if(foundLeft)
            return LEFT_TURN;

        else if(foundStraight)
            return GO_STRIGHT;

        else if (foundRight)
            return RIGHT_TURN;

        else
            return BACK_TURN;
    }
    void makeTurn(uint8_t turn){
        
        if (turn) {
            
        }
        
    }
#endif