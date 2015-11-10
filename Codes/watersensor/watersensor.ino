#define WATER_SENSOR 8
#define BUZZER 12
void setup()
{
Serial.begin(9600);
	pins_init();

}
void loop()
{
if(digitalRead(WATER_SENSOR) == HIGH)
		Serial.println("soundAlarm");
else 
     Serial.println("nope");
}
void pins_init()
{
	pinMode(WATER_SENSOR, INPUT);
}


