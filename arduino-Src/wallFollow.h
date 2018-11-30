#include "motor.h"
#include "distanceSensor.h"
#include "indicators.h"

#define WALL_FLLOW_DEBUG    false

// Full speed PID Values
#define WALL_FULL_SPEED_Kp 4
#define WALL_FULL_SPEED_Kd 150
#define WALL_FULL_SPEED_Ki 0

// Half Speed PID values
#define WALL_HALF_SPEED_Kp 0
#define WALL_HALF_SPEED_Kd 0
#define WALL_HALF_SPEED_Ki 0

#define WALL_POSITION       650
#define FRONT_MIN_DISTANCE  650

unsigned int frontDistance  = 0;
unsigned int leftDistance   = 0;
unsigned int rightDistance  = 0;

int             wallError       = 0;
int             wallI           = 0;
int             walLastError    = 0;
int             WallMotorSpeed  = 0;

void calPidWall (float Kp , float Kd , float Ki , unsigned int    position){
    wallError = position - WALL_POSITION;
    wallI = wallI + wallError;
    WallMotorSpeed = (Kp * wallError) + (Kd * (wallError - walLastError)) + wallI*Ki;
    walLastError = wallError;
}

void fullSpeedRightWallFollow(void){
    
    while(1){

        frontDistance = getDistance(FRONT);
        //leftDistance  = getDistance(LEFT); // We dont need get left distance since we are fllowing right wall
        rightDistance = getDistance(RIGHT);

        calPidWall(WALL_FULL_SPEED_Kp,WALL_FULL_SPEED_Kd,WALL_FULL_SPEED_Ki,rightDistance); // calculate pid For left and right motors
        rightMotorSpeed = FULL_BASE_SPEED_RIGHT + WallMotorSpeed;
        leftMotorSpeed =  FULL_BASE_SPEED_LEFT  - WallMotorSpeed;

        if (rightMotorSpeed > FULL_MOTOR_SPEED_RIGHT )  rightMotorSpeed = FULL_MOTOR_SPEED_RIGHT; // prevent the motor from going beyond max speed
        if (leftMotorSpeed >  FULL_MOTOR_SPEED_LEFT )   leftMotorSpeed  = FULL_MOTOR_SPEED_LEFT; // prevent the motor from going beyond max speed
        if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
        if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive   

        
        if (frontDistance == 0 && rightDistance == 0) { // check if there is availabe for anay wall if not break the loop
            break;
        }
        
        if(2 < frontDistance && frontDistance < FRONT_MIN_DISTANCE ){
            speedControl(160,160);
            turnRight();
            delay(200);
            Stop();
            delay(5000);
        }

        else
        {
            if (WALL_FLLOW_DEBUG) {
                Serial.print(rightDistance);
                Serial.print("\t");
                Serial.print(wallError);
                Serial.print("\t");
                Serial.print(leftMotorSpeed);
                Serial.print("\t");
                Serial.print(rightMotorSpeed);
                Serial.print("\t");
                Serial.println();
            }
            else {
                forward();
                speedControl(leftMotorSpeed,rightMotorSpeed); // change motor speed according PID values
            }
        }
    }
    backward();
    Stop(); // stop both motors after wall Follow
    beep(2,250);
}
