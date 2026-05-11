void distance(void)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duree = pulseIn(echoPin, HIGH);
  distancecapteur = duree*0.034/2;
  if (distancecapteur >= MesureMaxi || distancecapteur <= MesureMini) {
  Serial.println("Distance de mesure en dehors de la plage (3 cm a 3 m)");
  }
  Serial.print("Distance mesuree :");
  Serial.print(distancecapteur);
  Serial.println("cm");
  delay(1000);
}