  #include    <QTRSensors.h>
  #include    "indicators.h"

#ifndef QTRSensor_h
  #define QTRSensor_h
  #define NUM_SENSORS             8  // number of sensors used
  #define NUM_SAMPLES_PER_SENSOR  4
    // average 4 analog samples per sensor reading
  #define EMITTER_PIN             50  // emitter is controlled by digital pin 50

  // sensors 0 through 7 are connected to analog inputs 0 through 7, respectively
  QTRSensorsAnalog qtra((unsigned char[]) {0, 1, 2, 3, 4, 5,6,7}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
  unsigned int sensorValues[NUM_SENSORS];

  void calibrateSensorArray(void){
      beep(1,500);                    // Make beep sound before Start calibrate
      for (int i = 0; i < 250; i++)  // make the calibration take about 10 seconds
    {
      qtra.calibrate();             // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
    }
    beep(1,500);                  // Make beep sound after calibrate
  }

  void printCalibrateValues(void){
      for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtra.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
      Serial.println();
    
    // print the calibration maximum values measured when emitters were on
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtra.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
      Serial.println();
  }

  void testSensorArray(void){

      // read calibrated sensor values and obtain a measure of the line position from 0 to 5000
      // To get raw sensor values, call:
      //  qtra.read(sensorValues); instead of unsigned int position = qtra.readLine(sensorValues);
    unsigned int position = qtra.readLine(sensorValues);
    
    // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
    // 1000 means minimum reflectance, followed by the line position
    for (unsigned char i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(sensorValues[i]);
      Serial.print('\t');
    }
    //Serial.println(); // uncomment this line if you are using raw values
    Serial.println(position); // comment this line out if you are using raw values
    
    delay(250);
  }
#endif