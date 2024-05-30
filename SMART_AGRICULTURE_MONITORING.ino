
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

#include<DHT.h>
#define Type DHT11

int dhtpin = 5;
DHT HT(dhtpin, Type);

int Relay1=2;
int Relay2=16;
int LED=3;

#define echoPin 7
#define pingPin 6

long duration;
int distance;

void ultra_check();
long microsecondsToCentimeters(long microseconds);
char ch;

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void setup()
{
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);  
  pinMode(LED, OUTPUT);
  digitalWrite(Relay1,HIGH);
 digitalWrite(Relay2,HIGH);
   Serial.begin(9600);
   lcd.begin(16, 2);
 HT.begin();
   Serial.print("SMART AGRICULTURE  SYSTEM");
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("SMART AGRICULTURE");
   lcd.setCursor(0,1);
   lcd.print("SYSTEM....");
   delay(2000);
   
}
void loop ()
{
     SOIL_MOISTURE();
     HUMIDITY_MONITORING();
     WATER_LEVEL();
     LDR_READING();
     
} 
void HUMIDITY_MONITORING()
{
  float tempC;
  float humidityy;
  
  humidityy = HT.readHumidity();
  tempC = HT.readTemperature();
  
  Serial.print("humidity= ");
  Serial.println(humidityy);
  
  Serial.print("temperature= ");
  Serial.print(tempC);
  Serial.println("c");

  lcd.clear();
  lcd.print("Temp:");
  lcd.print(tempC);
   lcd.setCursor(0, 1);
   lcd.print("Humidity:");
   lcd.print(humidityy);
  
  delay(1000);

  if(tempC>33)
  {
    lcd.clear();
    lcd.print("High Temperature");
    Serial.println("$High Temperature..#");
    digitalWrite(Relay2,LOW);
    delay(1000);
    
  }
  else
  {
    digitalWrite(Relay2,HIGH);
    delay(1000);
    
  }
}
  
void SOIL_MOISTURE()
{                     
  int Soil_val = analogRead(A0); 
  Soil_val=1023-Soil_val;
  Serial.print("Moisture: ");
  Serial.println(Soil_val);
  lcd.clear();
  lcd.print("Moisture:");
  lcd.print(Soil_val);
  delay(1000);
  if(Soil_val<100)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Low Moisture");
    lcd.setCursor(0,1);
    lcd.print("Level..");
    digitalWrite(Relay1,LOW);
    Serial.println("$Moisture Level is Low Pump is On..#");
    delay(1000);
  }
  else
  {
     digitalWrite(Relay1,HIGH);
  }

}
void LDR_READING()
{
                      
  int LDR_val = analogRead(A1); 
  LDR_val=1023-LDR_val;
  Serial.print("LDR: ");
  Serial.println(LDR_val);
  lcd.clear();
  lcd.print("LDR:");
  lcd.print(LDR_val);
  delay(1000);
  if(LDR_val<500)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Less Light");
    lcd.setCursor(0,1);
    lcd.print("LED On..");
    digitalWrite(LED,HIGH);
    Serial.println("$Less Light Condition LED is On..#");
    delay(1000);
  }
  else
  {
    digitalWrite(LED,LOW);
  }

}

void WATER_LEVEL()
{
    long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   
   cm = microsecondsToCentimeters(duration);
   
   Serial.print("LEVEL:");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   lcd.clear();
   lcd.print("LEVEL:");
   lcd.print(cm);
   delay(1000);

   if(cm<20)
  {

     lcd.clear();
     lcd.print("HIGH WATER LEVEL");
     Serial.println("$HIGH WATER LEVEL#");
     delay(1000);
    
  }
  if((cm>20)&&(cm<50))
  {
     lcd.clear();
     lcd.print("MIDDLE WATER LEVEL");
     Serial.println("$MIDDLE WATER LEVEL#");
     delay(1000); 
  }
  if(cm>50)
  {

     lcd.clear();
     lcd.print("LOW WATER LEVEL");
     Serial.println("$LOW WATER LEVEL#");
     delay(1000);
    
  }

}
