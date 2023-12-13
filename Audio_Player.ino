#include <SD.h> // need to include the SD library
#define SD_ChipSelectPin 4 //connect pin 4 of arduino to cs pin of sd card
#include <TMRpcm.h> //Arduino library for asynchronous playback of PCM/WAV files
#include <SPI.h> //  need to include the SPI library

TMRpcm tmrpcm; // create an object for use in this sketch
int CurrentSong=1;
int PlayPauseButton=5;
int NextButton=6;
int PrevButton=7;
int MaxSongs=4;  //Should be equal to the total number of songs in the SD card

void setup()
{ 
 pinMode(PlayPauseButton,INPUT_PULLUP);
 pinMode(NextButton,INPUT_PULLUP);
 pinMode(PrevButton,INPUT_PULLUP);
 
 tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
 Serial.begin(9600);
 if (!SD.begin(SD_ChipSelectPin)) // returns 1 if the card is present
 {
  Serial.println("SD fail");
  return;
 }

 tmrpcm.setVolume(5); //
 tmrpcm.play("song1.wav"); //the sound file "song" will play each time the arduino powers up, or is reset
                          //try to provide the file name with extension
                     
}


void loop()
{  
  while(digitalRead(PlayPauseButton)==0 || digitalRead(NextButton)==0 || digitalRead(PrevButton)==0)
  {
    if(digitalRead(PlayPauseButton)==0)
    {
      tmrpcm.pause();
      while(digitalRead(PlayPauseButton)==0);
      delay(200);
    }
    else if(digitalRead(NextButton)==0)
    {
      if(CurrentSong<MaxSongs){//CurrentSong should be lesser than no. of songs 
        CurrentSong=CurrentSong+1;
        while(digitalRead(NextButton)==0);
          delay(200);
          song();
      }
      else{  //If song is the last then continue to song 1
        CurrentSong=1; 
        while(digitalRead(NextButton)==0);
          delay(200);
          song();
      }
    }
    else if(digitalRead(PrevButton)==0)
    {
      if(CurrentSong>1){
        CurrentSong=CurrentSong-1;
        while(digitalRead(PrevButton)==0);
        delay(200);
        song();
      }
      else{ //If song is 1 then loops around to the last song in the sd card
        CurrentSong = MaxSongs;
        while(digitalRead(PrevButton)==0);
        delay(200);
        song();
      }
    }
  }
}

void song (void)
{
  if(CurrentSong==1)
  {
    tmrpcm.play("Song1.wav");  
  }
  else if(CurrentSong==2)
  {
    tmrpcm.play("Song2.wav");  
  }
  else if(CurrentSong==3)
  {
    tmrpcm.play("Song3.wav");  
  }
  else if(CurrentSong==4)
  {
    tmrpcm.play("Song4.wav");  
  }
}
