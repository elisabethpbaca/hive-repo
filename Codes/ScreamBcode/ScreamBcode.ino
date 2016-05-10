//scream b
#include <SPI.h>
#include "RF24.h"
////////////////////////////////////////////////////////////////////////////////////////////
int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 4; // key
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define echoPin 2
#define trigPin 3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
byte addresses[][6] = {"1Node","2Node"};
bool radioNumber = 1;
RF24 radio(9,10);
bool role = 1;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct dataStruct{
    unsigned long _micros;
    int lightSensorValue;
    bool water;
    int beeName;
    int soil;
    int eyes;
    int joystickx;
    int joysticky;
};
  typedef struct dataStruct SensorData;
   SensorData myData;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
    if(radioNumber){
      radio.openWritingPipe(addresses[1]);
      radio.openReadingPipe(1,addresses[0]);
    }else{
      radio.openWritingPipe(addresses[0]);
      radio.openReadingPipe(1,addresses[1]);
    }
  radio.startListening();
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT);
  Serial.begin (9600); // 9600 bps
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
   myData.beeName = 2;
/////////joy/////////////joy//////////////joy/////////////////joy///////////////////joy//////////////////////joy/////////////   
  int x, y, z;
  myData.joystickx = analogRead (JoyStick_X);
  myData.joysticky = analogRead (JoyStick_Y);
  delay (100);
///////RF/////////////////////////RF/////////////////////////////RF//////////////////////////////////RF///////////////////////////////RF//////////////////////////////
   if (role == 1)  {
    radio.stopListening();                                    // First, stop listening so we can talk.
    Serial.println(F("Now sending"));
    myData._micros = micros();
     if (!radio.write( &myData, sizeof(myData) )){
       Serial.println(F("failed due to write"));
     }
    radio.startListening();                                    // Now, continue listening
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }
  }
///////eyes//////////////eyes//////////////////eyes/////////////////////////eyes//////////////////////////////eyes///////////////////////////////////
long duration, distance; // Duration used to calculate distance 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(20); 
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(100); 
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH); //Calculate the distance (in cm) based on the speed of sound.
   distance = duration/58.2;
 //  Serial.println(duration);
   myData.eyes = distance;
 //////// Spew it//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Serial.print(F("eyeSensorValue"));
    Serial.println(myData.eyes);
    Serial.print(F("x"));
    Serial.println(myData.joystickx);
    Serial.print(F("y"));
    Serial.println(myData.joysticky);
    delay(1000);
}
////////
