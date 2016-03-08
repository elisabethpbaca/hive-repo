
/*
* Getting Started example sketch for nRF24L01+ radios
* This is an example of how to send data from one node to another using data structures
* Updated: Dec 2014 by TMRh20
*/


//QUEEN


#include <SPI.h>
#include "RF24.h"

  byte addresses[][6] = {"1Node","2Node"};

  bool radioNumber = 0;

  RF24 radio(9,10);

  bool role = 0;

  struct dataStruct{
    unsigned long _micros;
    int lightSensorValueA;
    bool waterA;
    int lightSensorValueB;
    bool waterB;
    int beeName;
};

  typedef struct dataStruct SensorData;


void setup() {

  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
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




void loop() {
      
  SensorData myData;
  
    if( radio.available()){
                                                           // Variable for the received timestamp
       Serial.println("Listening");

     
      while (radio.available()) {                          // While there is data ready
    //    Serial.println("reading");
        radio.read( &myData, sizeof(myData) );             // Get the payload
      }
 
   if(myData.beeName==1){
      Serial.println("Reading:SensorCluster1");
      Serial.print(F(" lightsensorValue: "));
      Serial.println(myData.lightSensorValueA);
      Serial.print(F(" Water Sensor: "));
      Serial.println(myData.waterA);
   }
   else {
   
      Serial.println("Reading:SensorCluser2");
      Serial.print(F(" lightsensorValue: "));
      Serial.println(myData.lightSensorValueB);
      Serial.print(F(" Water Sensor: "));
      Serial.println(myData.waterB);
    }
   
  }

} // Loop

