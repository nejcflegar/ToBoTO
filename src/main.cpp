#include <Arduino.h>
#include <TFT_eSPI.h>
#include "mc.h"
#include "Objects.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite MainKnight = TFT_eSprite(&tft);
TFT_eSprite background1 = TFT_eSprite(&tft);
TFT_eSprite background2 = TFT_eSprite(&tft);


#define buttonRight 16
#define buttonLeft 4

Human Me = Human(100,100,true);

long CurrentTime = 0;
long BackupTimer = 0;

void setup(){
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_YELLOW);

  background1.createSprite(320,50);
  background1.setSwapBytes(true);
  background1.fillRect(0,0,320,50,TFT_DARKGREEN);

  background2.createSprite(320,160);
  background2.setSwapBytes(false);
  background2.fillRect(0,0,320,160,TFT_CYAN);
  

  MainKnight.createSprite(16,16);
  MainKnight.setSwapBytes(true);
  MainKnight.pushImage(0,0,16,16,knight[Me.skinRotation]);

  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);

  Serial.begin(9600);
}

void picture(){

  MainKnight.pushToSprite(&background2,Me.xPos,Me.yPos,TFT_WHITE);
  background1.pushSprite(0,190);
  background2.pushSprite(0,30);
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
  move();
  gravity();
  picture();
}