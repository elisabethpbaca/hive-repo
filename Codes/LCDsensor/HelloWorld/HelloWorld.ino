#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
/*
For details about the LCD display with I2C support see
http://www.fasttech.com/reviews/1380909/22072
and
http://dx.com/p/funduino-iic-i2c-1602-lcd-adapter-board-w-2-5-lcd-screen-black-green-red-173588
The reviewer comments by docpayce and particularly JackWP associated with the two product pages above have been very useful.
 
Connect the LCD: VCC -> 5V, GND -> GND, SDA -> A4 (PortC4, ADC4), SCL -> A5 (PortC5, SDA)
 
The LiquidCrystal_I2C library needs to be downloaded and installed from here: https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
*/
 
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
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);               // initialize the lcd
  lcd.home ();                   // go home
  lcd.print("Hello, BOB ");
  delay(500);
}
 
void loop()
{
//  int sensorValue = analogRead(SENSOR_PIN);
//  // set cursor to second row, first column
//  lcd.setCursor(0, 1);
//  lcd.print(sensorValue);
//  lcd.print("      ");
//  delay (100);
  // when characters arrive over the serial port...
  //lcd.home ();
  //lcd.print("Rhane");
  //Serial.println("Hello!");
  //Serial.println("Serial available: " + Serial.available());
  if (Serial.available()) 
  {   
    
    Serial.println("delay for 100");
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    Serial.println("lcd.clear()");
    lcd.clear();
    // read all the available characters
    lcd.home ();
    while (Serial.available() > 0) 
    {
      Serial.println("stuff is available, going to read");
      // display each character to the LCD
      // read the incoming byte:
      incomingByte = Serial.read();
      lcd.print(incomingByte);
    }
  }
}
