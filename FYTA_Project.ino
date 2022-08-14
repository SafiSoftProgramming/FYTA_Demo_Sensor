#include<SoftwareSerial.h>

//Bluetooth serial stuff
const int txpin = 5;       
const int rxpin = 6;

int SoilMoisture_Pin = A0 ;
int Light_Pin        = A1 ;
int Temperature_Pin  = A2 ;
int WaterTank_Pin    = A3 ;
int WaterPump_Pin    = 7  ;
#define water_pump 7

int soil_moisture_Value; 

int Light_Value ;

int Temperature_Value;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; 

int Water_Tank_Value ;



SoftwareSerial blue(txpin, rxpin);

char Command  ;

void setup() {
   blue.begin(9600);
   Serial.begin(9600);
  //blue.setTimeout(10);
  digitalWrite(water_pump,LOW);
  pinMode(water_pump,OUTPUT); 
}


void loop() {
 soil_moisture_Value = analogRead(SoilMoisture_Pin); //soil_moisture
  
 Light_Value = analogRead(Light_Pin); //Light
 
 Temperature_Value = analogRead(Temperature_Pin);//temp
  R2 = R1 * (1023.0 / (float)Temperature_Value - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 
  String Temp_String = String(Tc, 0);
  
 Water_Tank_Value = analogRead(WaterTank_Pin); //Water_Tank


//delay(1000);

   Serial.println(soil_moisture_Value );
   Serial.println(Light_Value );
   Serial.println(Temp_String );
  Serial.println( Water_Tank_Value);
    Serial.println( "//////////////////////////////////");


String Send = String(soil_moisture_Value)+","+String(Light_Value)+","+String(Temp_String)+","+String(Water_Tank_Value);
 blue.println(Send); 
 
  if (blue.available()) {
    Command = blue.read();
      if(Command == 'W'){
        Serial.println( 'W');
        digitalWrite(water_pump,HIGH);
        delay(1000);
        digitalWrite(water_pump,LOW);                 
      }
     } 
delay(500);
     
}
