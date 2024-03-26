#ifndef WATERPLANTS_H
#define WATERPLANTS_H

#include <Arduino.h>
#include "readWaterLevels.h"
#include "pumpControl.h"
#include "lcdController.h"
#include "refillTank.h"
#include "persistentRefillMessage.h"

void waterPlants(int wateringDuration);

#endif
