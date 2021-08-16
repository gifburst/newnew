// Displays the current phase of the moon

void modeMoonPhase(){

  uint8_t phase = 0;
  uint8_t pixI;
  float pixD;
  uint8_t mPix;
  
  mButton = false;
  
  time_t t = RTC.get();
  phase = (uint8_t) (((t - NEW_MOON) % LP) / (24L * 3600L));
  mPix = map(phase, 0, 29, 1, 100);

    u8g.firstPage();  
    do {
      u8g.setFont(u8g_font_04b_03r);
      u8g.setPrintPos(0,8);
      u8g.print("NEW MOON");
      u8g.drawLine(0, 10, 101, 10);
      u8g.drawLine(0, 55, 101, 55);
      u8g.drawLine(0, 10, 0, 55);
      u8g.drawLine(101, 10, 101, 55);
      u8g.drawLine(0, 33, 101, 33);
      u8g.setPrintPos(0,63);
      u8g.print("FULL MOON ");  
    
      for (int i = 1;i<100;i++){
        pixD = -sin(i * 2 * M_PI / 100.0 + (M_PI/2));
        pixI = pixD*23 + 33;
        u8g.drawPixel(i,pixI);
        if (i==mPix) u8g.drawCircle(i, pixI, 2);
      }
    } while( u8g.nextPage() );
    
    while(!mButton) {
      delay(25);
    }
    
  mButton = false;
  modeClock();
}

