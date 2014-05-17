// Unit testing setup
#line 2 "basic.ino"
#include <ArduinoUnit.h>

// PID library include
#include <PID_v1.h>

// Test to see if regulation stops when Input is the same value as Setpoint.
test(onSetpointRegulationTest)
{
  //Define Variables we'll be connecting to
  double Setpoint1, Input1, Output1;
  //Specify the links and initial tuning parameters
  PID myPID(&Input1, &Output1, &Setpoint1, 2, 5, 1, DIRECT);

  //initialize the variables we're linked to
  Input1 = 0;
  Setpoint1 = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  myPID.Compute();

  assertEqual(Output1, 0);
}

// Test to see if regulation stops when Input is above Setpoint
test(noRegulationTest) {
  //Define Variables we'll be connecting to
  double Setpoint2, Input2, Output2;
  //Specify the links and initial tuning parameters
  PID myPID(&Input2, &Output2, &Setpoint2, 2, 5, 1, DIRECT);

  //initialize the variables we're linked to
  Input2 = 100;
  Setpoint2 = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  myPID.Compute();

  assertEqual(Output2, 0);
}

// Test to see if regulation works when Input is below Setpoint
test(regulationActiovateTest) {
  //Define Variables we'll be connecting to
  double Setpoint3, Input3, Output3;
  //Specify the links and initial tuning parameters
  PID myPID(&Input3, &Output3, &Setpoint3, 2, 5, 1, DIRECT);

  //initialize the variables we're linked to
  Input3 = 50;
  Setpoint3 = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  myPID.Compute();

  assertNotEqual(Output3, 0);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Test::run();
}
