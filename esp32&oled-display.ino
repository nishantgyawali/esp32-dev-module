// 128×32 Split-color OLED (yellow top + blue bottom)
// Navbar starts at (1,1) - yellow bg (lit) + black text

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C   // change to 0x3D if screen is black

#define SDA_PIN 26
#define SCL_PIN 27

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("OLED 128x32 - Navbar at (1,1)");

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 init failed - check wiring/address"));
    for(;;);
  }

  display.clearDisplay();

  // ─── TOP NAVBAR (yellow when lit) ───────────────────────────────
  int navHeight = 16;   // small height to keep yellow in upper part only

  // Fill top area → lights up yellow pixels
  display.fillRect(0, 0, SCREEN_WIDTH, navHeight, SSD1306_WHITE);

  // NAV bar
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(40, 1);               // exactly as requested: start from 1,1
  display.print("Hello");

    // content 
  display.setCursor(17,10);  
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("\n Nishant");
 


  display.display();
}

void loop() {
  // static display
}