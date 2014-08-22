/**
FrontLeftMotor.ino

Purpose: This Sketch contains actual PWM-control of
front left motor and PID-regulation

@author Prince Balabis
@author Ali Rama
*/

static void Thread3(void *arg) {
	//START of one-run setup program

	//Local variables
	double frLM_Setpoint = 8;
	double frLM_Output;

	//Specify the links and initial tuning parameters
	PID frLM_PID(pfrLM_PIDInput, &frLM_Output, &frLM_Setpoint,
		25, 0, 0, DIRECT);

	// Pin for motor
	const int frLM_Pin = 3;

	//Turn PID on
	frLM_PID.SetMode(AUTOMATIC);

	//Setup PID
	frLM_PID.SetControllerDirection(DIRECT);
	frLM_PID.SetOutputLimits(40, 150);

	//Setup motor pin
	pinMode(frLM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		frLM_PID.Compute();
		analogWrite(frLM_Pin, frLM_Output);

		//Serial.print("LEFT Output:  ");
		//Serial.print(frLM_Output);
		//Serial.println();

	} //END of infinite loop for thread
}
