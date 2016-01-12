
#define WATER_SENSOR 8
#define BUZZER 12

float tempC;
int reading;
int tempPin = 1;

void pins_init()
  {
  pinMode(WATER_SENSOR, INPUT);
  }
  
int sensorPin = A1; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor

//Analog read pins
const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;
//to hold the caculated values
double x;
double y;
double z;
 


void setup(){
//setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup-setup
  
   Serial.begin(9600);
   pins_init();
   analogReference(INTERNAL);
   pinMode(ledPin, OUTPUT);

   }

void loop(){
//loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart-loopstart
  
//soil
    int soil_moisture=analogRead(A1);  // read from analog pin A3
    Serial.print(soil_moisture);
    Serial.print("analog value: ");
  
    if(soil_moisture<300) {
    Serial.println("Dry soil");
    }
    if((soil_moisture>300)&&(soil_moisture<600)) {
    Serial.println("Humid soil");
    }
     if((soil_moisture>600)&&(soil_moisture<950)){
    Serial.println( "water");
    }

//water 
    {
    if(digitalRead(WATER_SENSOR) == HIGH)
    Serial.println("soundAlarm");
    else 
    Serial.println("nope");
    }
//temp
    reading = analogRead(tempPin);
    tempC = reading / 9.31;
    float tempF;
    tempF = (tempC *1.8)+32;
    Serial.println(tempC);
    Serial.println(tempF);
    delay(1000);
//light 
    sensorValue = analogRead(sensorPin);
    digitalWrite(ledPin, HIGH);
    delay(sensorValue);
    digitalWrite(ledPin, LOW);
    delay(sensorValue);
    Serial.println(sensorValue, DEC);
//accelerometer
    //read the analog values from the accelerometer
    int xRead = analogRead(xPin);
    int yRead = analogRead(yPin);
    int zRead = analogRead(zPin);
 
    //convert read values to degrees -90 to 90 - Needed for atan2
    int xAng = map(xRead, minVal, maxVal, -90, 90);
    int yAng = map(yRead, minVal, maxVal, -90, 90);
    int zAng = map(zRead, minVal, maxVal, -90, 90);
 
    //Caculate 360deg values like so: atan2(-yAng, -zAng)
    //atan2 outputs the value of -π to π (radians)
    //We are then converting the radians to degrees
    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
 
    //Output the caculations
    Serial.print("x: ");
    Serial.print(x);
    Serial.print(" | y: ");
    Serial.print(y);
    Serial.print(" | z: ");
    Serial.println(z);
    delay(100);//just here to slow down the serial output - Easier to read

}







