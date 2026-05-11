void mouvement(void)
{
  if (etat == 1 && i<=2)
  {
    digitalWrite(ledav,HIGH);
    Serial.println("chariot avance");
    lcd.print("chariot avance");
    delay(10);
  }
  else if (etat == 1 && i==3)
  {
    etat = 0;
  }
  else if (etat == 2)
  {
    digitalWrite(ledar,HIGH);
    Serial.println("chariot recule");
    lcd.print("chariot recule");
  }
}