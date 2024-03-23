#include "readWaterLevels.h"
#include "lcdController.h"

int *readWaterLevelSensors()
{
  static int pinValues[3];
  // configure and read water level sensor pins
  for (int i = 0; i < 3; i++)
  {
    pinMode(i, INPUT);
    pinValues[i] = digitalRead(i);
  }
  return pinValues;
}

WaterLevels getReservoirLevels(int pinValues[3])
{
  String mainLevel = pinValues[1] == HIGH ? "F" : pinValues[0] == HIGH ? "P"
                                                                       : "E";
  String reserveLevel = pinValues[2] == LOW ? "E" : "F";

  return WaterLevels{mainLevel, reserveLevel};
}

void monitorWaterLevels(unsigned long duration, unsigned long refreshRate)
{
  toggleLCDPower(true);
  unsigned long startTime = millis();

  while (millis() - startTime < duration)
  {
    int *pinValues = readWaterLevelSensors();

    WaterLevels levels = getReservoirLevels(pinValues);

    String mainLevel = levels.mainLevel;
    String reserveLevel = levels.reserveLevel;

    unsigned long timeLeft = duration - (millis() - startTime);
    String topLine;
    if (timeLeft <= 5000)
    { // If 5 seconds or less are left
      int secondsLeft = timeLeft / 1000 + 1;
      topLine = "Done in: " + String(secondsLeft);
      int spaces = (16 - topLine.length()) / 2; // Calculate the number of spaces needed to center the text
      for (int i = 0; i < spaces; i++)
      { // Add the spaces to the beginning of the string
        topLine = " " + topLine;
      }
    }
    else
    {
      topLine = "Reservoir Lvls:";
    }

    DisplayItem items[] = {
        {0, 0, topLine},
        {0, 1, "Main: " + mainLevel + " Rsrv: " + reserveLevel}};

    multiPrint(items, sizeof(items) / sizeof(DisplayItem));
    delay(refreshRate);
  }
  toggleLCDPower(false);
}
