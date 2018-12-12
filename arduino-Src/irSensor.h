#ifndef irSensor__h
    #define irSensor__h
    #define IR_LEFT     0
    #define IR_RIGHT    1

    #define BACK_IR_LEFT     18
    #define BACK_IR_RIGHT    19


   volatile bool leftDetect = false;
   volatile bool rightDetect = false;

    volatile bool backLeftDetect = false;
    volatile bool backRightDetect = false;

       void leftDetect_ISR(void){
        leftDetect = true;
    }

    void rightDetect_ISR(void){
        rightDetect = true;
    }

    void backLeftDetect_ISR(void){
        backLeftDetect = true;
    }

    void backRightDetect_ISR(void){
        backRightDetect = true;
    }

    void irSensorInit(void){
        attachInterrupt(IR_LEFT,leftDetect_ISR,FALLING);
        attachInterrupt(IR_RIGHT,rightDetect_ISR,FALLING);
        attachInterrupt(digitalPinToInterrupt(BACK_IR_LEFT), backLeftDetect_ISR,FALLING);
        attachInterrupt(digitalPinToInterrupt(BACK_IR_RIGHT), backRightDetect_ISR,FALLING);
    }

    void testIrSensor(void){
        if(leftDetect){
            Serial.println("left Detected");
            leftDetect =false;
        }
        if(rightDetect){
            Serial.println("Right Detected");
            rightDetect =false;
        }
         if(backRightDetect){
            Serial.println("Back right Detected");
            backRightDetect =false;
        }
         if(backLeftDetect){
            Serial.println(" Back left Detected");
            backLeftDetect =false;
        }
    }

    void clear_ISR_Verialble(void){
        leftDetect = false;
        rightDetect = false;
    }
    void clear_ISR_Verialble_nearWheel(void){
        backRightDetect = false;
        backLeftDetect = false;
    }
#endif