int ledav =2; 
int ledar =4; 
int bpfcg =3; 
int bpfcd =5; 
int bpdcy =6;

void setup()
{
pinMode(ledav,OUTPUT) ;
pinMode(ledar,OUTPUT) ;
pinMode(bpfcg,INPUT) ;
pinMode(bpfcd,INPUT) ;
pinMode(bpdcy,INPUT) ;
Serial.begin(9600);
}

void loop()
{
  digitalWrite(ledar,LOW);
  digitalWrite(ledav ,LOW);
  while(digitalRead(bpdcy) == LOW) 
  {
    delay(100);
  }
  while(digitalRead(bpdcy) == HIGH) 
  {
    Serial.println("démarrage programme");
    digitalWrite(ledav,HIGH);
  }
  while(digitalRead(bpfcd) == LOW) 
  { 
    digitalWrite(ledav,HIGH);
    Serial.println("avance");
  }
  while(digitalRead(bpfcd) == HIGH) 
  {
    Serial.println("chariot au point B");
    digitalWrite(ledav,LOW);
    digitalWrite(ledar,LOW);
    delay(4000);
    digitalWrite(ledar,HIGH);
  }
  while(digitalRead(bpfcg) == LOW) 
  {
    digitalWrite(ledav,LOW);
    digitalWrite(ledar,HIGH);
    Serial.println("recule");
  }
  while(digitalRead(bpfcg) == HIGH) 
  {
    Serial.println("chariot au point A");
    digitalWrite(ledav,LOW);
    digitalWrite(ledar,LOW);
  }                   
}
