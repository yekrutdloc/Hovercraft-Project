// Dance.ino
//
// Purpose: This program is to demonstrate the different movements programmed to the hovercraft
// When program starts, 5 second delay is added to wait for the lift fan to fully spin up
// Afterwards the first dance move starts, which is to rotate right.
// The dance move length is changed by changing the variable "moveLength"
// Afterwards the lift fan spins down, to act as a break, before resuming to the next dance move
// Change motor pins below if needed
//
// @author Prince Balabis

// Pins for motors
const int liftFanPin = 7;
const int forwardPropulsionMotorPin = 6;
const int frontRightMotorPin = 2;
const int frontLeftMotorPin = 3;
const int rearRightMotorPin = 4;
const int rearLeftMotorPin = 5;

// length of a dance move
const int moveLength = 4000;

void setup()
{
  // Motor pin setup
  pinMode(liftFanPin, OUTPUT);
  pinMode(forwardPropulsionMotorPin, OUTPUT);
  pinMode(frontRightMotorPin, OUTPUT);
  pinMode(frontLeftMotorPin, OUTPUT);
  pinMode(rearRightMotorPin, OUTPUT);
  pinMode(rearLeftMotorPin, OUTPUT);

  // Motor initial setup
  analogWrite(liftFanPin, 255);
  analogWrite(forwardPropulsionMotorPin, 0);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}

void loop()
{
  // Delay untill dance starts
  delay(5000);

  // Rotate right  move
  rotateRight();
  disableHoverLift();

  // Rotate left  move
  enableHoverLift();
  rotateLeft();
  disableHoverLift();

  // Travel forward  move
  enableHoverLift();
  travelForward();
  disableHoverLift();


  // Move left move
  enableHoverLift();
  travelLeft();
  disableHoverLift();

  // Move right move
  enableHoverLift();
  travelRight();
  disableHoverLift();

  // Infinite loop to end dance
  while (1) {
    delay(2000);
  }
}

// Function to make the hovercraft move FORWARD
void travelForward() {
  analogWrite(forwardPropulsionMotorPin, 150);
  delay(moveLength);
  analogWrite(forwardPropulsionMotorPin, 0);
}

// Function to make the hovercraft move LEFT
void travelLeft() {
  analogWrite(frontRightMotorPin, 150);
  analogWrite(rearRightMotorPin, 150);
  delay(moveLength);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
}

// Function to make the hovercraft move RIGHT
void travelRight() {
  analogWrite(frontLeftMotorPin, 150);
  analogWrite(rearLeftMotorPin, 150);
  delay(moveLength);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}

// Function to make the hovercraft ROTATE LEFT
void rotateLeft() {
  analogWrite(frontRightMotorPin, 100);
  analogWrite(rearLeftMotorPin, 100);
  delay(moveLength);
  analogWrite(frontRightMotorPin, 0);
  analogWrite(rearLeftMotorPin, 0);
}

// Function to make the hovercraft ROTATE RIGHT
void rotateRight() {
  analogWrite(frontLeftMotorPin, 100);
  analogWrite(rearRightMotorPin, 100);
  delay(moveLength);
  analogWrite(frontLeftMotorPin, 0);
  analogWrite(rearRightMotorPin, 0);
}

// Function to make the hovercraft stop/break by DISABLING the LIFT FAN
void disableHoverLift() {
  analogWrite(liftFanPin, 0);
  delay(1500);
}

// Function to make hovercraft hover by ENABLING the LIFT FAN
void enableHoverLift() {
  analogWrite(liftFanPin, 255);
  delay(4000);
}
