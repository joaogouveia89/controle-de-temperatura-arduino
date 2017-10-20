/********************************************************************/
// First we include the libraries
#include <SoftwareSerial.h>

#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

SoftwareSerial hm10Serial(8, 9); // RX, TX
//// Connect HM10      Arduino Uno
////     Pin 1/TXD          Pin 6
////     Pin 2/RXD          Pin 7
//
float temperature;

void setup(void) 
{ 
 // start serial port 
  Serial.begin(9600);
  hm10Serial.begin(9600);
 
} 
void loop(void) 
{
  int parteInteira;
  int parteDecimal;
  if(hm10Serial.available()){
    int val = hm10Serial.read();
    if(val == 100){
      sensors.requestTemperatures();
      temperature = sensors.getTempCByIndex(0);
      parteInteira = temperature;
      parteDecimal = ((float)temperature-parteInteira)*100;
      Serial.println(temperature);
      hm10Serial.write(parteInteira);
      delay(1000);
      hm10Serial.write(parteDecimal);
    }
    
  }
} 
