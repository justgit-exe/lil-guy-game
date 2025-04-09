//~~~ADAFRUIT~~~
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//~~~MOVEMENT~~~
#define JUMP_HEIGHT 25
#define JUMP_SPEED 4
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
  pos_x = 64;
  pos_y = 50;
  r = 5;

  display.drawCircle(pos_x, pos_y, r, WHITE);
  display.display();

  button_new = 0;
  button_old = 0;
  state = STATE_REGULAR;
  jump_finished = false;
}

void loop() {

  if (digitalRead(BUTTON_PIN_LEFT)) {
    display.clearDisplay();
    pos_x = pos_x - MOVE_SPEED;
  }

  if (digitalRead(BUTTON_PIN_RIGHT)) {
    display.clearDisplay();
    pos_x = pos_x + MOVE_SPEED;
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
      }
      else {
        pos_y = pos_y + JUMP_SPEED;
      }
    break;

    case STATE_REGULAR:
      jump_finished = true;
    break;
  }
  button_old = button_new;

  display.drawCircle(pos_x, pos_y, r, WHITE);
  display.display();
}