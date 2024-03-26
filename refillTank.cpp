#include "refillTank.h"


void refillTank()
{
  // define the water level sensor values
  int *waterLevelSensorValues = readWaterLevelSensors();
  WaterLevels levels = getReservoirLevels(waterLevelSensorValues);

  if (levels.mainLevel != "F" && levels.reserveLevel == "F")
  {
    // Refill the main tank
      turnOnRefillPump();
      displayMessage("Main Tank:", "Refilling");
    do
    {
      // refresh the water level sensor values
      waterLevelSensorValues = readWaterLevelSensors();
      levels = getReservoirLevels(waterLevelSensorValues);

      // Check if the overflow sensor is triggered
      if (digitalRead(4) == HIGH)
      // stop refilling and display the message
      {
        displayMessage("ALERT:", "Overflow Detected");
        turnOffRefillPump();
        displayMessage("Main Tank:", "Purging Excess Water");
        turnOnMainPump();
        delay(5000);
        turnOffMainPump();

        while (digitalRead(4) == HIGH)
        {
          displayMessage("ALERT:", "Overflow Detected");
          delay(500);
          lcd.clear();
        }

        displayMessage("Overflow Cleared", "Resuming");
      }

      if (levels.reserveLevel == "E")
      {
        // If the reserve tank is empty, stop refilling and display the message
        turnOffRefillPump();
        displayMessage("Reserve Tank:", "Empty");
        delay(5000);
        return;
      }
      delay(500);
    } while (levels.mainLevel != "F");
    // Stop the refill pump and display the message
    turnOffRefillPump();
    displayMessage("Main Tank:", "Full");
    delay(5000);
    return;
  }
}
