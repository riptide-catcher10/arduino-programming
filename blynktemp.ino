#define BLYNK_TEMPLATE_ID "TMPLH9QFIMnn"
#define BLYNK_DEVICE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "MAqejAGJwymEvVIpZudAScBrAuiKGyqf"

#include <Wire.h>
#include "SparkFunBME280.h"
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

//WiFi network name and password:
// The barn at chapel Hill WIFI
//const char * ssid = "CenturyLink0605";
//const char * pass = "e3au6c77387dwd";
// The Thelen House wifi
const char * ssid = "mavy.farm";
const char * pass = "maverick";

BME280 mySensor;
BlynkTimer timer;

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Reading basic values from BME280");
  initWiFi();
 
  Blynk.config(BLYNK_AUTH_TOKEN);
  
  Wire.begin();
  while (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    delay(2000);
  }
  
  // Setup a function to be called every second
  timer.setInterval(3000L, sendSensor);

}

void loop()
{
  
  
  while (Blynk.connect() == false) {
     Serial.println("Blynk is not connected");
     unsigned long currentMillis = millis();
     if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
        Serial.print(millis());
        Serial.println("Reconnecting to WiFi...");
        WiFi.begin(ssid, pass);
        previousMillis = currentMillis;
     }
    
     delay(10000);
  }
  Blynk.run();
  timer.run();
}

void sendSensor() {
    float tempF = mySensor.readTempF();
    float h = mySensor.readFloatHumidity();
    //Serial.print("Temp:");Serial.println(temp);
    //Serial.print("Humidity:");Serial.println(h);
    Blynk.virtualWrite(V5, h); // select your virtual pins accordingly
    Blynk.virtualWrite(V6, tempF); // select your virtual pins accordingly
    
}
