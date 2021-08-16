// Set various options

void modeSettings(){
  int tItem = 0;

  boolean exit = false;
  setdisplay(tItem);

  while (!exit){
    if (digitalRead(btnUp) == LOW){
      if (tItem == 0) miltimeSet = !miltimeSet;
      if (tItem == 1) {
        contrast += 1;
        if (contrast > 63) contrast = 63;
        u8g.setContrast(contrast);
      }
      if (tItem == 2) setBeep = !setBeep;
      if (tItem == 3) exit = true;

      setdisplay(tItem);
      delay(100); 
    }

    if (digitalRead(btnDown) == LOW){
      if (tItem == 0) miltimeSet = !miltimeSet;
      if (tItem == 1) {
        contrast -= 1;
        if (contrast < 0) contrast = 0;
        u8g.setContrast(contrast);
      }  
      if (tItem == 2) setBeep = !setBeep;
      if (tItem == 3) exit = true;

      setdisplay(tItem);
      delay(100); 
    }

    if (mButton){
      tItem+=1;
      if (tItem >3) tItem = 0;
      setdisplay(tItem);
      delay(100);
      mButton = false;
    }
  }
  mButton = false;
  modeClock();
}

void setdisplay(int tDig){

  u8g.firstPage();  
  do {  
    // Display battery state
    u8g.setFont(u8g_font_unifontr);
    u8g.setPrintPos(0,10);
    u8g.print("* Settings *");

    u8g.setPrintPos(0,25);
    if (tDig == 0) u8g.print(">");
    u8g.print("Time: ");
    if (miltimeSet) u8g.print("24");
    else u8g.print("12");

    u8g.setPrintPos(0,38);
    if (tDig == 1) u8g.print(">");
    u8g.print("Cntrst: ");
    u8g.print(contrast);

    u8g.setPrintPos(0,51);
    if (tDig == 2) u8g.print(">");
    u8g.print("Beep: ");
    if (setBeep) u8g.print("On");
    else u8g.print("Off");

    u8g.setPrintPos(0,63);
    if (tDig == 3) u8g.print("=>");  
    u8g.print("DONE");  
  }    
  while( u8g.nextPage() );
}


