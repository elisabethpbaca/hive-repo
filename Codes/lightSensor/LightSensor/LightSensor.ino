int sensorPin = A1; // select the input pin for the potentiometer
//int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor

// Min 0
// Max 1024

void setup() {
//  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  sensorValue = analogRead(sensorPin);
  //digitalWrite(ledPin, HIGH);
  delay(100);
//  digitalWrite(ledPin, LOW);
  delay(100);
  Serial.println(sensorValue, DEC);
}
