//Local variables
double frRM_Setpoint = 8;
double frRM_Output;

//Specify the links and initial tuning parameters
PID frRM_PID(pfrRM_PIDInput, &frRM_Output, &frRM_Setpoint, 17, 0, 0, DIRECT);

// Pin for motor
const int frRM_Pin = 2;

static void Thread4(void *arg) {
	//START of one-run setup program

	//Turn PID on
	frRM_PID.SetMode(AUTOMATIC);

	//Setup PID
	//frLM_PID.SetSampleTime(100);
	frRM_PID.SetControllerDirection(REVERSE);
	frRM_PID.SetOutputLimits(0, 180);

	//Setup motor pin
	pinMode(frRM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		frRM_PID.Compute();
		analogWrite(frRM_Pin, frRM_Output);
	} //END of infinite loop for thread
}

