
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <SPI.h>
#include <SD.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor 

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

    while (1);
  }

}

void writeError() {

}

void writeData(float temperature, float humidity) {
  tmElements_t tm;
  if (RTC.read(tm)) {

    myFile = SD.open("balcony.csv", FILE_WRITE);
    Serial.print(temperature);
    Serial.println(humidity);
    myFile.print("20");
    int year = tmYearToCalendar(tm.Year);
    myFile.print(year, DEC);
    myFile.print("-");
    Serial.print(year);
    int month = tm.Month;
    if (month < 10) {
      myFile.print("0");
    }
    myFile.print(month, DEC);
    myFile.print("-");
    int day = tm.Day;
    if (day < 10) {
      myFile.print("0");
    }
    myFile.print(day, DEC);
    myFile.print(" ");
    int hours = tm.Hour;
    int minutes = tm.Minute;
    int seconds = tm.Second;
    if (hours < 10) {
      myFile.print("0");
    }
    myFile.print(hours, DEC); //24-hr
    myFile.print(":");
    if (minutes < 10) {
      myFile.print("0");
    }
    myFile.print(minutes, DEC);
    myFile.print(":");
    if (seconds < 10) {
      myFile.print("0");
    }
    myFile.print(seconds, DEC);
    myFile.print(",");
    myFile.print(temperature);
    myFile.print(",");
    myFile.println(humidity);
    myFile.close();
  }

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
    Serial.println("Error brainwave overload");

  }
  else {
    writeData(temperature, humidity);


  }

  delay(1800000L);



}


// put your main code here, to run repeatedly:
