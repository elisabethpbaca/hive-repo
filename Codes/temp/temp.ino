float tempC;
int reading;
int tempPin = 1;

void setup()
{
analogReference(INTERNAL);
Serial.begin(9600);
}

void loop()
{
reading = analogRead(tempPin);
tempC = reading / 9.31;
float tempF;
tempF = (tempC *1.8)+32;
Serial.println(tempC);
Serial.println(tempF);
delay(1000);
}
