#ifndef indicators_h
    #define indicators_h
    #define GREEN_LED_PIN   37
    #define BLUE_LED_PIN    39
    #define RED_LED_PIN     41
    #define BUZZER_PIN      35

    #define BLUE    1
    #define GREEN   2
    #define RED     3

    #define ON 1
    #define OFF 0

    void indicatorsInit(){
        pinMode(GREEN_LED_PIN,OUTPUT);
        pinMode(BLUE_LED_PIN,OUTPUT);
        pinMode(RED_LED_PIN,OUTPUT);
        pinMode(BUZZER_PIN,OUTPUT);
    }

    void ledOnOff(uint8_t led , bool state){
        switch (led)
        {
            case BLUE:
                
                if (state) {
                    digitalWrite(BLUE_LED_PIN ,HIGH);
                }
                else {
                    digitalWrite(BLUE_LED_PIN ,LOW);
                }
                break;

            case GREEN:
                
                if (state) {
                    digitalWrite(GREEN_LED_PIN ,HIGH);
                }
                else {
                    digitalWrite(GREEN_LED_PIN ,LOW);
                }
                break;

            case RED:
                
                if (state) {
                    digitalWrite(RED_LED_PIN ,HIGH);
                }
                else {
                    digitalWrite(RED_LED_PIN ,LOW);
                }
                break;

            default:
            // do nothing
                break;
        }
        
    }

    void beep (uint8_t number , uint16_t duration){
        
        for(uint8_t i = 0; i < number; i++)
        {
            digitalWrite(BUZZER_PIN ,HIGH);
            delay(duration);
            digitalWrite(BUZZER_PIN ,LOW);
            delay(duration);
        }
        
    }

    void testIndicators (){
    ledOnOff(BLUE,ON);
    delay(1000);
    ledOnOff(BLUE,OFF);
    delay(1000);

    ledOnOff(GREEN,ON);
    delay(1000);
    ledOnOff(GREEN,OFF);
    delay(1000);

    ledOnOff(RED,ON);
    delay(1000);
    ledOnOff(RED,OFF);
    delay(1000);

    beep(2,1000);
    }
#endif