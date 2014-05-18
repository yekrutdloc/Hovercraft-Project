// This basic program blinks between two different PWM-values

int pwmPin = 2;

void setup()
{
  pinMode(pwmPin, OUTPUT); // Setup pin as output
}

void loop()
{
  analogWrite(pwmPin, 255); // Set pwm to max
  delay(2000); // Hold max pwm for two seconds
  analogWrite(pwmPin, 100); // Set pwm to 100
  delay(2000); // Hold pwm 100 for two seconds
}



