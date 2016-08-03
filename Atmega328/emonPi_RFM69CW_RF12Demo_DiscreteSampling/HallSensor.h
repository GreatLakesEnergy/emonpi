/*
 *  Header file to Hall Sensor class
 * 
 *  
 */

#ifndef HALL_SENSOR_LIB

#define HALL_SENSOR_LIB

#include "Arduino.h"

class HallSensor {
  public:
    // - - - Function
    float VREF = 3.3;
    float VOFFSET = 0.0;
    
    bool DEBUGGING = 0;
    bool INVERTED = 0;
    
    void Initialise( float in_VREF, float in_VOFFSET, bool in_INVERTED );
    void Set( int in_Readings, int  in_readingDelay, int in_SampleSize, int in_readingSeparation );
    
    float get_current( );
    float get_reading( );
    
    float get_volt(float adc);
    float get_adc(float v);
    
    int Readings = 3;
    int readingSeparation = 1;     //
    int readingDelay = 100;      //
    int SampleSize = 200;
    
    
    unsigned long time_for_reading;
    float CurrentReading = 0;
  
  private:
    
    void serialprint(String msg, float var);
    
    void serialline(String msg, float var);
    
    
};    // Eo HallSensor

#endif


// Eo File
