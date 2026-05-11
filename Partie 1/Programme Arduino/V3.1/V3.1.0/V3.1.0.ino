int ledav =2;
int ledar =4;
int bpfcg =3;
int bpfcd =5;
int bpdcy =6;
int son_ab =7;
int son_dcy =8;


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
  digitalWrite(ledar , LOW) ;
  digitalWrite(ledav , LOW) ;
  while(digitalRead(bpdcy) == LOW)
  {
    while(digitalRead(bpdcy) == LOW) 
      {
        delay(100);
      }
      while(digitalRead(bpdcy) == HIGH) 
      {
        Serial.println("démarrage programme");
        digitalWrite(ledav,HIGH);
      }
     for(int i=0;i<=2;i++)
    {
      Serial.println("aller-retour n°");
      Serial.println(i);
      digitalWrite(ledar,LOW);
      digitalWrite(ledav ,LOW);
      
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
        delay(1000);
        Serial.println("son chariot au point B");
        tone(7,440);
        delay(150);
        tone(7,440);
        noTone(7);
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
        Serial.println("son chariot au point A");
        tone(7,440);
        delay(150);
        tone(7,440);
        noTone(7);
        delay(1000);
      }
    }
    Serial.println("son chariot qui a fini un cycle");
    tone(8,880);
    delay(150);
    tone(8,880);
    delay(150);
    tone(8,880);
    noTone(8);
  }
}
