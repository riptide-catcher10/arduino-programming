#include <Adafruit_PCT2075.h>

float temp = 0;

Adafruit_PCT2075 PCT2075;

void setup() {
  PCT2075 = Adafruit_PCT2075();

  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }
  Serial.println("Adafruit PCT2075 Test");

  if (!PCT2075.begin()) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  
  Serial.println("Found PCT2075 chip");

}

void loop() {
  temp = PCT2075.getTemperature() * 1.8 + 32;
  Serial.print("Temperature: "); Serial.print(temp);Serial.println(" f");
  delay(1000);
}
