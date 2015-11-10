int sensorPin = A1; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
int buttonpin = 3; // define D0 Sensor Interface
int val = 0;// define numeric variables val
 
void setup () 
{
  pinMode (ledPin, OUTPUT);
  pinMode (buttonpin, INPUT) ;// output interface D0 is defined sensor
  Serial.begin (9600);
}
 
void loop () 
{
  delay(1000);
  sensorValue = analogRead (sensorPin);
  val = digitalRead(buttonpin);// digital interface will be assigned a value of pin 3 to read val
//  digitalWrite (ledPin, HIGH);
//  delay (sensorValue);
//  digitalWrite (ledPin, LOW);
//  delay (sensorValue);
  Serial.print ("Analog Read: ");
  Serial.println (sensorValue);
  Serial.print ("Digital Read: ");
  Serial.println (val, DEC);
  Serial.println ("");
}
