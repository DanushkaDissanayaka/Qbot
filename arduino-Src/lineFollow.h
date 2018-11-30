#include "QTRSensor.h"
#include "motor.h"

#define LINE_FLLOW_DEBUG    false

// Full speed PID Values
float thisvalue = 0.075;
double FULL_SPEED_Kp =  0.074;
double FULL_SPEED_Kd =  0;
#define FULL_SPEED_Ki   0

// Half Speed PID values
#define HALF_SPEED_Kp 0
#define HALF_SPEED_Kd 0
#define HALF_SPEED_Ki 0

#define LINE_POSITION   3500
#define MIN_VALUE       200
#define MAX_VALUE       600
//uint16_t    leftMotorSpeed  = 0;
//uint16_t    rightMotorSpeed = 0;

int             error       = 0;
int             I           = 0;
int             lastError   = 0;
int             motorSpeed  = 0;
unsigned int    position    = 0;

void calPid (float Kp , float Kd , float Ki){
    position = qtra.readLine(sensorValues);
    error = position - LINE_POSITION;
    I = I + error;
    motorSpeed = (Kp * error) + (Kd * (error - lastError)) + I*Ki;
    lastError = error;
}

void fullSpeedLineFollowBlackStrip(void){
    
    while(1){

        calPid(FULL_SPEED_Kp,FULL_SPEED_Kd,FULL_SPEED_Ki); // calculate pid For left and right motors

        if(sensorValues[0] < MIN_VALUE &&sensorValues[1] < MIN_VALUE && sensorValues[2] < MIN_VALUE && sensorValues[3] < MIN_VALUE && sensorValues[4] < MIN_VALUE && sensorValues[5] < MIN_VALUE && sensorValues[6] < MIN_VALUE && sensorValues[7] < MIN_VALUE){
                break; // lost our line
            }
        if(sensorValues[0] > MAX_VALUE &&sensorValues[1] > MAX_VALUE && sensorValues[2] > MAX_VALUE && sensorValues[3] > MAX_VALUE && sensorValues[4] > MAX_VALUE && sensorValues[5] > MAX_VALUE && sensorValues[6] > MAX_VALUE && sensorValues[7] > MAX_VALUE){
                break; // found our solution
            }
        rightMotorSpeed = FULL_BASE_SPEED_RIGHT - motorSpeed;
        leftMotorSpeed =  FULL_BASE_SPEED_LEFT  + motorSpeed;

        if (rightMotorSpeed > FULL_MOTOR_SPEED_RIGHT )  rightMotorSpeed = FULL_MOTOR_SPEED_RIGHT; // prevent the motor from going beyond max speed
        if (leftMotorSpeed >  FULL_MOTOR_SPEED_LEFT )   leftMotorSpeed  = FULL_MOTOR_SPEED_LEFT; // prevent the motor from going beyond max speed
        if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
        if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive   

        if (LINE_FLLOW_DEBUG) {
            Serial.print(position);
            Serial.print("\t");
            Serial.print(error);
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
    Stop(); // stop both motors after line Follow
}
