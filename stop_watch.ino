
#include <Wire.h>

#include <SerLCD.h> //Click here to get the library: http://librarymanager/All#SparkFun_SerLCD
SerLCD lcd; // Initialize the library with default I2C address 0x72
int button = 13;
bool stopClock = false;
int buttonCounter = 0;
void setup() {
  Wire.begin();

  lcd.begin(Wire); //Set up the LCD for I2C communication

  lcd.setBacklight(255, 255, 255); //Set backlight to bright white
  lcd.setContrast(5); //Set contrast. Lower to 0 for higher contrast.
  pinMode(button,INPUT_PULLUP);
  lcd.clear(); //Clear the display - this moves the cursor to home position as well
}

void loop() {
  // Set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Print the number of seconds since reset:
  if (!stopClock) {
    lcd.print(millis() / 1000);
  }

  if (buttonCounter == 2) {
    stopClock = false;
    buttonCounter = 0;
  }

  if (digitalRead(button) == LOW) {
    stopClock = true;  
    buttonCounter++;
  }
}
