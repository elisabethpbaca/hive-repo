

//lightstart
int lightPin = A1; // select the input pin for the potentiometer
// Min 0
// Max 1024
//300 is dark and 900 is bright room 
//lightend

//water begin
#define WATER_SENSOR 7


#include <SPI.h>
#include "RF24.h"

byte addresses[][6] = {"1Node","2Node"};


/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(9,10);
/**********************************************************/


// Used to control whether this node is sending or receiving
bool role = 1;


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
  pinMode(WATER_SENSOR, INPUT);

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



// sensor code goes here 
void loop() {
  
  SensorData myData;
  
  //water start
  if(digitalRead(WATER_SENSOR) == HIGH)
  {
    myData.water = true;
  } else {
    myData.water = false;
  }
 
//water end
// light code
  
  myData.lightSensorValue =  analogRead(lightPin); 
 // end light code 
  
  //soil
int soil_moisture=analogRead(A3);  // read from analog pin A3
myData.soil = soil_moisture;
//soil end
  myData.beeName =1;  
  
/****************** Ping Out Role ***************************/  
if (role == 1)  {
    
    radio.stopListening();                                    // First, stop listening so we can talk.
    
    
    Serial.println(F("Now sending"));
  myData._micros = micros();
     if (!radio.write( &myData, sizeof(myData) )){
       Serial.println(F("failed due to write"));
       Serial.print("beename:");
       Serial.println(myData.beeName);
     }
    // Serial.print(F("Size of myData: "));
   //  Serial.println(sizeof(myData));
       
    radio.startListening();                                    // Now, continue listening
    
    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
    
    while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
    }

        
        // Spew it
 
        Serial.print(F("lightsensorValue: "));
        Serial.println(myData.lightSensorValue);
        Serial.print(F("Water Sensor: "));
        Serial.println(myData.water);
        Serial.print(F("soil sensor :"));
        Serial.println(myData.soil); 
        //Serial.print(F(", Size of myData: "));
        //Serial.println(sizeof(myData));
    //}

    // Try again 1s later
    delay(1000);
  }

} // Loop

