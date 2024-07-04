

#include <Wire.h> 
#include <BH1750.h>


#define SDA 19 
#define SCL 23


BH1750 lightMeter;

void setup(){

  
Wire.begin(SDA, SCL);

  Serial.begin(115200); 

  Wire.begin();   // Initialize the I2C bus 

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}