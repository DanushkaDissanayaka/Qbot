#include "motor.h"
#include "distanceSensor.h"
#include "indicators.h"

#define WALL_FLLOW_DEBUG    false

// Full speed PID Values
double WALL_FULL_SPEED_Kp = 3.7;
double WALL_FULL_SPEED_Kd = 0;
#define WALL_FULL_SPEED_Ki 0

// Half Speed PID values
#define WALL_HALF_SPEED_Kp 0
#define WALL_HALF_SPEED_Kd 0
#define WALL_HALF_SPEED_Ki 0

#define WALL_POSITION       650
#define FRONT_MIN_DISTANCE  200

unsigned int frontDistance  = 0;
unsigned int leftDistance   = 0;
unsigned int rightDistance  = 0;

int             wallError       = 0;
int             wallI           = 0;
int             walLastError    = 0;
int             WallMotorSpeed  = 0;

void calPidWall (float Kp , float Kd , float Ki , unsigned int    position){
    wallError = position;
    wallI = wallI + wallError;
    WallMotorSpeed = (Kp * wallError) + (Kd * (wallError - walLastError)) + wallI*Ki;
    walLastError = wallError;
}

void fullSpeedWallFollow(void){
    
    while(1){

        frontDistance = getDistance(FRONT);
        leftDistance  = getDistance(LEFT);
        rightDistance = getDistance(RIGHT);

        calPidWall(WALL_FULL_SPEED_Kp,WALL_FULL_SPEED_Kd,WALL_FULL_SPEED_Ki,rightDistance-leftDistance); // calculate pid For left and right motors
        rightMotorSpeed = WALL_BASE_SPEED_RIGHT + WallMotorSpeed;
        leftMotorSpeed =  WALL_BASE_SPEED_LEFT  - WallMotorSpeed;

        if (rightMotorSpeed > WALL_MOTOR_SPEED_RIGHT )  rightMotorSpeed = WALL_MOTOR_SPEED_RIGHT; // prevent the motor from going beyond max speed
        if (leftMotorSpeed >  WALL_MOTOR_SPEED_LEFT )   leftMotorSpeed  = WALL_MOTOR_SPEED_LEFT; // prevent the motor from going beyond max speed
        if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
        if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive   
        

        if (rightDistance == 0 && leftDistance == 0) { 
            break; // We have found a junction or dedend
        }
        
        if(2 < frontDistance && frontDistance < FRONT_MIN_DISTANCE ){
           //beep(2,100);
           break; // found a junction
        }
        
        else
        {
            if (WALL_FLLOW_DEBUG) {
                Serial.print(rightDistance - leftDistance);
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
    speedControl(255,255);
        backward();
        delay(BACKWORD_STOP_DELAY);
        Stop(); // stop both motors after wall Follow
    beep(2,250);
}

void checkWallDedend(void) {
    freeforward(200);
    FreeRotateLeft(150);
    freeforward(200);
    // now check there have ay wall
    if(getDistance(LEFT) != 0 || getDistance(RIGHT) != 0){
        //we have found 4way junction
        //  allso we have take our turn
        beep(100,1);
    }
    else{
        // wehave found dedend
        //GO back
        FreeRotateLeft(300);
        freeforward(200);
        FreeRotateRight(150);
    }
}
    
void WallFollowing() {
    normalSpeed();
    while(1){

    frontDistance = getDistance(FRONT);
    leftDistance  = getDistance(LEFT);
    rightDistance = getDistance(RIGHT);

  if (frontDistance < 4 && frontDistance != 0) {
    Stop();
    delay(1000);
    if(leftDistance < 4){
      turnRight();
    }
    else{
     turnLeft(); 
    }
    delay(200);
    Stop();
  } else {
    if (leftDistance > 10 && leftDistance < 20 ) {
      turnLeft();
      delay(30);
      forward();
      delay(30);
    } else if (leftDistance < 5 && leftDistance > 0) {
      turnRight();
      delay(30);
      forward();
      delay(30);
    } else if (leftDistance > 20 || leftDistance == 0) {
      forward();
      delay(50);
      turnLeft();
      delay(30);
      forward();
      delay(30);
    } else {
      forward();
    }
  }

  delay(20);
    }
}
