#include <OneWire.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int i =1;
int etat =0;
int ledav =2;
int ledar =4;
int bpdcy =6;
int son_ab =7;
int son_dcy =8;
int MesureMaxi = 300; // Distance maxi a mesurer 
int MesureMini = 3; // Distance mini a mesurer 
const int trigPinA = 9; 
const int echoPinA = 10; 
const int trigPinB = 11; 
const int echoPinB = 12;
long dureeA; 
long distanceA;
long dureeB; 
long distanceB;
rgb_lcd lcd;
const int colorR = 200;
const int colorG = 50;
const int colorB = 50;

void setup()
{
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  sensors.begin();
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(bpdcy, INPUT);
  Serial.begin(115200);
}
void loop()
{
  lcd.setCursor(0, 1);
  digitalWrite(ledar , LOW) ;
  digitalWrite(ledav , LOW) ;
  lcd.clear();
  lcd.print("Attente");
  Serial.println("Attente");
  temp();
  i = 1;
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
    prepwrite();
    lcd.print("T Trop haute");
    delay(100);
  }
  while(i<=3)
  {  
    delay(1000);
    digitalWrite(ledav,HIGH);
    temp();
    prepwrite();
    distance();
    while(distanceB <= 10) 
    {
      Serial.println("chariot point B");
      temp();
      prepwrite();
      lcd.print("chariot point B");
      digitalWrite(ledav,LOW);
      digitalWrite(ledar,LOW);
      Serial.println("son chariot au point B");
      sonab();
      etat = 2;
      mouvement();
      delay(3000);
      distance();
    }
    while(distanceA <= 10) 
    {
      Serial.println("chariot point A");
      temp();
      prepwrite();
      lcd.print("chariot point A");
      digitalWrite(ledav,LOW);
      digitalWrite(ledar,LOW);
      Serial.println("son chariot au point A");
      lcd.clear();
      Serial.println("A-R n ");
      Serial.println(i);
      lcd.setCursor(0,0);
      lcd.print("A-R n ");
      lcd.print(i);
      i = i+1 ;
      etat = 1 ;
      mouvement();
      temp();
      sonab();
      delay(3000);
      distance();
    }
  }
  Serial.println("son chariot qui a fini un cycle");
  prepwrite();
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