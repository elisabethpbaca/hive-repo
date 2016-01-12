// # the sensor value description
//# 0~300     dry soil
//# 300~700     humid soil
//# 700~950     in water
#define WATER_SENSOR 8
#define BUZZER 12
//water 
  void pins_init()
  {
  	pinMode(WATER_SENSOR, INPUT);
  }



void setup(){

Serial.begin(9600);
   pins_init();
}

void loop(){
  
//soil soil 
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




}







