#ifndef  distanceSensor_h
    #define distanceSensor_h
    #define MAX_DISTANCE        2000 // In micro second
    #define LEFT_ECHO_PIN       31
    #define LEFT_TRIG_PIN       33

    #define RIGHT_ECHO_PIN      23
    #define RIGHT_TRIG_PIN      25

    #define FRONT_RIGHT_ECHO_PIN      35
    #define FRONT_RIGHT_TRIG_PIN      37

    #define FRONT_LEFT_ECHO_PIN      39
    #define FRONT_LEFT_TRIG_PIN      41

    #define FRONT_ECHO_PIN      27
    #define FRONT_TRIG_PIN      29

    #define LEFT        1
    #define RIGHT       2
    #define FRONT       3
    #define FRONT_RIGHT 4
    #define FRONT_LEFT  5

    void sensorInit(){
        pinMode(LEFT_TRIG_PIN,OUTPUT);
        pinMode(LEFT_ECHO_PIN,INPUT);

        pinMode(RIGHT_TRIG_PIN,OUTPUT);
        pinMode(RIGHT_ECHO_PIN,INPUT);

        pinMode(FRONT_TRIG_PIN,OUTPUT);
        pinMode(FRONT_ECHO_PIN,INPUT);

        pinMode(FRONT_RIGHT_TRIG_PIN,OUTPUT);
        pinMode(FRONT_RIGHT_ECHO_PIN,INPUT);

        pinMode(FRONT_LEFT_TRIG_PIN,OUTPUT);
        pinMode(FRONT_LEFT_ECHO_PIN,INPUT);
    }

    void createPulse(uint8_t pin){
        digitalWrite(pin,LOW);
        delayMicroseconds(2);
        digitalWrite(pin,HIGH);
        delayMicroseconds(10);
        digitalWrite(pin,LOW);
    }

    unsigned int getDistance(uint8_t side){
        
        switch (side)
        {
            case LEFT:
                createPulse(LEFT_TRIG_PIN);
                return pulseIn(LEFT_ECHO_PIN,HIGH,MAX_DISTANCE)/29/2;
                // get Left Distance

            case RIGHT:
                createPulse(RIGHT_TRIG_PIN);
                return pulseIn(RIGHT_ECHO_PIN,HIGH,MAX_DISTANCE)/29/2;
                // get Right Distance
                
            case FRONT:
                createPulse(FRONT_TRIG_PIN);
                return pulseIn(FRONT_ECHO_PIN,HIGH,MAX_DISTANCE)/29/2;
                // get Front Distance

            case FRONT_RIGHT:
                createPulse(FRONT_RIGHT_TRIG_PIN);
                return pulseIn(FRONT_RIGHT_ECHO_PIN,HIGH)/29/2;
                // get FRONT_RIGHT Distance

            case FRONT_LEFT:
                createPulse(FRONT_LEFT_TRIG_PIN);
                return pulseIn(FRONT_LEFT_ECHO_PIN,HIGH)/29/2;
                // get FRONT_Left Distance

            default:
                // do noting
                return -1;
        }
    }

    void testDistanceSensor(){

        Serial.print("Distance "); 
        Serial.print('\t'); Serial.print("LEFT: "); Serial.print(getDistance(LEFT));
        Serial.print('\t'); Serial.print("FRONT: "); Serial.print(getDistance(FRONT));
        Serial.print('\t'); Serial.print("RIGHT: "); Serial.print(getDistance(RIGHT));
        Serial.print('\t'); Serial.print("FRONT RIGHT: "); Serial.print(getDistance(FRONT_RIGHT));
        Serial.print('\t'); Serial.print("FRONT LEFT: "); Serial.print(getDistance(FRONT_LEFT));
        Serial.println();
    }
#endif