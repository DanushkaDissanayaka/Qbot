#include "lineFollow.h"
//#include "wallFollow.h"
#include "indicators.h"
#include "irSensor.h"
#include "motor.h"
#include "QTRSensor.h"

#ifndef mazeSolve_h
    #define mazeSolve_h
    #define FORWARD_TIME        200
    #define MAZE_SOLVE_DEBUG    false
    #define LEFT_TURN           1
    #define RIGHT_TURN          2
    #define GO_STRIGHT          3
    #define BACK_TURN           4

    bool straightDetect = false;
    unsigned char dir;

    char select_turn(unsigned char found_left, unsigned char found_straight, unsigned char found_right)
    {
        // Make a decision about how to turn.  The following code
        // implements a left-hand-on-the-wall strategy, where we always
        // turn as far to the left as possible.
        if(found_left)
            return 'L';
        else if(found_straight)
            return 'S';
        else if(found_right)
            return 'R';
        else
            return 'B';
    } // end select_turn


    void turn(char dir)
    {
        switch(dir) {
            // Turn left 90deg
            case 'L':    
            BlackLinetTurnLeft();
            break;
            // Turn right 90deg
            case 'R':
            BlackLineTurnRight();
            break;
            // Turn right 180deg to go back
            case 'B':
            BlackLinetTurnLeft();
            break;
            // Straight ahead
            case 'S':
            // do nothing
            break;
        }
    }// end turn

    void solveMaze(void){

        while(1){

            fullSpeedLineFollowBlackStrip();
            //freeforward(FORWARD_TIME);
            delay(2000);

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

                dir = select_turn(leftDetect,straightDetect,rightDetect);
                //Select turn according to sensor readingd
                // check there is a dedend and we have wall to fllow
                if(dir == 'B' &&  getDistance(LEFT) != 0 && getDistance(RIGHT) != 0){
                    fullSpeedWallFollow();
                    // freeforward(1000);
                    // fullSpeedWallFollow();
                    break;
                }
                // Make the turn indicated by the path.
                turn(dir);
            } 
        }
    }

    /*uint8_t getTurn(uint8_t foundLeft, uint8_t foundRight, uint8_t foundStraight){
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
        
        if (turn == LEFT_TURN) {
            BlackLineTurnRight();
        }
        else if (turn == RIGHT_TURN )
        
    }*/

#endif