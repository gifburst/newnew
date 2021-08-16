// Display the ammount of RAM

void modeStatus(){

  mButton = false;


  while(!mButton){

    u8g.firstPage();  
    do {  
      // Display battery state
      u8g.setFont(u8g_font_unifontr);
      u8g.setPrintPos(0,10);
      u8g.print("** Status **");

      u8g.setPrintPos(3,30);
      u8g.print("FR: ");
      u8g.print(freeRam());
      u8g.print(" B");

      u8g.setPrintPos(3,45);
      u8g.print("RTC: ");
      if(timeStatus()!= timeSet) u8g.print("Err");
      else u8g.print("Ok");

      u8g.setPrintPos(3,60);
      u8g.print("Barom: ");
      u8g.print("Ok");

    } 
    while( u8g.nextPage() );
  }
  mButton = false; 
  modeClock();
}   

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}


