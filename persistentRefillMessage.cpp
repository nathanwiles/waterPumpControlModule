#include "persistentRefillMessage.h"

void displayRefillMessage()
{
  int *waterLevelSensorValues = readWaterLevelSensors();
  WaterLevels levels = getReservoirLevels(waterLevelSensorValues);

  while (levels.reserveLevel == "E")
  {
    displayMessage("Reserve Tank:", "Empty");
    delay(2000);
    displayMessage("Reserve Tank:", "Needs Refill")
    delay(2000);
    waterLevelSensorValues = readWaterLevelSensors();
    levels = getReservoirLevels(waterLevelSensorValues);
  }
  displayMessage("Reserve Tank:", "Full");
  delay(2000);
  displayMessage("Reserve Tank:", "Thanks! you're a lifesaver!");
  delay(2000);
}
