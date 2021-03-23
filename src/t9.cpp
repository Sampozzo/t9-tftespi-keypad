#include "t9.h"

#include <Arduino.h>

int8_t xj, yj, bj;

#define color1 0x026A
#define color2 0xBAC0

int n = 4;
int m = 3;
int posX[12];
int posY[12];

int fromTop = 25;
int fromLeft = 2;
int boxW = 39;
int boxH = 30;
int space = 3;
char buttons[4][3] = {
    {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};
String letters[4][3] = {{" ", "abc", "def"},
                        {"ghi", "jkl", "mno"},
                        {"pqrs", "tuv", "wxyz"},
                        {"", "", ""}};

char lastChar;
int tx;
int ty;
char buf[100];
uint8_t lastKey;

void t9Draw(TFT_eSPI* tft) {
  tft->fillScreen(TFT_WHITE);
  tft->setSwapBytes(true);
  tft->setTextWrap(true);
  tft->setTextColor(TFT_WHITE);
  for (int i = 0; i < n; i++) {
    posY[i] = fromTop + (boxH * i) + (space * i);
    for (int j = 0; j < m; j++) {
      posX[j] = fromLeft + (boxW * j) + (space * j);
      tft->fillRoundRect(posX[j], posY[i], boxW, boxH, 3, color1);
      tft->drawString(String(buttons[i][j]), posX[j] + 4, posY[i] + 2, 2);
      tft->drawString(letters[i][j], posX[j] + 4, posY[i] + 20, 1);
    }
  }
}

void keyPressed(TFT_eSPI* tft) {
  tft->fillRoundRect(posX[tx], posY[ty], boxW, boxH, 3, color2);
  tft->setTextColor(TFT_WHITE);
  tft->drawString(String(buttons[ty][tx]), posX[tx] + 4, posY[ty] + 2, 2);
  tft->drawString(letters[ty][tx], posX[tx] + 4, posY[ty] + 20, 1);
  delay(100);
  tft->fillRoundRect(posX[tx], posY[ty], boxW, boxH, 3, color1);
  tft->setTextColor(TFT_WHITE);
  tft->drawString(String(buttons[ty][tx]), posX[tx] + 4, posY[ty] + 2, 2);
  tft->drawString(letters[ty][tx], posX[tx] + 4, posY[ty] + 20, 1);
  tft->fillRect(0, 0, 128, 24, TFT_WHITE);
  tft->setTextColor(TFT_BLACK, TFT_WHITE);
  int sumX = tft->drawString(buf, 5, 5, 2);
  tft->setTextColor(TFT_YELLOW, TFT_BLUE);
  tft->drawString(&lastChar, sumX + 5, 5, 2);
}

String t9(TFT_eSPI* tft, I2CKeyPad* keypad) {
  memset(buf, 0, sizeof buf);
  t9Draw(tft);
  boolean loop = true;
  while (loop) {
    uint8_t key = keypad->getKey();
    if (key != lastKey && keypad->isPressed() && key < 16) {
      char keys = (char)"123A456B789C*0#DNF"[key];
      Serial.println(key);
      boolean write = true;
      if (keys == '1') {
        lastChar = '1';
        tx = 0;
        ty = 0;
      } else if (keys == '2') {
        if (lastChar == 'a') {
          lastChar = 'b';
        } else if (lastChar == 'b') {
          lastChar = 'c';
        } else if (lastChar == 'c') {
          lastChar = '2';
        } else {
          lastChar = 'a';
        }
        tx = 1;
        ty = 0;
      } else if (keys == '3') {
        if (lastChar == 'd') {
          lastChar = 'e';
        } else if (lastChar == 'e') {
          lastChar = 'f';
        } else if (lastChar == 'f') {
          lastChar = '3';
        } else {
          lastChar = 'd';
        }
        tx = 2;
        ty = 0;
      } else if (keys == '4') {
        if (lastChar == 'g') {
          lastChar = 'h';
        } else if (lastChar == 'h') {
          lastChar = 'i';
        } else if (lastChar == 'i') {
          lastChar = '4';
        } else {
          lastChar = 'g';
        }
        tx = 0;
        ty = 1;
      } else if (keys == '5') {
        if (lastChar == 'j') {
          lastChar = 'k';
        } else if (lastChar == 'k') {
          lastChar = 'l';
        } else if (lastChar == 'l') {
          lastChar = '5';
        } else {
          lastChar = 'j';
        }
        tx = 1;
        ty = 1;
      } else if (keys == '6') {
        if (lastChar == 'm') {
          lastChar = 'n';
        } else if (lastChar == 'n') {
          lastChar = 'o';
        } else if (lastChar == 'o') {
          lastChar = '6';
        } else {
          lastChar = 'm';
        }
        tx = 2;
        ty = 1;
      } else if (keys == '7') {
        if (lastChar == 'p') {
          lastChar = 'q';
        } else if (lastChar == 'q') {
          lastChar = 'r';
        } else if (lastChar == 'r') {
          lastChar = 's';
        } else if (lastChar == 's') {
          lastChar = '7';
        } else {
          lastChar = 'p';
        }
        tx = 0;
        ty = 2;
      } else if (keys == '8') {
        if (lastChar == 't') {
          lastChar = 'u';
        } else if (lastChar == 'u') {
          lastChar = 'v';
        } else if (lastChar == 'v') {
          lastChar = '8';
        } else {
          lastChar = 't';
        }
        tx = 1;
        ty = 2;
      } else if (keys == '9') {
        if (lastChar == 'w') {
          lastChar = 'x';
        } else if (lastChar == 'x') {
          lastChar = 'y';
        } else if (lastChar == 'y') {
          lastChar = 'z';
        } else if (lastChar == 'z') {
          lastChar = '9';
        } else {
          lastChar = 'w';
        }
        tx = 2;
        ty = 2;
      } else if (keys == '0') {
        lastChar = '0';
        tx = 0;
        ty = 0;
      } else if (keys == 'A') {
        loop = false;
        write = false;
      } else if (keys == 'D') {
        strcat(buf, &lastChar);
        lastChar = ' ';
      } else if (keys == 'C') {
        buf[strlen(buf) - 1] = '\0';
      } else {
        write = false;
      }
      if (write) {
        keyPressed(tft);
      }
    }
    lastKey = key;
  }
  return (String)buf;
}