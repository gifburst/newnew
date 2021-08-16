// Display the X, Y, and Z acceleration

void modeAccel(){

  mButton = false;
  dof.setAccelODR(dof.A_ODR_100);
  delay(300);
  
  while(!mButton){
 
    dof.readAccel();

    float axf, ayf, azf;

    axf=dof.calcAccel(dof.ax);
    ayf=dof.calcAccel(dof.ay);
    azf=dof.calcAccel(dof.az);

    u8g.firstPage();  
    do {

      u8g.setFont(u8g_font_04b_03r);
      u8g.setPrintPos(0,8);
      u8g.print("Accel Data (g)");
      u8g.setPrintPos(0,16);
      u8g.print("X: ");
      u8g.print(ayf, 2);
      u8g.setPrintPos(0,24);
      u8g.print("Y: ");
      u8g.print(axf, 2);
      u8g.setPrintPos(0,32);
      u8g.print("Z: ");
      u8g.print(azf, 2);

      u8g.drawFrame(50, 10, 50, 50);
      u8g.drawCircle(axf*20 + 76, ayf*20 + 35, 4);
      u8g.drawLine(71, 35, 81, 35);
      u8g.drawLine(75, 30, 75, 40);
    } 
    while( u8g.nextPage() );

    delay(100);
  }
  mButton = false; 
  dof.setAccelODR(dof.A_POWER_DOWN);
  modeClock();
}



