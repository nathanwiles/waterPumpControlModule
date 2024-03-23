#include "waterPlants.h"

bool refillMessageToggle = false;

int waterPlants(int wateringDuration = 30)
{
  DisplayItem items[2]; // Declare items here

  while (true)
  {
    int *waterLevelSensorValues = readWaterLevelSensors();
    WaterLevels levels = getReservoirLevels(waterLevelSensorValues);

    if (levels.reserveLevel == "E" && levels.mainLevel == "E")
    {
      refillMessageToggle = !refillMessageToggle;
      char *emptyItem = "Empty";
      char *refillItem = "Please Refill";
      char *line1 = "Both Tanks:";
      char *line2 = refillMessageToggle ? emptyItem : refillItem;
      displayMessage(line1, line2);
      return wateringDuration;
    }

    if ((levels.mainLevel == "P" || levels.mainLevel == "E") && levels.reserveLevel == "F")
    {
      // Refill the main tank
      do
      {
        turnOnRefillPump();
        displayMessage("Main Tank:", "Refilling");
        waterLevelSensorValues = readWaterLevelSensors();
        levels = getReservoirLevels(waterLevelSensorValues);
        // Check if the overflow sensor is triggered
        if (digitalRead(4) == HIGH)
        {
          turnOffRefillPump();
          turnOnMainPump();
          delay(5000);
          turnOffMainPump();

          while (digitalRead(4) == HIGH)
          {
            displayMessage("ALERT:", "Overflow Detected");
          }

          displayMessage("Overflow Cleared", "Resuming");
        }

        if (levels.reserveLevel == "E")
        {
          // If the reserve tank is empty, stop refilling and display the message
          turnOffRefillPump();
          displayMessage("Reserve Tank:", "Empty");
          // exit (to restart), returning the remaining time
          return wateringDuration;
        }
        delay(500);
      } while (levels.mainLevel != "F");
      // Stop the refill pump and display the message
      turnOffRefillPump();
      displayMessage("Main Tank:", "Full");
    }

    displayMessage("Watering:", "Starting");
    turnOnMainPump();
    int frame = 0; // frame counter for the animation

    for (int i = wateringDuration; i > 0; i--)
    {
      waterLevelSensorValues = readWaterLevelSensors();
      levels = getReservoirLevels(waterLevelSensorValues);
      if (levels.mainLevel == "E")
      {
        turnOffMainPump();
        displayMessage("Main Tank:", "Empty");
        return i; // Return remaining time
      }
      // Display the countdown with the animation
      items[0] = {0, 0, "Watering: "};
      items[1] = {4, 1, String(i) + "s left"};
      lcd.clear();
      multiPrint(items, 2);
      lcd.setCursor(0, 1);
      lcd.write(byte(frame)); // Display the animation
      lcd.setCursor(15, 1);
      lcd.write(byte(frame)); // Display the animation
      delay(1000);

      frame = (frame + 1) % 7; // Increment the frame counter and reset it to 0 when it reaches 8
    }

    turnOffMainPump();
    displayMessage("Watering:", "Complete");

    // display persistent message if the reserve tank is empty
    bool refillNeededFlag = false;
    while (levels.reserveLevel == "E")
    {
      refillNeededFlag = true;
      // check the water levels
      waterLevelSensorValues = readWaterLevelSensors();
      levels = getReservoirLevels(waterLevelSensorValues);
      // toggle the message
      refillMessageToggle = !refillMessageToggle;

      // Display to screen
      DisplayItem emptyItem = {5, 1, "Empty"};
      DisplayItem refillItem = {1, 1, "Please Refill"};
      items[0] = {0, 0, "Reserve Tank:"};
      items[1] = refillMessageToggle ? emptyItem : refillItem;
      lcd.clear();
      multiPrint(items, 2);

      // wait
      delay(2000);
    }
    if (refillNeededFlag) // means the message to refill was displayed at least once
    {
      items[0] = {0, 0, "Reserve Tank:"};
      items[1] = {1, 1, "Thanks! You're a lifesaver!"}; // Replace with your funny message
      lcd.clear();
      multiPrint(items, 2);
      delay(2000);
    }
    return 0; // Return 0 if watering is complete
  }
}

void startWatering(int wateringDuration = 30)
{
  int remainingTime = waterPlants(wateringDuration);
  while (remainingTime > 0)
  {
    remainingTime = waterPlants(remainingTime);
  }
  return;
}
