#include "persistentRefillMessage.h"

// if reservoir is empty, displays a persistent refill message until reservoir is full
void displayRefillMessage()
{
  WaterLevels levels = getReservoirLevels();

  while (levels.reserveLevel == "E")
  {
    displayMessage("Reserve Tank:", "Empty");
    delay(2000);
    displayMessage("Reserve Tank:", "Needs Refill");
    delay(2000);
    levels = getReservoirLevels();
  }
  displayMessage("Reserve Tank:", "Full");
  delay(2000);
  displayMessage("Reserve Tank:", "Thanks! you're a lifesaver!");
}
