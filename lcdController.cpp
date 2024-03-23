#include "lcdController.h"
#include "customChars.h"
// Initialize the hd44780_I2Cexp object
hd44780_I2Cexp lcd;

void toggleLCDPower(bool powerOn)
{

  if (powerOn)
  {
    pinMode(lcdPowerPin, OUTPUT); // Set pin 10 as output for power
    digitalWrite(lcdPowerPin, HIGH);
    if (lcd.begin(16, 2)) // LCD columns and rows
    {
      lcd.print("Init Failed");
      delay(4000);
      return; // don't continue
    }
  }

  lcd.createChar(0, water1);
  lcd.createChar(1, water2);
  lcd.createChar(2, water3);
  lcd.createChar(3, water4);
  lcd.createChar(4, water5);
  lcd.createChar(5, water6);
  lcd.createChar(6, water7);
  lcd.createChar(7, water8);


  if (!powerOn)
  {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Good");
    lcd.setCursor(9, 1);
    lcd.print("Bye!");
    delay(1000);
    digitalWrite(lcdPowerPin, LOW);
  }
}

void multiPrint(DisplayItem *items, int itemCount)
{
  lcd.clear();
  for (int i = 0; i < itemCount; i++)
  {
    lcd.setCursor(items[i].cursorX, items[i].cursorY);
    if (items[i].message.length() > 16) {
      for (int j = 0; j <= items[i].message.length() - 15; j++) {
        lcd.setCursor(items[i].cursorX, items[i].cursorY);
        lcd.print(items[i].message.substring(j, j + 16));
        delay(500); // Adjust the delay to control the speed of the scrolling
      }
    } else {
      lcd.print(items[i].message);
    }
  }
}

void displayMessage(const char* line1, const char* line2)
{
  DisplayItem items[2] = {{0, 0, line1}, {0, 1, line2}};
  lcd.clear();
  multiPrint(items, 2);
  delay(3000); // Display the message for 3 seconds
}
