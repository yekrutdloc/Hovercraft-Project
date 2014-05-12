void setup()
{
  pinMode(6, OUTPUT);   // sets the pin as output
}

void loop()
{
  analogWrite(6, 255);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  delay(3000);
  analogWrite(6, 0);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  delay(3000);
}

