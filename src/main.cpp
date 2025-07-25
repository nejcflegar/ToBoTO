#include <Arduino.h>
#include <TFT_eSPI.h>
#include "mc.h"
#include "Objects.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite MainKnight = TFT_eSprite(&tft);
TFT_eSprite background1 = TFT_eSprite(&tft);
TFT_eSprite background2 = TFT_eSprite(&tft);


#define buttonLeft 16
#define buttonRight 4

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
  MainKnight.pushToSprite(&background2,Me.xPos,Me.yPos,TFT_WHITE);
  background1.pushSprite(0,190);
  background2.pushSprite(0,30);
  Serial.print(digitalRead(buttonLeft));
//  Serial.print(digitalRead(buttonRight));
}