const int liftFanPin = 7;
const int forwardPropulsionMotorPin = 6;
const int frontRightMotorPin = 2;
const int frontLeftMotorPin = 3;
const int rearRightMotorPin = 4;
const int rearLeftMotorPin = 5;
const int delayTime = 4000;

void setup()
{
  pinMode(liftFanPin, OUTPUT);
  pinMode(forwardPropulsionMotorPin, OUTPUT);
  pinMode(frontRightMotorPin, OUTPUT);
  pinMode(frontLeftMotorPin, OUTPUT);
  pinMode(rearRightMotorPin, OUTPUT);
  pinMode(rearLeftMotorPin, OUTPUT);

  analogWrite(liftFanPin, 255);
  analogWrite(forwardPropulsionMotorPin, 0);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}

void loop()
{
  delay(6000);

  rotateRight();
  disableHoverLift();

  enableHoverLift();
  rotateLeft();
  disableHoverLift();

  enableHoverLift();
  travelForward();
  disableHoverLift();

  enableHoverLift();
  travelLeft();
  disableHoverLift();

  enableHoverLift();
  travelRight();
  disableHoverLift();
  while (1) {
  }
}

void travelForward() {
  analogWrite(forwardPropulsionMotorPin, 150);
  delay(delayTime);
  analogWrite(forwardPropulsionMotorPin, 0);
}

void travelLeft() {
  analogWrite(frontRightMotorPin, 150);
  analogWrite(rearRightMotorPin, 150);
  delay(delayTime);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
}

void travelRight() {
  analogWrite(frontLeftMotorPin, 150);
  analogWrite(rearLeftMotorPin, 150);
  delay(delayTime);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}

void rotateLeft() {
  analogWrite(frontRightMotorPin, 100);
  analogWrite(rearLeftMotorPin, 100);
  delay(delayTime);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}

void rotateRight() {
  analogWrite(frontLeftMotorPin, 100);
  analogWrite(rearRightMotorPin, 100);
  delay(delayTime);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
}

void disableHoverLift() {
  analogWrite(liftFanPin, 0);
  delay(2000);
}

void enableHoverLift() {
  analogWrite(liftFanPin, 255);
  delay(5000);
}
