#include "refillTank.h"

void refillTank() {
  // define the water level sensor values
  WaterLevels levels = getReservoirLevels();

  // Handle the case where the reserve tank is empty
  if (levels.reserveLevel == "E") {
    displayRefillMessage();
    refillTank();
  };

  // Handle the case where the main tank is full
  if (levels.mainLevel == "F") {
    displayMessage("Main Tank:", "Already Full!");
    delay(2000);
  };

  // Handle the case where the main tank is not full and the reserve tank is full
  if (levels.mainLevel != "F" && levels.reserveLevel == "F") {
    // Refill the main tank
    turnOnRefillPump();
    displayMessage("Main Tank:", "Refilling");
    do {
      // refresh the water level sensor values
      levels = getReservoirLevels();

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

        while (digitalRead(4) == HIGH) {
          displayMessage("ALERT:", "Overflow Detected");
          delay(500);
          lcd.clear();
        }

        displayMessage("Overflow Cleared", "Resuming");
        delay(3000);
        displayMessage("Main Tank:", "Refilling");
        turnOnRefillPump();
      }

      if (levels.reserveLevel == "E") {
        // If the reserve tank is empty, stop refilling and display the message
        turnOffRefillPump();
        displayRefillMessage();
        displayMessage("Main Tank:", "Refilling");
        turnOnRefillPump();
      }

    } while (levels.mainLevel != "F");
    // Stop the refill pump and display the message
    turnOffRefillPump();
    displayMessage("Main Tank:", "Full");
    delay(3000);
  }
}
