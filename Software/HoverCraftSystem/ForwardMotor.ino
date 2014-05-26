// Pin for motor
const int fPM_Pin = 6;

// Manual set of PWM
int fPM_Force = 200;

static void Thread7(void *arg) {
	//START of one-run setup program

	//Setup motor pin
	pinMode(fPM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		analogWrite(fPM_Pin, fPM_Force);
	} //END of infinite loop for thread
}
