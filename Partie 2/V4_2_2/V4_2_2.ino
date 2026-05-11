/* programme ok le 27 01 2026*/



#include <OneWire.h>
#include "rgb_lcd.h"
#include <DallasTemperature.h>
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 7
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
int ledav =2;
int ledar =4;
int bpfcg =3;
int bpfcd =5;
int bpdcy =6;
int son_ab =7;
int son_dcy =8;

rgb_lcd lcd;
const int colorR = 200;
const int colorG = 50;
const int colorB = 50;
 
void setup()
{
  Wire.begin(); // Rejoindre le bus I2C (Pas besoin d adresse pour le maitre)
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  sensors.begin();
  pinMode(ledav,OUTPUT) ;
  pinMode(ledar,OUTPUT) ;
  pinMode(bpfcg,INPUT) ;
  pinMode(bpfcd,INPUT) ;
  pinMode(bpdcy,INPUT) ;
  Serial.begin(9600);
}
 
void loop()
{
  lcd.setCursor(0, 1);
  digitalWrite(ledar , LOW) ;
  digitalWrite(ledav , LOW) ;
  lcd.clear();
  lcd.print("Attente");
  temp();
  while(digitalRead(bpdcy) == LOW)
  {
    temp();
  }
  while (sensors.getTempCByIndex(0)>= 30)
  {
    digitalWrite(ledav,LOW);
    digitalWrite(ledar,LOW);
    temp();
    Serial.print ("T° trop haute pour fonctionner");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("T Trop haute");
    delay(100);
  }
     for(int i=1;i<=3;i++)
    {  
      lcd.clear();
      Serial.println("A-R n ");
      Serial.println(i);
      lcd.setCursor(0,0);
      lcd.print("A-R n ");
      lcd.print(i);
      temp();
      while(digitalRead(bpfcd) == LOW) 
      { 
        digitalWrite(ledav,HIGH);
        Serial.println("chariot avance");
        temp();
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("chariot avance");
      }
      while(digitalRead(bpfcd) == HIGH) 
      {
        Serial.println("chariot point B");
        temp();
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("chariot point B");
        digitalWrite(ledav,LOW);
        digitalWrite(ledar,LOW);
        delay(1000);
        Serial.println("son chariot au point B");
        sonab();
        digitalWrite(ledar,HIGH);
      }
      while(digitalRead(bpfcg) == LOW) 
      {
        digitalWrite(ledav,LOW);
        digitalWrite(ledar,HIGH);
        Serial.println("recule");
        temp();
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("chariot recule");
      }
      while(digitalRead(bpfcg) == HIGH) 
      {
        Serial.println("chariot point A");
        temp();
        lcd.setCursor(0,1);
        lcd.print("                ");
        lcd.setCursor(0,1);
        lcd.print("chariot point A");
        digitalWrite(ledav,LOW);
        digitalWrite(ledar,LOW);
        Serial.println("son chariot au point A");
        sonab();
        delay(1000);
      }
    }
    Serial.println("son chariot qui a fini un cycle");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("cycle fini");
    sonfcy();
  }
 
void sonab()
{
  tone(7,440);
  delay(150);
  noTone(7);
  delay(150);
  tone(7,440);
  delay(150);
  noTone(7);
}
 
void sonfcy()
{
  tone(8,880);
  delay(150);
  noTone(8);
  delay(150);
  tone(8,880);
  delay(150);
  noTone(8);
  delay(150);
  tone(8,880);
  delay(150);
  noTone(8);
}

void temp()
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);
  lcd.setCursor(9, 0);
  lcd.print("T=");
  lcd.print(tempC);
  delay(1);
}
