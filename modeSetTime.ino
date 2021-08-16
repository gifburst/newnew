// This mode sets the current time

void modeSetTime(){
  
  int tDigit = 0;
  int tHour = hour();
  int tMinute = minute();
  int tDay = day();
  int tMonth = month();
  int tYear = year();

  boolean exit = false;

  mSTdisplay(tDigit, tHour, tMinute, tDay, tMonth, tYear);

  while (!exit){
    if (digitalRead(btnUp) == LOW){
      if (tDigit == 0) tHour += 1;
      if (tDigit == 1) tMinute += 1;
      if (tDigit == 2) tMonth += 1;
      if (tDigit == 3) tDay += 1;
      if (tDigit == 4) tYear += 1;
      if (tDigit == 5) exit = true;

      if (tHour > 23) tHour = 0;
      if (tMinute > 59) tMinute = 0;
      if (tDay > 31) tDay = 1;
      if (tMonth > 12) tMonth = 1;
      mSTdisplay(tDigit, tHour, tMinute, tDay, tMonth, tYear);
      delay(100); 
    }

    if (digitalRead(btnDown) == LOW){
      if (tDigit == 0) tHour -= 1;
      if (tDigit == 1) tMinute -= 1;
      if (tDigit == 2) tMonth -= 1;
      if (tDigit == 3) tDay -= 1;
      if (tDigit == 4) tYear -= 1;
      if (tDigit == 5) exit = true;

      if (tHour < 1) tHour = 23;
      if (tMinute < 0) tMinute = 59;
      if (tDay < 1) tDay = 31;
      if (tMonth < 1) tMonth = 12;
      mSTdisplay(tDigit, tHour, tMinute, tDay, tMonth, tYear);
      delay(100); 
    }

    if (mButton){
      tDigit+=1;
      if (tDigit >5) tDigit = 0;
      mSTdisplay(tDigit, tHour, tMinute, tDay, tMonth, tYear);
      delay(100);
      mButton = false;
    }
  }
  mButton = false;
  setTime(tHour, tMinute, 00, tDay, tMonth, tYear); 
  RTC.set(now()); 
  modeClock();
}

void mSTdisplay(int tDig, int tH, int tM, int tdD, int tdM, int tdY){

  u8g.firstPage();  
  do {  
    // Display current time
    u8g.setFont(u8g_font_04b_03r);
    u8g.setPrintPos(0,8);
    u8g.print("* Set Time *");
    
    u8g.setFont(u8g_font_unifontr);
    u8g.setPrintPos(0,38);

    if (tDig != 1) u8g.setFont(u8g_font_freedoomr25n);
    u8g.print(tH);
    u8g.print(":");
    u8g.setFont(u8g_font_unifontr);
    if (tDig != 0) u8g.setFont(u8g_font_freedoomr25n);
    if (tM<10) u8g.print("0");
    u8g.print(tM);

    u8g.setFont(u8g_font_unifontr);
    u8g.setPrintPos(0,52);
    if (tDig == 2) u8g.print(">");
    u8g.print(tdM);
    u8g.print("/");
    if (tDig == 3) u8g.print(">");
    u8g.print(tdD);
    u8g.print("/");
    if (tDig == 4) u8g.print(">");
    u8g.print(tdY);
    
    u8g.setPrintPos(0,63);
    if (tDig == 5) u8g.print("=>");
    u8g.print("DONE");  
  } 
  while( u8g.nextPage() );
}


