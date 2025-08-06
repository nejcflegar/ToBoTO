#include <Arduino.h>
#include <TFT_eSPI.h>
#include "mc.h"
#include "Objects.h"
#include "maps.cpp"
#include "tla.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite MainKnight = TFT_eSprite(&tft);
TFT_eSprite GroundEarth = TFT_eSprite(&tft);
TFT_eSprite BackGround = TFT_eSprite(&tft);
TFT_eSprite SkyLine = TFT_eSprite(&tft);

TFT_eSprite GroundPicture[192] = TFT_eSprite(&tft);
Ground GroundValues[192] = Ground();

#define buttonRight 16
#define buttonLeft 4

Human Me = Human(100,100,true);

long CurrentTime = 0;
long BackupTimer = 0;

int mapCount = 0; //sets which map is displayed
boolean newMap = true;
Map mapObj =  Map();
int countTile = 0;

void setup(){
  tft.init();
  tft.setRotation(3);

  GroundEarth.createSprite(320,60);
  GroundEarth.setSwapBytes(true);
  GroundEarth.fillRect(0,0,320,60,TFT_DARKGREEN);

  BackGround.createSprite(320,140);
  BackGround.setSwapBytes(false);
  BackGround.fillRect(0,0,320,140,TFT_CYAN);
  
  SkyLine.createSprite(320,40);
  SkyLine.setSwapBytes(true);
  SkyLine.fillRect(0,0,320,40,TFT_YELLOW);

  MainKnight.createSprite(16,16);
  MainKnight.setSwapBytes(true);
  MainKnight.pushImage(0,0,16,16,knight[Me.skinRotation]);

  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);

  for(int i = 0; i < 192; i++){
    GroundPicture[i].createSprite(20,20);
  }


  Serial.begin(9600);
}

//naredi da mas 3 arraya za 3 backgrounde in potem jih samo gor vrzeses

void picture(){

for(int i = 0; i < 192; i++){

}  

  MainKnight.pushToSprite(&BackGround,Me.xPos,Me.yPos,TFT_WHITE);
  GroundEarth.pushSprite(0,180);
  SkyLine.pushSprite(0,0);
  BackGround.pushSprite(0,40);
}

void generateMap(int x){
  //Ground Earth
  countTile = 0;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 12; j++){
      switch(mapObj.getMap(x,i,j)){
        case 0: 
          GroundPicture[countTile].pushImage(0,0,20,20,tla[0]);
          GroundValues[countTile].setXY(i*20,j*20);
          break;
        case 1:
          GroundPicture[countTile].pushImage(0,0,20,20,tla[1]);
          GroundValues[countTile].setXY(i*20,j*20);
          break;
      }
      countTile++;
    }
  } 
}

void gravity(){
  if(Me.atGround != false){
    if(Me.yVel < 100){
      Me.yVel++;
    }
  }
}

void move(){
  if(Me.yVel != 0){
    Me.yPos += (Me.yVel / 25) + 1;
  }

  if(Me.xVel != 0){
    if(Me.xVel > 0){
      if((0 < Me.xVel) && (Me.xVel < 25)){
        Me.xPos++;
      }else if((25 < Me.xVel) && (Me.xVel < 50)){     
        Me.xPos+=2;
      }else if((50 < Me.xVel) && (Me.xVel < 75)){
        Me.xPos+=3;
      }else if((75 < Me.xVel) && (Me.xVel < 100)){
        Me.xPos+=4;
      }
    }else{
      if((0 > Me.xVel) && (Me.xVel > -25)){
        Me.xPos--;
      }else if((-25 > Me.xVel) && (Me.xVel > -50)){     
        Me.xPos-=2;
      }else if((-50 > Me.xVel) && (Me.xVel > -75)){
        Me.xPos-=3;
      }else if((-75 > Me.xVel) && (Me.xVel > -100)){
        Me.xPos-=4;
      }
    }
  }
}


void loop(){
  CurrentTime = millis();
  if(CurrentTime - BackupTimer >= 333){
    BackupTimer = CurrentTime;
    if(Me.skinRotation != 2){
      Me.skinRotation++;
    }else{
      Me.skinRotation = 0;
    }
    MainKnight.pushImage(0,0,16,16,knight[Me.skinRotation]);
  }

  if(digitalRead(buttonLeft) == 0){
    if(Me.xVel > 0){
      Me.xVel -= 10;
    }else{
      if(Me.xVel > -100){
        Me.xVel--;
      }
    }
  }

  if(digitalRead(buttonRight) == 0){
    if(Me.xVel < 0){
      Me.xVel += 10;
    }else{
      if(Me.xVel < 100){
        Me.xVel++;
      }
    }
  }

  if(digitalRead(buttonRight) == digitalRead(buttonLeft)){
    Me.xVel = 0;
  }

  /*
  Serial.print("Levo: ");
  Serial.print(digitalRead(buttonLeft));
  Serial.print("  ||  ");
  Serial.print("Desno: ");
  Serial.print(digitalRead(buttonRight));
  Serial.print("  ||  ");
  Serial.print(Me.xVel);
  Serial.print("  ||  ");
  Serial.println(Me.xPos);
  */

  if(newMap == true){
    newMap = false;
    generateMap(mapCount);
  }

  move();
  gravity();
  picture();
}