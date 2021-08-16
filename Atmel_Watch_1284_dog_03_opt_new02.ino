//To compile and load this code onto your watch, select "Mighty 1284 8Mhz" from
//the Boards menu. 

// 03_opt_new This firmware uses the mega1284, internal 8Mhz clock with external I2C RTC and DOG lcd with u8g library 
// in Designed Watch Configuration with updated graphics and cleaner code. It is ver 03 optimized for low current
// Uses the Watchdog timer instead of timer 2 for periodic timing

#include <avr/sleep.h> //Needed for sleep_mode
#include <avr/power.h> //Needed for powering down perihperals such as the ADC/TWI and Timers
#include <Wire.h>
#include <SPI.h>
#include "U8glib.h"
#include <Time.h>
#include <MCP79412RTC.h>
#include <SFE_BMP180.h>
#include <SFE_LSM9DS0.h>

#define modeButton 10
#define btnUp 13
#define btnDown 14
#define beeper 21
#define battSense A0
#define NEW_MOON 944605920
#define LP       2551443L // Lunar period in seconds
#define charge 1

#define LSM9DS0_XM  0x1D // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6B // Would be 0x6A if SDO_G is LOW

SFE_BMP180 barometer;
LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

U8GLIB_DOGS102 u8g(7, 5, 4, 3, 2); // SPI Com: SCK = 7, MOSI = 5, CS = 4, A0 = 3

boolean mButton = false;
int mSelect = -1;
boolean miltimeSet = true;
boolean setBeep = false;
boolean beingSet = false;
boolean clockUp = true;

int contrast = 30;
int16_t mxMax, myMax, mzMax, mxMin, myMin, mzMin; //sets the max and min levels of the magnetometer to better determine heading

float temperature;
float pressure;

int maxMode = 10; //zero indexed number of modes
char* modeName[]={
  "Clock", "Weather", "Accel", "Magnetic", "Mag Cal", "Set Time","Status", "Settings", "Battery", "Moon Ph", "Song"};

//***************************************************
//*****     The 1 sec interrupt handler     *****
//***************************************************

SIGNAL(WDT_vect){
  //Add periodic operations
  if (mSelect == -1) clockUp = true;
}

//*********************************************
//*****     The modeButton interrupt     ******
//*********************************************

SIGNAL(INT0_vect){
  //Hitting the button sets the global variable mButton

  mButton = true;

  if (setBeep) tone(beeper, 4400, 200);

  //Debounce
  delay(20);
  while(digitalRead(modeButton) == LOW) ; //Wait for you to remove your finger
}


//*********************************************
//*****             SETUP                 *****
//*********************************************

void setup() {                
  //   To reduce power, setup all pins as inputs with no pullups
  for(int x = 1 ; x < 31 ; x++){
    pinMode(x, INPUT);
    digitalWrite(x, LOW);
  }

  pinMode(modeButton, INPUT); //This is the main button, tied to INT0
  digitalWrite(modeButton, HIGH); //Enable internal pull up on button

  pinMode(btnUp, INPUT); //This is the main button, tied to INT0
  digitalWrite(btnUp, HIGH); //Enable internal pull up on button

  pinMode(btnDown, INPUT); //This is the main button, tied to INT0
  digitalWrite(btnDown, HIGH); //Enable internal pull up on button

  pinMode(charge, INPUT);
  digitalWrite(charge, HIGH);

  Wire.begin();

  u8g.setContrast(contrast);
  u8g.setRot180();

  setTime(21, 35, 00, 6, 13, 2014); 
  setSyncProvider(RTC.get);  

  //Power down various bits of hardware to lower power usage  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  //Shut off as much as possible.

  //  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0xFF; //Disable digital input buffers on all ADC0-ADC7 pins
  DIDR1 = (1<<AIN1D)|(1<<AIN0D); //Disable digital input buffer on AIN1/0

  power_adc_disable(); 
  //  power_twi_disable();
  power_spi_disable();
  //  power_usart0_disable(); 
  //  power_usart1_disable(); 
  //  power_timer0_disable(); //Needed for delay and millis()
  power_timer1_disable();
//  power_timer2_disable(); //Needed for beep 
  power_timer3_disable();

  // Setup the watchdog timer to overflow every 8 seconds.
  MCUSR &= ~(1<<WDRF);
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1<<WDP0 | 1<<WDP3; // Set Watchdog Timer to interupt on 8 second overflow
  WDTCSR |= _BV(WDIE); // Enable Interupt with no reset

  //Setup external INT0 interrupt
  EICRA = (1<<ISC01); //Interrupt on falling edge
  EIMSK = (1<<INT0); //Enable INT0 interrupt

  barometer.begin();
  dof.begin();
  dof.setAccelODR(dof.A_POWER_DOWN);
  
  modeClock();

  sei(); //Enable global interrupts

  mButton = false;

}

//**********************************************
//*****               LOOP                 *****
//**********************************************

void loop() {
  if(!mButton) {
    if (clockUp) {
      modeClock();
      clockUp=false;
    }
    else {

      sleep_mode(); 
    }//Stop everything and go to sleep. Wake up if the WDT buffer overflows or if you hit the button
  }
  else {
    mButton = false;
    modeMenu();

    switch(mSelect){

    case -1:
      modeClock();
      break;
    case 0: // Clock
      modeClock();
      mSelect=-1;
      break;

    case 1:
      // Weather
      modeWeather();
      break;

    case 2:
      // Acceleration
      modeAccel();
      break;

    case 3:
      // Magnetic
      modeMag();
      break;        

    case 4:
      modeMagCal();
      break;

    case 5:
      modeSetTime();
      break;

    case 6: // free RAM
      modeStatus();
      break;

    case 7: // Settings
      modeSettings();
      break;

    case 8: // Battery
      modeBattery();
      break;

    case 9: // MoonPhase
      modeMoonPhase();
      break;

    case 10: // Song
      modeSong();
      break;

      mSelect = -1;
    }

  }
}











