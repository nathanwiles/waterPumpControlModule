#ifndef WATERPLANTS_H
#define WATERPLANTS_H

#include <Arduino.h>
#include "readWaterLevels.h"
#include "pumpControl.h"
#include "lcdController.h"

int waterPlants(int wateringDuration);
void startWatering(int wateringDuration);

#endif
