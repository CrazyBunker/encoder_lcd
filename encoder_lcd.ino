// -----
#include <LiquidCrystal.h>
#include <RotaryEncoder.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define ROTARYSTEPS 10
#define ROTARYMIN 0
#define ROTARYMAX 255
RotaryEncoder encoder(8, 9);
int lastPos = -1;

byte symbol[6][8] = {
  {
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000
  }, {
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000
  }
};

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(57600);
  Serial.println("LimitedRotator example for the RotaryEncoder library.");
  encoder.setPosition(2 / ROTARYSTEPS); // start with the value of 10.
} // setup()

void loop()
{
  lcd.setCursor(4, 1);
  encoder.tick();
  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition() * ROTARYSTEPS;

  if (newPos < ROTARYMIN) {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;

  } else if (newPos > ROTARYMAX) {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  } // if

  if (lastPos != newPos) {
    Serial.print(newPos);
    lcd.print(newPos / 10);
    Serial.println();
    lastPos = newPos;
  } // if
} // loop ()

// The End

