#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>  // include i/o class header
#include <cmath>
#include "customChars.h"


#define lcdPowerPin 10

struct DisplayItem {
  int cursorX;
  int cursorY;
  String message;
};

void multiPrint(DisplayItem* items, int itemCount);
void toggleLCDPower(bool powerOn);
void displayMessage(const String& line1, const String& line2);

extern hd44780_I2Cexp lcd;

#endif
