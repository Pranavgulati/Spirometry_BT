 /*
*This program sends the sensor data values by computing pressure
*to Bluetooth device
 */

/*
*The part chosen mpx2102dp is a differential pressure sensor 
*it send the pressure difference between the two prongs to 
*the voltage pins
*the construction of the spirometer should be such that it records this difference
*Please discuss the hardware available for a better understanding of its constraints
 */
#include <SoftwareSerial.h>
#define RXPIN 3
#define TXPIN 4
#define V1PIN 19 //A5 pin on the arduino UNO V+pin of sensor
#define V2PIN 18 //A4 pin on the arduino UNO V-pin of sensor
#define TIME_PERIOD 500 //time periodof sampling in milliseconds
#define DELIMITER '\n'
#define SEPARATOR ','
//WARNING
//please power the sensor with the 5V vcc only
//since over voltage can damage input pins
//Please ensure common grounding of sensor
#define COMM_SPEED 115200
#define DEBUG_SPEED 115200
#define USE_SERIAL Serial

//GLOBALS
SoftwareSerial BT(RXPIN,TXPIN);
byte transmissionStatus =0;

void setup() {
Serial.begin(DEBUG_SPEED);
BT.begin(COMM_SPEED);
}

void loop() {
  if(USE_SERIAL.available()>0){
    transmissionStatus=(byte)USE_SERIAL.read()-48;
    }
  else if(transmissionStatus==1){
    int P1=analogRead(V1PIN);
    int P2=analogRead(V2PIN);
    float diff=((float)(P2-P1))*(5/1024); //P1 corresponds to vacuum/low pressure side acc to datasheet
    float pressure=diff*0.03; //pressure in kPa kiloPascal
    USE_SERIAL.print(pressure);
    USE_SERIAL.print(DELIMITER);
   }
   delay(TIME_PERIOD);
}
