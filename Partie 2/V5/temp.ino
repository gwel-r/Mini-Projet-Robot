void temp(void)
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);
  lcd.setCursor(9, 0);
  lcd.print("T=");
  lcd.print(tempC);
  delay(1);
}