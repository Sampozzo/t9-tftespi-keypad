#ifndef T9_H
#define T9_H
#include <Arduino.h>
#include <Keypad.h>
#include <TFT_eSPI.h>

void t9Draw(TFT_eSPI* tft);
void keyPressed(TFT_eSPI* tft);
void t9(TFT_eSPI* tft, Keypad* keypad);
#endif