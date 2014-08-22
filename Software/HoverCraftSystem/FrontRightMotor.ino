/**
FrontRightMotor.ino

Purpose: This Sketch contains actual PWM-control
of front right motor and PID-regulation

@author Prince Balabis
@author Ali Rama
*/

static void Thread4(void *arg) {
	//START of one-run setup program

	//Local variables
	double frRM_Setpoint = 8;
	double frRM_Output;

	//Specify the links and initial tuning parameters
	PID frRM_PID(pfrRM_PIDInput, &frRM_Output, &frRM_Setpoint,
		28, 0, 0, DIRECT);

	// Pin for motor
	const int frRM_Pin = 2;

	//Turn PID on
	frRM_PID.SetMode(AUTOMATIC);

	//Setup PID
	frRM_PID.SetControllerDirection(DIRECT);
	frRM_PID.SetOutputLimits(40, 150);

	//Setup motor pin
	pinMode(frRM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		frRM_PID.Compute();
		analogWrite(frRM_Pin, frRM_Output);

		//Serial.print("RIGHT Output:  ");
		//Serial.print(frLM_Output);
		//Serial.println();

	} //END of infinite loop for thread
}

