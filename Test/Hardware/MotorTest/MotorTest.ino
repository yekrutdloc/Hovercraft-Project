const int liftFanPin = 7;
const int forwardPropulsionMotorPin = 6;
const int frontRightMotorPin = 2;
const int frontLeftMotorPin = 3;
const int rearRightMotorPin = 4;
const int rearLeftMotorPin = 5;

void setup()
{
  pinMode(liftFanPin, OUTPUT);
  pinMode(forwardPropulsionMotorPin, OUTPUT);
  pinMode(frontRightMotorPin, OUTPUT);
  pinMode(frontLeftMotorPin, OUTPUT);
  pinMode(rearRightMotorPin, OUTPUT);
  pinMode(rearLeftMotorPin, OUTPUT);
}

void loop()
{
  analogWrite(liftFanPin, 255);
  analogWrite(forwardPropulsionMotorPin, 0);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}



