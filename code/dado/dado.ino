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

int TitlPin=2;
int ButtPin=3;
int BuzzPin=0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  pinMode(TitlPin, INPUT_PULLUP);
  pinMode(ButtPin, INPUT_PULLUP);
  pinMode(BuzzPin, OUTPUT);
  
  display.clearDisplay();
	display.setTextColor(SSD1306_WHITE);
	display.setTextSize(2);
	display.setCursor(20, 20);
	display.println("electric\n  dice");
	display.display();
}

void loop() {
  int result=0;
  int dice[]={4, 6, 8, 10, 12, 20, 100};
  int indDice=6;

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
				indDice=(indDice+1)%nDices;
				page=1;
			}
		}
  }
	
	switch(page){
		case 0:
			if(!digitalRead(TitlPin)){
				if(teatrical){
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
			display.clearDisplay();
			display.setTextColor(SSD1306_WHITE);
			display.setTextSize(2);
			display.setCursor(0, 0);
			display.println("electric\ndice");
			display.display();
			if(!digitalRead(TitlPin)){
				page=0;
			}
			break;
	}
}

