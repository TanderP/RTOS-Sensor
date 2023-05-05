#include <Arduino.h>
#include "Wire.h"
#include <WiFi.h>
#include <Wire.h>
#include <BH1750.h>
#include <Ticker.h>
#include <DHTesp.h>


#define DHT_PIN 18
#define DHT_TYPE DHTesp::DHT11
#define OLED_RESET -1

BH1750 lightMeter ;
DHTesp dht;
WiFiClient espClient;
// Matthew Filbert Tander
// 2501994241
// ESP32-DEvkit V4
//Upesy wroom

float temp, hum, lux;
String condition;
//xyz = 241
//x = temp
//y = hum
//z = lux

void humRead(void *pvParameters){ //Y
  while(1){

   hum = dht.getHumidity(); // read humidity
    
  vTaskDelay(4000 / portTICK_PERIOD_MS);}
   //}
  
}
void sensorDisplay(void *pvParameters){
  while (1) {

   Serial.printf("Serial Monitor : Lux = %.2f lx || Temperature  : %.2f | Humidity : %.2f\n", lux, temp, hum);
   if(lux >=400 ){
    
   condition = "WARNING!";
   Serial.printf("WARNING, 2501994241, %.2f lx\n", lux);
  }
  else
  { Serial.printf("CLOSED, 2501994241, %.2f lx\n", lux);
  condition = "CLOSED";}

   
  vTaskDelay(1000 / portTICK_PERIOD_MS);}
   //
}
void tempRead(void *pvParameters){//X
   int failedCount = 0;
  const int maxFailedCount = 5; // maximum number of consecutive failures before setting temp to NaN
  while(1) {
    float tempRead = dht.getTemperature();
    if(!isnan(tempRead)) { // check if data was successfully read
      temp = tempRead; // update temp if data was successfully read
      failedCount = 0; // reset failure count
    }
    else {
      failedCount++; // increment failure count
      if (failedCount >= maxFailedCount) {
        temp = NAN; // set temp to NaN if there have been too many consecutive failures
        failedCount = 0; // reset failure count
      }
    }
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  }}
void luxRead(void *pvParameters){//Z
  while(1){
  lux = lightMeter.readLightLevel();
  vTaskDelay(1000 / portTICK_PERIOD_MS);}
}


  void setup() {
Serial.begin(115200);
 
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
    lightMeter.begin();
  dht.setup(DHT_PIN, DHT_TYPE);

  xTaskCreatePinnedToCore(humRead, "sensorRead", 2044, NULL, 1, NULL, 0);
 xTaskCreatePinnedToCore(tempRead, "Temperature", 2044, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(luxRead, "luxRead", 2044, NULL, 1, NULL, 0);
 xTaskCreatePinnedToCore(sensorDisplay, "sensorDisplay", 2044, NULL, 1, NULL, 0);

// xTaskCreatePinnedToCore(function, "function", 2048, NULL, 1, NULL, 0);

  // put your setup code here, to run once:
}
void loop() {

  // put your main code here, to run repeatedly:
}
