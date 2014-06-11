//HoverCraftMotors_Test.ino
//
// Purpose: This program is made to easily 
// test each or several motors with PWM
//
// @author Prince Balabis
//

// Pins to the motors/fans
const int liftFanPin = 7;
const int forwardPropulsionMotorPin = 6;
const int frontRightMotorPin = 2;
const int frontLeftMotorPin = 3;
const int rearRightMotorPin = 4;
const int rearLeftMotorPin = 5;

// Setup pins as outputs
void setup()
{
  pinMode(liftFanPin, OUTPUT);
  pinMode(forwardPropulsionMotorPin, OUTPUT);
  pinMode(frontRightMotorPin, OUTPUT);
  pinMode(frontLeftMotorPin, OUTPUT);
  pinMode(rearRightMotorPin, OUTPUT);
  pinMode(rearLeftMotorPin, OUTPUT);
}

// Change PWM-values accordingly to test the motors
void loop()
{
  analogWrite(liftFanPin, 255);
  analogWrite(forwardPropulsionMotorPin, 0);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}



