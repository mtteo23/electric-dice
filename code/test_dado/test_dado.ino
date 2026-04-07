#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Try 0x3C or 0x3D depending on your module
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int TiltPin = 2;
int ButPin = 3;
int LedPin = 4;
int BuzPin = 0;

void setup() {
	Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("Display not found");
  }

  pinMode(TiltPin, INPUT_PULLUP);
  pinMode(ButPin, INPUT_PULLUP);
  pinMode(LedPin, OUTPUT);
  
  
}

void loop() {
	delay(50);
	String message="test display";
	if(digitalRead(TiltPin)){
		Serial.println("tilt up");
		message=message+"\ntilt up";
	}else{
		Serial.println("tilt down");
		message=message+"\ntilt down";
	}
	
	if(digitalRead(ButPin)){
		Serial.println("button pressed");
		message=message+"\nbutton pressed";
	}else{
		Serial.println("button released");
		message=message+"\nbutton released";
	}
	
	digitalWrite(LedPin, HIGH);
	
	display.clearDisplay();
	display.setTextColor(SSD1306_WHITE);
	display.setTextSize(1);
	display.setCursor(0, 0);
	display.println(message);
	display.display(); 
}

/* Per l'esp32-c3
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1        // No reset pin
#define SCREEN_ADDRESS 0x3C     // Most common I2C address

// ESP32-C3 I2C pins (adjust if needed)
#define SDA_PIN 8
#define SCL_PIN 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // Init I2C with explicit pins for ESP32-C3
  Wire.begin(SDA_PIN, SCL_PIN);

  // Init display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 not found! Check wiring.");
    while (true);  // Halt
  }

  display.clearDisplay();

  display.setTextSize(2);               // Scale 2 = larger text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);            // X, Y position
  display.println("Hello");

  display.setTextSize(1);               // Scale 1 = normal text
  display.setCursor(25, 45);
  display.println("ESP32-C3 OLED!");

  display.display();                    // Push buffer to screen
}

void loop() {
  // Nothing needed here
}
*/
