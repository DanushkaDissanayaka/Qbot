#ifndef keyPad_h
    #define keyPad_h
    #define GROUND_PIN  50
    #define START       48
    #define DOWN        46
    #define UP          44
    #define BACK        42
    #define KEY_PRESS_DELAY 250

    void keypadInit(){
        pinMode(GROUND_PIN , OUTPUT);
        digitalWrite(GROUND_PIN , LOW);

        pinMode(START , INPUT_PULLUP);
        pinMode(DOWN , INPUT_PULLUP);
        pinMode(UP , INPUT_PULLUP);
        pinMode(BACK , INPUT_PULLUP);
    }

    char getKey(){
        
        if (!digitalRead(START) || !digitalRead(DOWN) || !digitalRead(UP) || !digitalRead(BACK) ) {
                if(!digitalRead(START)){
                delay(KEY_PRESS_DELAY);
                return 's';
            }
            else if(!digitalRead(DOWN)){
                delay(KEY_PRESS_DELAY);
                return 'd';
            }
            else if(!digitalRead(UP)){
                delay(KEY_PRESS_DELAY);
                return 'u';
            }
            else if(!digitalRead(BACK)){
                delay(500);
                return 'b';
            }
        }
        return 'n';
    }

    void testKeypad(void){
        char key = getKey();
        if(key != 'n'){
        Serial.println(key);
        }
    }
#endif