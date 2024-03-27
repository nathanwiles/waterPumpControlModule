#include "pumpControl.h"

const int MAIN_PUMP_PIN = 20;
const int REFILL_PUMP_PIN = 21;

void setupPumpControl() {
  pinMode(MAIN_PUMP_PIN, OUTPUT);
  pinMode(REFILL_PUMP_PIN, OUTPUT);
  digitalWrite(MAIN_PUMP_PIN, HIGH);
  digitalWrite(REFILL_PUMP_PIN, HIGH);
}

void turnOnMainPump() {
  digitalWrite(MAIN_PUMP_PIN, LOW);
}

void turnOnRefillPump() {
  digitalWrite(REFILL_PUMP_PIN, LOW);
}

void turnOffMainPump() {
  digitalWrite(MAIN_PUMP_PIN, HIGH);
}

void turnOffRefillPump() {
  digitalWrite(REFILL_PUMP_PIN, HIGH);
}
