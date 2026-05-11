int ledav =2; 
int ledar =4; 
int BPfcg =3; 
int BPfcd =5; 
int BPdcy =6; 


void setup()
{
pinMode(ledav,OUTPUT) ;
pinMode(ledar,OUTPUT) ;
pinMode(BPfcg,INPUT) ;
pinMode(BPfcd,INPUT) ;
pinMode(BPdcy,INPUT) ;
Serial.begin(9600);
}

void loop()
{
 if (digitalRead(BPdcy)==HIGH)
 {
  Serial.println("démarrage programme");
  while (digitalRead(BPfcd)==LOW)
  {
  digitalWrite(ledar , LOW) ;
  digitalWrite(ledav , HIGH) ;
  }
  if (digitalRead(BPfcd)==HIGH)
  {
    digitalWrite(ledar , LOW) ;
    digitalWrite(ledav , LOW) ;
    Serial.println("chariot au point B");
    delay(4000);
    while (digitalRead(BPfcg)==LOW)
    {
    digitalWrite(ledar , HIGH) ;
    digitalWrite(ledav , LOW) ;
    }
  }
  if (digitalRead(BPfcg)==HIGH)
  {
    Serial.println("chariot au point A");
    digitalWrite(ledar , LOW) ;
    digitalWrite(ledav , LOW) ;
  }
 }
}
