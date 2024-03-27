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
    if (items[i].message.length() > 16)
    {
      for (int j = 0; j <= items[i].message.length() - 15; j++)
      {
        lcd.setCursor(items[i].cursorX, items[i].cursorY);
        lcd.print(items[i].message.substring(j, j + 16 - items[i].cursorX));
        delay(500); // Adjust the delay to control the speed of the scrolling
      }
    }
    else
    {
      lcd.setCursor(items[i].cursorX, items[i].cursorY);
      lcd.print(items[i].message);
    }
  }
}

void displayMessage(const String& line1, const String& line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);

  // display the message on the second line

  // Check if the message is longer than 16 characters
  if (line2.length() > 16)
  {
    for (int j = 0; j <= line2.length() - 15; j++)
    {
      lcd.setCursor(0, 1);
      lcd.print(line2.substring(j, j + 16));
      delay(500); // Adjust the delay to control the speed of the scrolling
    }
    delay(1000);
  }
  else
  {
    // Calculate the number of spaces needed to center the text
    int spaces = (16 - line2.length()) / 2;
    // Add the spaces to the beginning of the string
    String spacedLine2 = line2;
    for (int i = 0; i < spaces; i++)
    {
      spacedLine2 = " " + spacedLine2;
    }
    // Display the message
    lcd.setCursor(0, 1);
    lcd.print(line2);
    delay(3000); // Display the message for 3 seconds
  }
}
