//~~~ADAFRUIT~~~
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//~~~MOVEMENT~~~
#define JUMP_HEIGHT 20
#define JUMP_SPEED 2
#define MOVE_SPEED 1

#define STATE_REGULAR 0
#define STATE_JUMP_UP 1
#define STATE_JUMP_DOWN 2
int state;
int button_new, button_old;
int jump_displacement;
bool jump_finished;

//~~~GENERAL~~
#define BUTTON_PIN_LEFT 2
#define BUTTON_PIN_UP 4
#define BUTTON_PIN_RIGHT 7
int pos_x, pos_y, pos_y_original, r;

#define SPRITE_WIDTH 14
#define SPRITE_HEIGHT 10

//14x10px
const unsigned char sprite_UP [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x24, 0x90, 0x44, 0x88, 0x80, 0x04, 0x82, 0x84, 0x81, 0x04, 0x80, 0x04, 
	0x40, 0x08, 0x3f, 0xf0
};
const unsigned char sprite_RIGHT [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x82, 0x44, 0x82, 0x44, 0x80, 0x04, 0x81, 0x44, 
	0x40, 0x88, 0x3f, 0xf0
};
const unsigned char sprite_LEFT [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x89, 0x04, 0x89, 0x04, 0x80, 0x04, 0x8a, 0x04, 
	0x44, 0x08, 0x3f, 0xf0
};
const unsigned char sprite_DOWN [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x80, 0x04, 0x84, 0x84, 0x84, 0x84, 0x80, 0x04, 
	0x42, 0x88, 0x3f, 0xf0
};
const unsigned char sprite_NORMAL [] PROGMEM = {
	0x07, 0x80, 0x18, 0x60, 0x20, 0x10, 0x40, 0x08, 0x84, 0x84, 0x84, 0x84, 0x80, 0x04, 0x82, 0x84, 
	0x41, 0x08, 0x3f, 0xf0
};

//(Total bytes used to store images in PROGMEM = 240)
const int sprite_allArray_LEN = 5;
const unsigned char* sprite_allArray[5] = {
	sprite_DOWN,  //0
	sprite_LEFT,  //1
	sprite_NORMAL,//2
	sprite_UP,    //3
	sprite_RIGHT  //4
};

int sprite_state;

void setup() {
  //***OLED INITIALIZATION***
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000); 
  display.clearDisplay();

  //***BUTTON INITIALIZATION***
  pinMode(BUTTON_PIN_LEFT, INPUT);
  pinMode(BUTTON_PIN_UP, INPUT);
  pinMode(BUTTON_PIN_RIGHT, INPUT);

  //***SETUP***
  pos_x = 64 - SPRITE_WIDTH;
  pos_y = 50 - SPRITE_HEIGHT;
  r = 5;

  //display.drawBitmap(x, y, spriteName, w, h, color)
  display.drawBitmap(pos_x, pos_y, sprite_NORMAL, SPRITE_WIDTH, SPRITE_HEIGHT, 1);
  display.display();

  button_new = 0;
  button_old = 0;
  state = STATE_REGULAR;
  jump_finished = false;
  sprite_state = 2; //NORMAL
}

void loop() {

  if (digitalRead(BUTTON_PIN_LEFT)) {
    display.clearDisplay();
    pos_x = pos_x - MOVE_SPEED;
    sprite_state = 1;
  }

  if (digitalRead(BUTTON_PIN_RIGHT)) {
    display.clearDisplay();
    pos_x = pos_x + MOVE_SPEED;
    sprite_state = 4;
  }

  button_new = digitalRead(BUTTON_PIN_UP);
  if (((button_new != button_old && button_new == 1) || ((button_new != button_old && button_new == 1) && (digitalRead(BUTTON_PIN_RIGHT) || digitalRead(BUTTON_PIN_LEFT)))) && jump_finished == true) {
    jump_finished = false;
    pos_y_original = pos_y;
    state = STATE_JUMP_UP;
  }
  switch(state) {
    case STATE_JUMP_UP:
      display.clearDisplay();
      sprite_state = 3;
      if (pos_y <= pos_y_original - JUMP_HEIGHT) {
        state = STATE_JUMP_DOWN;
      }
      else {
        pos_y = pos_y - JUMP_SPEED;
      }
    break;

    case STATE_JUMP_DOWN:
      display.clearDisplay();
      if (pos_y == pos_y_original) {
        state = STATE_REGULAR;
        sprite_state = 2;
      }
      else {
        pos_y = pos_y + JUMP_SPEED;
        sprite_state = 0;
      }
    break;

    case STATE_REGULAR:
      jump_finished = true;
    break;
  }
  button_old = button_new;

  if (!digitalRead(BUTTON_PIN_RIGHT) && !digitalRead(BUTTON_PIN_LEFT) && !digitalRead(BUTTON_PIN_UP)) {
    display.clearDisplay();
    if (state == STATE_JUMP_UP) {
      sprite_state = 3;
    }
    else if (state == STATE_JUMP_DOWN) {
      sprite_state = 0;
    }
    else {
      sprite_state = 2;
    }
  }

  display.drawBitmap(pos_x, pos_y, sprite_allArray[sprite_state], SPRITE_WIDTH, SPRITE_HEIGHT, 1);
  display.display();
}
