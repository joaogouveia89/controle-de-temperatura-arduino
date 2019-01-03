/********************************************************************/
// First we include the libraries
#include <SoftwareSerial.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include "framework/temperature_list.h"

#define ONE_WIRE_BUS 2
#define TEMPERATURE_SENSOR_RX 6
#define TEMPERATURE_SENSOR_TX 7
#define LIST_SIZE 100
#define ERROR_MARGIN 0.5

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);

SoftwareSerial hm10Serial(TEMPERATURE_SENSOR_RX, TEMPERATURE_SENSOR_TX);

float temperature;
int parteInteira;
int parteDecimal;
int sensorStatus = NOT_CALIBRATED;
int measures = 0;
TList* temperatures = NULL;


void setup(void)
{
  // start serial port
  Serial.begin(9600);
}
void loop(void)
{
  if (sensorStatus == NOT_CALIBRATED) {
    sensor.requestTemperatures();
    temperature = sensor.getTempCByIndex(0);
    if (measures == LIST_SIZE) {
      temperatures = popTemperature(temperatures);
    } else {
      measures++;
    }
    temperatures = add(temperatures, temperature);
    sensorStatus = checkCalibration(temperatures, ERROR_MARGIN, LIST_SIZE);
  }else{
    Serial.println("CALIBRATED");
  }

//  if (hm10Serial.available()) {
//    int val = hm10Serial.read();
//    if (val == 100) {
//      parteInteira = temperature;
//      parteDecimal = ((float)temperature - parteInteira) * 100;
//      Serial.println(temperature);
//      hm10Serial.write(parteInteira);
//      delay(1000);
//      hm10Serial.write(parteDecimal);
//    }
//  }
}
