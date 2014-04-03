int res1 = 0;
int res2 = 1;
int res3 = 2;
int res4 = 3;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(res1));
  Serial.print("-");
  Serial.print(analogRead(res2));
  Serial.print("-");
  Serial.print(analogRead(res3));
  Serial.print("-");
  Serial.print(analogRead(res4));
  Serial.println();
  delay(10);
}
