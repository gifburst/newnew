// Display the X, Y, and Z magnetic values

void modeMag(){
  float mx, my, mz;

  mButton = false;


  while(!mButton){

    dof.readMag();

    mx = map(dof.mx, mxMin, mxMax, -100, 100);
    my = map(dof.my, myMin, myMax, -100, 100);
    mz = map(dof.mz, mzMin, mzMax, -100, 100);    

    // To calculate heading in degrees. 0 degree indicates North
    float heading = atan2(mx, my);
    if(heading < 0)
      heading += 2 * M_PI;

    u8g.firstPage();  
    do {  
      // Display battery state
      u8g.setFont(u8g_font_04b_03r);
      u8g.setPrintPos(0, 8);
      u8g.print("Magnetic Field");
      u8g.setPrintPos(0, 16);
      u8g.print("X: ");
      u8g.print(mx);
      u8g.setPrintPos(0, 24);
      u8g.print("Y: ");
      u8g.print(my);
      u8g.setPrintPos(0,32);
      u8g.print("Z: ");
      u8g.print(mz);

      u8g.drawFrame(40, 30, 56, 30);
      u8g.setPrintPos(40, 24);
      u8g.setFont(u8g_font_unifontr);
      u8g.print("Heading");
      u8g.setPrintPos(43, 50);
      u8g.setFont(u8g_font_courB10);
      u8g.print(heading *180/M_PI, 1);
    } 
    while( u8g.nextPage() );

    delay(500); 
  }
  mButton = false; 

  modeClock();
}




