
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Define the I2C address. The default is 0x76. Check your sensor for other possible addresses.
#define BME280_ADDRESS 0x76 

#define SDA 19 
#define SCL 23

// Create an instance of the BME280 sensor
Adafruit_BMP280 bmp;

// Variable to store delay between readings
unsigned long delayTime;

void setup() {

  
Wire.begin(SDA, SCL);

  Serial.begin(115200);
  while (!Serial);  // Wait for serial to be available
  Serial.println(F("BM280 test"));

  // Initialize the BME280 sensor
  if (!bmp.begin(BME280_ADDRESS)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  
  Serial.println("-- Default Test --");
  delayTime = 1000; // 1 second delay between readings
}

void loop() { 
  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure() / 100.0F);
  Serial.println(" hPa");

 
  Serial.println();
}