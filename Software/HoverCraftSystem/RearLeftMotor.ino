/**
RearLeftMotor.ino

Purpose: This Sketch contains actual PWM-control
of rear left motor and PID-regulation

@author Prince Balabis
@author Ali Rama
*/

static void Thread5(void *arg) {
	//START of one-run setup program

	//Local variables
	double reLM_Setpoint = 8;
	double reLM_Output;

	//Specify the links and initial tuning parameters
	PID reLM_PID(preLM_PIDInput, &reLM_Output, &reLM_Setpoint,
		25, 0, 0, DIRECT);

	// Pin for motor
	const int reLM_Pin = 4;

	//turn the PID on
	reLM_PID.SetMode(AUTOMATIC);

	//Setup PID
	reLM_PID.SetControllerDirection(DIRECT);
	reLM_PID.SetOutputLimits(40, 150);

	//Setup motor pin
	pinMode(reLM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		reLM_PID.Compute();
		analogWrite(reLM_Pin, reLM_Output);
	} //END of infinite loop for thread
}

