#include "waterPlants.h"
#include "lcdController.h"

const int buttonPin = 7;  // the number of the pushbutton pin

unsigned long lastButtonPressTime = 0;
int selectedDuration = 0;
bool isStarted = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // initialize the pushbutton pin as an input with pullup resistor
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // read the state of the pushbutton value

  if (buttonState == LOW) {
    if (!isStarted) {
      toggleLCDPower(true);
      isStarted = true;
    }
    selectedDuration += 10;
    if (selectedDuration > 60) {
      selectedDuration = 0;  // 0 represents the cancel option
    }
    lastButtonPressTime = millis();
    DisplayItem item;
    if (selectedDuration == 0) {
      item = { 0, 0, "Cancel" };
    } else {
      item = { 0, 0, "Duration: " + String(selectedDuration) };
    }
    multiPrint(&item, 1);
  }

  if (isStarted && millis() - lastButtonPressTime > 3000) {  // 3 seconds have passed
    if (selectedDuration != 0) {
      startWatering(selectedDuration);
    }
    isStarted = false;  // go back to waiting for a button press
    toggleLCDPower(false);
    selectedDuration = 0;  // reset to the initial value
  }
  delay(500);  // delay to avoid button debouncing
}
