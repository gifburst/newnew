// The mode that displays the time for a few seconds.
// Do nothing and the routine will return and turn off the display
// if the modButton is pressed, you will enter the menu

void modeClock(){
  time_t t = RTC.get();

  // Display current time

  u8g.firstPage();  
  do {  
    // Display current time

    u8g.setPrintPos(5, 30);
    u8g.setFont(u8g_font_osb21r);
    getNumOnes(hour(t));

    u8g.setPrintPos(55, 50);
    u8g.setFont(u8g_font_courB18r);
    if (minute(t)<10) u8g.print("0");
    u8g.print(minute(t));

    u8g.setPrintPos(1, 63);
    u8g.setFont(u8g_font_04b_03r);
    u8g.print("Batt: ");

    power_adc_enable(); 
    u8g.print(analogRead(24)*.006373, 2);
    u8g.print("v");
    power_adc_disable(); 

  }  while( u8g.nextPage() );
}

void getNumOnes(int numT){
  switch (numT){
    case 1:
    case 13:
    u8g.print(" One");
    break;
    
    case 2:
    case 14:
    u8g.print(" Two");
    break;
    
    case 3:
    case 15:
    u8g.print("Three");
    break;
    
    case 4:
    case 16:
    u8g.print(" Four");
    break;
    
    case 5:
    case 17:
    u8g.print(" Five");
    break;
    
    case 6:
    case 18:
    u8g.print("   Six");
    break;
    
    case 7:
    case 19:
    u8g.print("Seven");
    break;
    
    case 8:
    case 20:
    u8g.print("Eight");
    break;
    
    case 9:
    case 21:
    u8g.print(" Nine");
    break;
    
    case 10:
    case 22:
    u8g.print("  Ten");
    break;
    
    case 11:
    case 23:
    u8g.print("Eleven");
    break;
    
    case 12:
    case 0:
    u8g.print("Twelve");
    break;
  }
}
