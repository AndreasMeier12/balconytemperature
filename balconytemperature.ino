
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor 

DS3231 clock1;
File myFile;


bool century = false;
bool h12Flag;
bool pmFlag;
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   Wire.begin();

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
    dht.begin();

    sensor_t sensor;
  dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
 
  Serial.print("Initializing SD card...");
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    dht.begin();

    while (1);
  }
  
}

void writeError() {

}

void writeData(float temperature, float humidity) {
  myFile = SD.open("balcony.csv", 0X04);
      Serial.print(temperature);
    Serial.println(humidity);
      myFile.print("20");
      myFile.print(clock1.getYear(), DEC);
      myFile.print("-");
      myFile.print(clock1.getMonth(century), DEC);
      myFile.print("-");
      myFile.print(clock1.getDate(), DEC);
      myFile.print(" ");
      myFile.print(clock1.getHour(h12Flag, pmFlag), DEC); //24-hr
      myFile.print(":");
      myFile.print(clock1.getMinute(), DEC);
      myFile.print(":");
      myFile.print(clock1.getSecond(), DEC);
      myFile.print(",");
      myFile.print(temperature);
      myFile.print(",");
      myFile.println(humidity);
      myFile.close();
      Serial.println(clock1.getYear(), DEC);

      Serial.println("done");
      


}



void loop() {
  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  float temperature = event.temperature;

                dht.humidity().getEvent(&event);
  float humidity = event.relative_humidity;

  if (isnan(temperature) || isnan(humidity)) {
    //writeError(temperature, humidity)
    Serial.println("Error brainwave overflow");

  }
  else {
    writeData(temperature, humidity);


  }

        delay(1800000L);



}


// put your main code here, to run repeatedly:
