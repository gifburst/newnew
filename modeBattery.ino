// Check Battery status

void modeBattery(){
  
  //Turn on the ADC
  power_adc_enable(); 
  
  delay(200);

  mButton = false;
  int bV;

  while(!mButton){

    bV = analogRead(24);
    power_adc_disable(); 

    u8g.firstPage();  
    do {  
      // Display battery state
      u8g.setFont(u8g_font_unifontr);
      u8g.setPrintPos(0,10);
      u8g.print("* Battery *");
      u8g.setPrintPos(10,35);
      u8g.print("ADC: ");
      u8g.print(bV);
      u8g.setPrintPos(10,50);
      u8g.print("V: ");
      u8g.print(bV*0.006373 , 2);
      u8g.print(" V");

    } 
    while( u8g.nextPage() );
    delay(500);
  }
  mButton = false; 
  modeClock();
}


