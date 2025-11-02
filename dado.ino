#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Try 0x3C or 0x3D depending on your module
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int TitlPin = 3;
int ButPin = 0;
int BuzPin = 0;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); // Stop if display not found
  }

  pinMode(PinTilt, INPUT);
}

void loop() {
  int result=0;
  
  if(!digitalRead(PinTilt))
  {
    result=random(20)+1;
    delay(50);
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(9);
    display.setCursor(45, 0);
    if(result>9)
      display.setCursor(14, 0);
    display.println(String(result)); // Print text
    display.display(); 
  }
}
