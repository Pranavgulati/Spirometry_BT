 /*
*This program sends the sensor data values directly
*to Bluetooth device
 */
#include <SoftwareSerial.h>
#define RXPIN 3
#define TXPIN 4
#define V1PIN 19 //A5 pin on the arduino UNO V+pin of sensor
#define V2PIN 18 //A4 pin on the arduino UNO V+pin of sensor
#define TIME_PERIOD 500 //time period of sampling in milliseconds
#define DELIMITER ','
#define SEPARATOR ','
//WARNING
//please power the sensor with the 5V vcc only
//since over voltage can damage input pins
//Please ensure common grounding of sensor
#define COMM_SPEED 19200
#define DEBUG_SPEED 115200
#define USE_SERIAL BT

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
    USE_SERIAL.print(analogRead(V1PIN));
    USE_SERIAL.print(SEPARATOR);
    USE_SERIAL.print(analogRead(V2PIN));
    USE_SERIAL.print(DELIMITER);
   }
   delay(TIME_PERIOD);
}
