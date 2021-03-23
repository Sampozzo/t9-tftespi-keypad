#ifndef T9_H
#define T9_H
#include <Arduino.h>
#include <Keypad.h>
#include <TFT_eSPI.h>
#include "I2CKeyPad.h"

void t9Draw(TFT_eSPI* tft);
void keyPressed(TFT_eSPI* tft);
String t9(TFT_eSPI* tft, I2CKeyPad* keypad);
#endif