int fan = 2;


void setup()
{
  pinMode(fan, OUTPUT);
}

void loop()
{
 
  analogWrite(fan, 255);
  delay(2000);
  analogWrite(fan, 100);
  delay(2000);
}



