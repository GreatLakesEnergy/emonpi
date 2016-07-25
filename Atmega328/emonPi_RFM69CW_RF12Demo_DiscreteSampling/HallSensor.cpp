

#include "Arduino.h"
#include "HallSensor.h"

/*  Important Class Variable
 *   
 *   
 *   ---- VREF 
 *    precise Voltage of ADC EXTERNAL voltage reference 
 *    
 *    Around 3.3V
 *    
 *  ---- Readings
 *    No of readings to be made
 *    Default : 3
 *    
 *  ---- reading Delay
 *    Delay in between readings in [ms]
 *    default 100
 * 
 *  ---- Sample Size
 *    Number of samples to be taken from one ADC for one reading
 *    
 *  ---- Reading Separation
 *    Delay in between Readings
 *    
 */

void HallSensor::Initialise( float in_VREF ){
  
  analogReference(DEFAULT);   // EXTERNAL
   
  VREF = in_VREF;   //3.283;
    
  Readings = 3;   
  readingDelay = 100;
  
  SampleSize =  200;
  readingSeparation = 1;

  CurrentReading = 0;
  
}   // Eo Initialise


void HallSensor::Set( int in_Readings, int  in_readingDelay, int in_SampleSize, int in_readingSeparation ){
  
  //analogReference(EXTERNAL);
  
  // VREF = in_VREF;                                 // 3.283;
    
  Readings = in_Readings;                      //3;   
  readingDelay = in_readingDelay;             // 100;
  
  SampleSize = in_SampleSize;                 //  200;
  readingSeparation = in_readingSeparation;            // 1;

  CurrentReading = 0;

  /*if( DEBUGGING){
    serialprint("Readings  ", Readings);
    serialprint("\treading Delay  ", readingDelay);

    serialprint("\tSample size  ", SampleSize);
    serialprint("\treading separation del  ", readingSeparation);
  }*/
  
}   // Eo Initialise


/* ----------- Measure current 
 *  Takes several (_Reading) readings from ADC,
 *  each of _SampleSize values
 *  each with a delay of _readingSeparation in between
 *  Reading returns average over _SampleSize values
 *  
 *  Each reading followed by a delay of _readingDelay ms
 *  
 */
float HallSensor::get_current( int PIN, float offset_adjust ) 
{
  float readings[5];
  float result = 0;
  
  // Take X  Readings
  for( int i=0; i< Readings; i++)
  {
    result += get_reading( PIN);
    // Alternatively put value into array to find Mean or middle value
    //readings[i] = get_reading( PIN);
    //result += readings[i]
    
    delay(readingDelay);
  }

  result /= Readings;
  
  CurrentReading = result +offset_adjust;

  return CurrentReading;
  
  //last_reading = millis();
  
}   // Eo get_current


// tkaes SampleSize, Separate (delay between readings)
// returns:   average over all adc values
//
float HallSensor::get_reading( int PIN )
{
  int sensor;
  int sample_no = 0;
  float average = 0;
  float voltage, current;
  
  reading_begin = millis();
  
  while(sample_no < SampleSize)
  {
      switch(PIN){
        case 0:
          sensor = analogRead(A0);
          break;
        case 1:
          sensor = analogRead(A1);
          break;
        case 2:
          sensor = analogRead(A2);
          break;
        case 3:
          sensor = analogRead(A3);
          break;
        case 4:
          sensor = analogRead(A4);
          break;
        case 5:
          sensor = analogRead(A5);
          break;
        default:
          sensor = analogRead(A0);
          break;
      }

      average += sensor;
      
      sample_no++;
      
      delay(readingSeparation);
  } // Eo while loop

  
  time_for_reading = reading_begin - millis();
  
  average /= SampleSize;
  voltage = get_volt(average);
  
  /*  -------------  Current to voltage curves for curent sensor -------------
   *  
   *  Equ for G 0, Z 0,     =  (168.05 * v1 ) -400.22;
   *  Equ for G 1, Z 1      = (140.74 * v2 ) -365.82;
   *  
   *  where
   *  0 is turned all the way clockwise
   *  1 is turned all the way anti-clockwise
   *  
   */
  
  current = ( 140.74 * voltage ) -365.82;

  // ======================= DEBUG O P 
  if(DEBUGGING){
    
    Serial.println("======================= DEBUG ");
    Serial.println("time\tavrg adc\t> volt\t >>curr");
    Serial.println( time_for_reading);
    Serial.println(average);
    Serial.println(voltage);
    Serial.println(current);
    
  } 
  
  return current;
} // Eo get_reading


float HallSensor::get_volt(float adc){
  return ( ( adc * VREF ) / 1023 );     }


float HallSensor::get_adc(float v){
  return ( ( v * 1023) / VREF );        }




