/* 

The objective of this code if to sense the soil moisture through a capacitive soil moisture sensor and send it to a cloud service platform "ThingSpeak" 


/*information and pin connections:

- The I2C bus for the 1st BMP180 sensor and the LCD screen is: 
                                   SCL ----> 22
                                   SDA ----> 21
                                   

- the capacitive soil moisture sensor is connected to pin number            
*/

#include "ThingSpeak.h" //This is the Library for the cloud data website "ThingSpeak"
#include "secrets.h"  //this file contains the WiFi network information
#include <WiFi.h> //The library for Wifi connection 


char ssid[] = SECRET_SSID;   // your network SSID (WiFi network name) from secrets
char password[] = SECRET_PASS;   // your network password from secrets

WiFiClient  client; 

unsigned long myChannelNumber = SECRET_CH_ID; //ThisngSpeak channel ID added to secrets
const char * myWriteAPIKey = SECRET_WRITE_APIKEY; //ThisngSpeak channel Write API key in Secrets

int SMS = 34;
int SMS_Aalog;
int SMS_Val;
int interval = 1000;


void setup() {
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor

   pinMode(SMS, INPUT),

   WiFi.mode(WIFI_STA);   //seting the ESP32 to station status
  ThingSpeak.begin(client);  // Initialize ThingSpeak 
  
 if(WiFi.status() != WL_CONNECTED){  //this whole part is to check if the ESP32 is connected to the WiFi network
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);  
      Serial.print(".");
      delay(3000);     
    } 
    Serial.println("\nConnected.");
 }
  

}

void loop() { 
 SMS_Aalog= analogRead(SMS); 
 SMS_Val= map( SMS_Aalog, 3056, 1050, 0, 100);


  Serial.print("Analog Read from the sensor = ");
  Serial.println(SMS_Aalog);
  Serial.println("----------------------------------------");
  Serial.println("----------------------------------------");

   ThingSpeak.setField(2, SMS_Val); //send the data to the selected field in ThingSpeak if you have more than one data point set the field below in each line
      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); //convert evrything to integer and send it.
  delay(interval);


  if (WiFi.status()!= WL_CONNECTED){
    delay(5000);
 
    ESP.restart();
}
 

}
