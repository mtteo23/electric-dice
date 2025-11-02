#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Try 0x3C or 0x3D depending on your module
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define nDices 7

int TitlPin=3;
int ButtPin=0;
int BuzzPin=0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  pinMode(TitlPin, INPUT);
  pinMode(ButtPin, INPUT);
  pinMode(BuzzPin, OUTPUT);
}
  int dice = 20;

void loop() {
  int result=0;
  int dice[]={4, 6, 8, 10, 12, 20, 100};
  int indDice=6;
  int indDiceT=6;

  int page=0;

  bool teatrical=0;

  int time=0;
  
  if(!digitalRead(ButtPin))
    time=millis();
  else{
    if(millis()-time>=2000){
      //shutdown();
    }
    if(millis()-time>0){
      time=0;
      indDiceT=(indDiceT+1)%(nDices+1);
      page=1;
    }
  }

  if(page == 0){
    if(!digitalRead(TitlPin)){
      if(teatrical==1){
        teatrical=0;
        //TODO
      }
      else{
        result=random(dice[indDice])+(dice[indDice]!=100);

        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(9);
        display.setCursor(45, 0);
        if(result>9)
          display.setCursor(14, 0);
        display.println(String(result)); // Print text
        display.display(); 
        
        delay(50);
      }
    }
  }
  else{
    if(page==1){
      if(indDice==nDices){
        if(!digitalRead(TitlPin)){
          page=0;
          teatrical=1;
          if(indDiceT!=nDices){
            indDice=indDiceT;
          }
        }
      }
      else{
        if(!digitalRead(TitlPin)){
          page=0;
          if(indDiceT!=nDices){
            indDice=indDiceT;
          }
        }
      }
    }
  }
}
