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

  if(analogRead(res1) < 60){
      Serial.print(1);
  } else {
    Serial.print(0);
  }
  
  if(analogRead(res2) < 20){
      Serial.print(1);
  } else {
    Serial.print(0);
  }

  if(analogRead(res3) < 70){
      Serial.print(1);
  } else {
    Serial.print(0);
  }
  
    if(analogRead(res4) < 70){
      Serial.print(1);
  } else {
    Serial.print(0);
  }

  Serial.println();
  delay(10);
}
