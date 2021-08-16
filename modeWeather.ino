// Displays the Pressure and Temperature

void modeWeather(){

  while(!mButton){

    getWeatherData();

    u8g.firstPage();  
    do {  
      // Display battery state
      u8g.setFont(u8g_font_unifontr);
      u8g.setPrintPos(0,10);
      u8g.print("* Weather *");

      u8g.setPrintPos(3,28);
      u8g.print("T: ");
      u8g.print(temperature);
      u8g.print(" oF");

      u8g.setPrintPos(3,43);
      u8g.print("P: ");
      u8g.print(pressure , 2);

    } 
    while( u8g.nextPage() );     

    delay(500);
  }
  mButton = false;
  modeClock();
}

void getWeatherData(){
    char status;
     double T,P;
     
    status = barometer.startTemperature();
  if (status != 0)  delay(status);
    
    barometer.getTemperature(T);
    temperature =float( T*1.8+32.0);
    
    status = barometer.startPressure(3);
      if (status != 0) delay(status);  
      
    status = barometer.getPressure(P, T);
    pressure = float(P);
}
