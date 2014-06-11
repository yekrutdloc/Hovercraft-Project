/**
LiftFanMotor.ino

Purpose: This Sketch contains
code to PWM-control
the lift fan

@author Prince Balabis
@author Ali Rama
*/

static void Thread8(void *arg) {
	//START of one-run setup program

	// Pin for motor
	const int lf_Pin = 7;

	// Manual set of PWM
	int lf_Force = 255;

	//Setup motor pin
	pinMode(lf_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		analogWrite(lf_Pin, lf_Force);
	} //END of infinite loop for thread
}
