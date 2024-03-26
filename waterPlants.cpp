#include "waterPlants.h"

bool refillMessageToggle = false;

void waterPlants(int wateringDuration = 30)
{
  DisplayItem items[2]; // Declare items here

  int *waterLevelSensorValues = readWaterLevelSensors();
  WaterLevels levels = getReservoirLevels(waterLevelSensorValues);

  // If main tank has water, run pump
  if (levels.mainLevel != "E")
  {
    displayMessage("Watering:", "Starting");
    turnOnMainPump();
  }

  int frame = 0; // frame counter for the animation

  for (int i = wateringDuration; i > 0; i--)
  {
    waterLevelSensorValues = readWaterLevelSensors();
    levels = getReservoirLevels(waterLevelSensorValues);
    // If main tank runs out, refill, then continue
    if (levels.mainLevel == "E")
    {
      refillTank();
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
  delay(5000);

  if levels.reserveLevel == "E"
  {
    displayMessage("Reserve Tank:", "Empty");
    delay(5000);
  }

  // Once watering is complete, refill main tank
  refillTank();
  displayRefillMessage();

  return; // Return 0 if watering is complete
}
