//QUEEN
//////////////lcd///////////////lcd//////////////////lcd//////////////////lcd////////////////////
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
//Connect the LCD: VCC -> 5V, GND -> GND, SDA -> A4 (PortC4, ADC4), SCL -> A5 (PortC5, SDA)
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin,BACKLIGHT_PIN,POSITIVE);
LCD *myLCD = &lcd;
int SENSOR_PIN = 0; // center pin of the potentiometer
char incomingByte;   // for incoming serial data
/////////////RF//////////////////////RF///////////////////////////RF///////////////////////////////RF//////////////////
#include <SPI.h>
#include "RF24.h"
  byte addresses[][6] = {"1Node","2Node"};
  bool radioNumber = 0;
  RF24 radio(9,10);
  bool role = 0;
//////////////DATA//////////////////////////DATA//////////////////////DATA//////////////////
  struct dataStruct{
    unsigned long _micros;
    int lightSensorValue;
    bool water;
    int beeName;
    int soil;
    int sound;
};
  typedef struct dataStruct SensorData;
void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  Serial.begin(9600);
  lcd.begin(16,2);               // initialize the lcd
  lcd.home ();                   // go home
  lcd.print("Hello, BOB ");
  delay(500);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  //myData.value = 0;
  Serial.println("Value set to 0");
  // Start the radio listening for data
  radio.startListening();
}
void loop() 
{
  SensorData myData;
   lcd.clear();
   incomingByte = Serial.read();
   lcd.print(incomingByte);
  if( radio.available()){
                                                           // Variable for the received timestamp
       Serial.println("Listening");

     
      while (radio.available()) {                          // While there is data ready
    //    Serial.println("reading");
        radio.read( &myData, sizeof(myData) );             // Get the payload
      }
 
   if(myData.beeName==1){
      
      Serial.print(F(" lightsensorValue: "));
      Serial.println(myData.lightSensorValue);
      Serial.print(F(" Water Sensor: "));
      Serial.println(myData.water);
      Serial.print(F(" Soil Sensor: "));
      Serial.print(myData.soil);
    
        if(myData.soil<300) {
          Serial.println("Dry soil");
        }
        else if((myData.soil>300)&&(myData.soil<600)) {
          Serial.println("Humid soil");
        }
        else if((myData.soil>600)&&(myData.soil<950)){
          Serial.println( "water");
        }
         else{
          Serial.println ( "ERROR");
        }
      
   }
   else {
   
      Serial.println("Reading:SensorCluser2");
      Serial.print(F(" Sound Sensor Value "));
      Serial.println(myData.sound);
    }
   }
  } 
  //END of loop 
