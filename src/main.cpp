#include <Arduino.h>
#include <Keypad.h>
#include <TFT_eSPI.h>

#include "t9.h"

TFT_eSPI tft = TFT_eSPI();

///////////////////////////////////////////////////////////////////////////
// KEYBOARD
const int ROW_NUM = 4;     // four rows
const int COLUMN_NUM = 4;  // four columns
char keys[ROW_NUM][COLUMN_NUM] = {{'1', '2', '3', 'A'},
                                  {'4', '5', '6', 'B'},
                                  {'7', '8', '9', 'C'},
                                  {'E', '0', 'F', 'D'}};

byte pin_rows[ROW_NUM] = {26, 27, 14,
                          13};  // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {
    16, 19, 21, 22};  // connect to the column pinouts of the keypad

Keypad keypad =
    Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
///////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(0);
  t9Draw(&tft);
}

void loop() {
  t9(&tft, &keypad);  
}