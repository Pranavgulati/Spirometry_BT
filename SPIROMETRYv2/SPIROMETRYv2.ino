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
#define SEPARATOR ','
//WARNING
//please power the sensor with the 5V vcc only
//since over voltage can damage input pins
//Please ensure common grounding of sensor
#define COMM_SPEED 19200
//  #define COMM_SPEED 9600
//  #define COMM_SPEED 115200
#define DEBUG_SPEED 115200
#define USE_SERIAL BT
#define DEBUG 1
//GLOBALS
SoftwareSerial BT(RXPIN,TXPIN);
byte transmissionStatus =0;

void setup() {
Serial.begin(DEBUG_SPEED);
BT.begin(COMM_SPEED);
}
float getData(int P1,int P2){
  if(DEBUG){return P1;}
  else{
    //PLEASE DO the MATH with the sensor vaules here as per your requirements
    //float diff=((float)(P2-P1))*(5/1024); //P1 corresponds to vacuum/low pressure side acc to datasheet
    //float pressure=diff*0.03; //pressure in kPa kiloPascal
    float diff=((float)(P2-P1)); //P1 corresponds to vacuum/low pressure side acc to datasheet
    float pressure=diff; //pressure in kPa kiloPascal
    return pressure;
    }
  }
  
void loop() {
  if(USE_SERIAL.available()>0){
    transmissionStatus=(byte)USE_SERIAL.read()-48;
    }
  else if(transmissionStatus==1){
    int P1=analogRead(V1PIN);
    int P2=analogRead(V2PIN);
    USE_SERIAL.print(getData(P1,P2));
    USE_SERIAL.print(SEPARATOR);
    if(DEBUG){Serial.print(getData(P1,P2));
    Serial.print(SEPARATOR);
    }
   }
   delay(TIME_PERIOD);
}
