void modeMagCal(){

  mButton = false;

  mxMax = 0;
  myMax = 0;
  mzMax = 0;
  mxMin = 200000;
  myMin = 200000;
  mzMin = 200000;



  while(!mButton){

    dof.readMag();

    if (dof.mx>mxMax) mxMax = dof.mx;
    if (dof.my>myMax) myMax = dof.my;
    if (dof.mz>mzMax) mzMax = dof.mz;
    if (dof.mx<mxMin) mxMin = dof.mx;
    if (dof.my<myMin) myMin = dof.my;
    if (dof.mz<mzMin) mzMin = dof.mz; 

    u8g.firstPage();  
    do {  
      // Display battery state
      u8g.setFont(u8g_font_unifontr);
      u8g.setPrintPos(0, 10);
      u8g.print("Mag Cal");
      u8g.setFont(u8g_font_04b_03r);
      u8g.setPrintPos(0,20);
      u8g.print("Rotate slowly 360 deg");
      u8g.setPrintPos(0,30);
      u8g.print("Xmax: ");
      u8g.print(mxMax);
      u8g.setPrintPos(45,30);
      u8g.print("Xmin: ");
      u8g.print(mxMin);
      u8g.setPrintPos(0,40);
      u8g.print("Ymax: ");
      u8g.print(myMax);
      u8g.setPrintPos(45,40);
      u8g.print("Ymin: ");
      u8g.print(myMin);
      u8g.setPrintPos(0,50);
      u8g.print("Zmax: ");
      u8g.print(mzMax);
      u8g.setPrintPos(45,50);
      u8g.print("Zmin: ");
      u8g.print(mzMin);      
    }
    while( u8g.nextPage() );
  }
  mButton = false; 

  modeClock();    
}


