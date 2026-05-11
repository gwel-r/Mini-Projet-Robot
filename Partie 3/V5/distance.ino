void distance(void)
{
  digitalWrite(trigPinA, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinA, LOW);
  dureeA = pulseIn(echoPinA, HIGH);
  distanceA = dureeA*0.034/2;
  if (distanceA >= MesureMaxi || distanceA <= MesureMini) {
  Serial.println("Distance de mesure en dehors de la plage (3 cm à 3 m)");
  }
  Serial.print("Distance mesuree :");
  Serial.print(distanceA);
  Serial.println("cm");
  digitalWrite(trigPinB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinB, LOW);
  dureeB = pulseIn(echoPinB, HIGH);
  distanceB = dureeB*0.034/2;
  if (distanceB >= MesureMaxi || distanceB <= MesureMini) {
  // Si la distance est hors plage, on affiche un message d'erreur //
  Serial.println("Distance de mesure en dehors de la plage (3 cm à 3 m)");
  }
  else{
    Serial.print("Distance mesuree :");
  Serial.print(distanceB);
  Serial.println("cm");
  }
  delay(1000);
}
