// Displays the options for which watch function to jump to

void modeMenu(){
  
  mSelect = 0;

  setMenuDisplay(0);

  while (!mButton){
    if (digitalRead(btnDown) == LOW){
      delay(20);
      while(!digitalRead(btnDown));
      mSelect += 1;
      if (mSelect>maxMode) mSelect = 0;
      setMenuDisplay(mSelect); 
    }
    if (digitalRead(btnUp) == LOW){
      delay(20);
      while(!digitalRead(btnUp));
      mSelect -= 1;
      if (mSelect<0) mSelect = maxMode;
      setMenuDisplay(mSelect); 
    }
  }
  mButton = false;
  //Return with mSelect containing the desired mode
}

void setMenuDisplay(int mSel){

  int curSel = 0;
  // Display mode header

  u8g.firstPage();  
  do {  

    u8g.setFont(u8g_font_unifontr);
    u8g.setPrintPos(0,10);
    u8g.print("*** MENU ***");

    // Display current mode
    if (mSel == 0) curSel = maxMode;
    else curSel = mSel-1;

    u8g.setPrintPos(8,28);
    u8g.print(modeName[curSel]);

    u8g.setPrintPos(8,43);
    u8g.print("> ");
    u8g.print(modeName[mSelect]);

    if (mSel == maxMode) curSel = 0;
    else curSel = mSel+1;

    u8g.setPrintPos(8,58);
    u8g.print(modeName[curSel]);
  }     
  while( u8g.nextPage() );
}

