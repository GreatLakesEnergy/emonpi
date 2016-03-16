// emonPi used 16 x 2 I2C LCD display 

/*
void emonPi_LCD_Startup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();                 // Or lcd.noBacklight() 
  lcd.print("emonPi V"); lcd.print(firmware_version*0.1);
  lcd.setCursor(0, 1); lcd.print("OpenEnergyMon");
} 
*/
void serial_print_startup(){
  //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//  lcd.clear(); 

  Serial.print("CT 1 Cal: "); Serial.println(Ical1);
  Serial.print("CT 2 Cal: "); Serial.println(Ical2);
  Serial.print("CT 3 Cal: "); Serial.println(Ical3);
  Serial.print("CT 4 Cal: "); Serial.println(Ical4);
  delay(1000);
  Serial.print("VRMS AC ~");
  Serial.print(vrms); Serial.println("V");

  if (ACAC) 
  {
    for (int i=0; i<10; i++)                                              // indicate AC has been detected by flashing LED 10 times
    { 
      digitalWrite(LEDpin, HIGH); delay(200);
      digitalWrite(LEDpin, LOW); delay(300);
    }
//    lcd.print("AC Wave Detected");
    Serial.println("AC Wave Detected - Real Power calc enabled");
    if (USA==TRUE) Serial.print("USA mode active "); 
    Serial.print("Vcal: "); Serial.println(Vcal);
    Serial.print("Vrms: "); Serial.print(Vrms); Serial.println("V");
    Serial.print("Phase Shift: "); Serial.println(phase_shift);
  }
  else 
  {
     delay(1000);
    digitalWrite(LEDpin, HIGH); delay(2000); digitalWrite(LEDpin, LOW);   // indicate DC power has been detected by turing LED on then off
  
//   lcd.print("AC NOT Detected");
   Serial.println("AC NOT detected - Apparent Power calc enabled");
   if (USA==TRUE) Serial.println("USA mode"); 
   Serial.print("Assuming VRMS: "); Serial.print(Vrms); Serial.println("V");
   Serial.println("Assuming power from batt / 5V USB - power save enabled");
 }  

//lcd.setCursor(0, 1); lcd.print("Detected ");

  if (CT_count==0) {
    Serial.println("no CT detected");
//    lcd.print("No CT's");
  }
   else   
   {
    
     if (CT1) {
      Serial.println("CT 1 detect");
//      lcd.print("CT1 ");
    }
     if (CT2) {
      Serial.println("CT 2 detect");
//      lcd.print("CT2");
    }
     if (CT3) {
      Serial.println("CT 3 detect");
//      lcd.print("CT3");
    }
     if (CT4) {
      Serial.println("CT 4 detect");
//      lcd.print("CT4");
    }
   }
  
  delay(2000);

  if (DS18B20_STATUS==1) {
    Serial.print("Detect "); 
    Serial.print(numSensors); 
    Serial.println(" DS18B20");
//    lcd.clear();
//    lcd.print("Detected: "); lcd.print(numSensors); 
//    lcd.setCursor(0, 1); lcd.print("DS18B20 Temp"); 
  }
  else {
  	Serial.println("0 DS18B20 detected");
//  	lcd.clear();
//  	lcd.print("Detected: "); lcd.print(numSensors); 
//    lcd.setCursor(0, 1); lcd.print("DS18B20 Temp"); 
  }

  if (RF_STATUS == 1){
    #if (RF69_COMPAT)
      Serial.println("RFM69CW Init: ");
    #else
      Serial.println("RFM12B Init: ");
    #endif

    Serial.print("Node "); Serial.print(nodeID); 
    Serial.print(" Freq "); 
    if (RF_freq == RF12_433MHZ) Serial.print("433Mhz");
    if (RF_freq == RF12_868MHZ) Serial.print("868Mhz");
    if (RF_freq == RF12_915MHZ) Serial.print("915Mhz"); 
    Serial.print(" Network "); Serial.println(networkGroup);

    Serial.print("CT1 CT2 CT3 CT4 VRMS/BATT PULSE");
    if (DS18B20_STATUS==1){Serial.print(" Temperature 1-"); Serial.print(numSensors);}
    Serial.println(" "); 
    delay(500); 

    showString(helpText1);
  }
  delay(20);  
}


void send_emonpi_serial()  //Send emonPi data to Pi serial /dev/ttyAMA0 using struct JeeLabs RF12 packet structure 
{
  byte binarray[sizeof(emonPi)];
  memcpy(binarray, &emonPi, sizeof(emonPi));
  
  Serial.print("OK ");
  Serial.print(nodeID);
  for (byte i = 0; i < sizeof(binarray); i++) {
    Serial.print(' ');
    Serial.print(binarray[i]);
    //Serial.print("hey");
  }
  Serial.print(" (-0)");
  Serial.println();
  
  delay(10);
}

static void showString (PGM_P s) {
  for (;;) {
    char c = pgm_read_byte(s++);
    if (c == 0)
      break;
    if (c == '\n')
      Serial.print('\r');
    Serial.print(c);
  }
}
