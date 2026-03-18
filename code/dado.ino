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
  pinMode(ButtPin, INPUT_PULLUP);
  pinMode(BuzzPin, OUTPUT);
}

void loop() {
  int result=0;
  int dice[]={4, 6, 8, 10, 12, 20, 100};
  int indDice=6;
  int indDiceT=6;

  int page=0;

  bool teatrical=0;

  int time;
  int diff;
  
  diff=millis()-time;
  if(!digitalRead(ButtPin))
    time=millis();
  else{
    if(diff>=2000){
      //shutdown();
    }
    else{
			if(diff>10){
				time=millis();
				indDiceT=(indDiceT+1)%nDices;
				page=1;
			}
		}
  }
	
	switch(page){
		case 0:
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
			break;
			
		case 1:
			if(!digitalRead(TitlPin)){
				page=0;	
				indDice=indDiceT;
			}
			break;
	}
}

