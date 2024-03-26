#ifndef WATERPLANTS_H
#define WATERPLANTS_H

#include <Arduino.h>
#include "readWaterLevels.h"
#include "pumpControl.h"
#include "lcdController.h"
#include "refillTank.h"
#include "persistentRefillMessage.h"

int waterPlants(int wateringDuration);
void startWatering(int wateringDuration);

#endif
