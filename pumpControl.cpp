#include "pumpControl.h"

void turnOnMainPump() {
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
}

void turnOnRefillPump() {
  pinMode(21, OUTPUT);
  digitalWrite(21, LOW);
}

void turnOffMainPump() {
  pinMode(20, OUTPUT);
  digitalWrite(20, HIGH);
}

void turnOffRefillPump() {
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
}
