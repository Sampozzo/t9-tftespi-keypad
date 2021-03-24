#include <Arduino.h>
#include <Keypad.h>
#include <TFT_eSPI.h>

#include "I2CKeyPad.h"
#include "t9.h"

TFT_eSPI tft = TFT_eSPI();

const uint8_t KEYPAD_ADDRESS = 0x21;
I2CKeyPad keypad;

void setup() {
  Serial.begin(115200);
  Wire.begin(17, 16);
  Wire.setClock(400000);
  if (keypad.begin(KEYPAD_ADDRESS) == false) {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1)
      ;
  }

  tft.init();          // inizialize tft screen
  tft.setRotation(0);  // set the screen rotation

  // start the t9 loop and get the string
  // from the user input
  String result = t9(&tft, &keypad);

  // print the result on the screen
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.drawString(result, 5, 5, 2);
}

void loop() {}