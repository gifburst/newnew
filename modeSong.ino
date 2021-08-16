// Play song to test speaker. Can also call for triggered events (alarms, warnings, etc)

void modeSong(){
  
char noteNames[] =     {'C','D','E','F','G','a','b'};
unsigned int frequencies[] = {262,294,330,349,392,440,494};
const byte noteCount = sizeof(noteNames); // number of notes (7 here)

//notes, a space represents a rest
char score[] = "CCGGaaGFFEEDDC GGFFEEDGGFFEED CCGGaaGFFEEDDC ";  
const byte scoreLen = sizeof(score); // the number of notes in the score

for (int i = 0; i < scoreLen; i++)
  {
    int duration = 333;  // each note lasts for a third of a second
    
    for (int j = 0; j < noteCount; j++)
  { 
    if (noteNames[j] == score[i]) // find a matching note name in the array
      tone(beeper, frequencies[j], duration); //  play the note
  }
      delay(duration); 
  }
  
  mButton = false; 
  modeClock();
}


