#include "waterPlants.h"

bool refillMessageToggle = false;

void waterPlants(int wateringDuration = 30)
{
  WaterLevels levels = getReservoirLevels();

  // If main tank has water, run pump
  if (levels.mainLevel != "E")
  {
    displayMessage("Watering:", "Starting");
    turnOnMainPump();
  }

  int frame = 0; // frame counter for the animation

  for (int i = wateringDuration; i > 0; i--)
  {
    levels = getReservoirLevels();
    // If main tank runs out, refill, then continue
    if (levels.mainLevel == "E")
    {
      refillTank();
    }

    // Display the countdown with the animation
    displayMessage("Watering:", (i + "s left"));

    // Display the animation frames in 2 places.
    lcd.setCursor(0, 1);
    lcd.write(byte(frame));
    lcd.setCursor(15, 1);
    lcd.write(byte(frame));

    // Increment the frame counter and reset it to 0 when it reaches 8
    frame = (frame + 1) % 7;

    // Delay for 1 second
    delay(1000);
  }

  turnOffMainPump();
  displayMessage("Watering:", "Complete");
  delay(3000);

  // Once watering is complete, refill main tank
  refillTank();

  return; // Return 0 if watering is complete
}
