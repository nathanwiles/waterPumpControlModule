#ifndef READWATERLEVELS_H
#define READWATERLEVELS_H

#include <Arduino.h>

struct WaterLevels
{
  String mainLevel;
  String reserveLevel;
};

int* readWaterLevelSensors();
void monitorWaterLevels(unsigned long duration, unsigned long refreshRate);
WaterLevels getReservoirLevels();


#endif
