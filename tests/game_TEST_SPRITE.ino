#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// 'PNG - UP', 14x10px
const unsigned char sprite_UP [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x24, 0x90, 0x44, 0x88, 0x80, 0x04, 0x82, 0x84, 0x81, 0x04, 0x80, 0x04, 
	0x40, 0x08, 0x3f, 0xf0
};
// 'PNG -  RIGHT', 14x10px
const unsigned char sprite_RIGHT [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x82, 0x44, 0x82, 0x44, 0x80, 0x04, 0x81, 0x44, 
	0x40, 0x88, 0x3f, 0xf0
};
// 'PNG - LEFT', 14x10px
const unsigned char sprite_LEFT [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x89, 0x04, 0x89, 0x04, 0x80, 0x04, 0x8a, 0x04, 
	0x44, 0x08, 0x3f, 0xf0
};
// 'PNG - DOWN', 14x10px
const unsigned char sprite_DOWN [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x80, 0x04, 0x84, 0x84, 0x84, 0x84, 0x80, 0x04, 
	0x42, 0x88, 0x3f, 0xf0
};
// 'PNG - NORMAL', 14x10px
const unsigned char sprite_NORMAL [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x84, 0x84, 0x84, 0x84, 0x80, 0x04, 0x82, 0x84, 
	0x41, 0x08, 0x3f, 0xf0
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 240)
const int epd_bitmap_allArray_LEN = 5;
const unsigned char* sprite_allArray[5] = {
	sprite_DOWN,
	sprite_LEFT,
	sprite_NORMAL,
	sprite_UP,
	sprite_RIGHT
};

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);  // Pause for 2 seconds

  // Clear the buffer.
  display.clearDisplay();

  // Draw bitmap on the screen
  //display.drawBitmap(x, y, spriteName, w, h, color)
  display.drawBitmap(0, 28, sprite_NORMAL, 14, 10, 1);
  display.drawBitmap(20, 28, sprite_LEFT, 14, 10, 1);
  display.drawBitmap(40, 28, sprite_RIGHT, 14, 10, 1);
  display.drawBitmap(60, 28, sprite_UP, 14, 10, 1);
  display.drawBitmap(80, 28, sprite_NORMAL, 14, 10, 1);
  display.display();

}

void loop() {
  //display.drawBitmap(0, 0, epd_bitmap_allArray[counter], 128, 64, 1);
  //display.display();
  //display.clearDisplay();
}
