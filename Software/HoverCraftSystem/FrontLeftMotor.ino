//Local variables
double frLM_Setpoint = 8;
double frLM_Output;

//Specify the links and initial tuning parameters
PID frLM_PID(pfrLM_PIDInput, &frLM_Output, &frLM_Setpoint, 35, 0.008, 55, DIRECT);

// Pin for motor
const int frLM_Pin = 3;

static void Thread2(void *arg) {
	//START of one-run setup program

	//Setup PID
	frLM_PID.SetControllerDirection(REVERSE);
	frLM_PID.SetOutputLimits(0, 200);

	//Turn PID on
	frLM_PID.SetMode(AUTOMATIC);

	//Setup motor pin
	pinMode(frLM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		frLM_PID.Compute();
		analogWrite(frLM_Pin, frLM_Output);
	} //END of infinite loop for thread
}
