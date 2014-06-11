/**
ForwardMotor.inp

Purpose: This Sketch controls the forward propulsion motor.
Right now it only "blinks" the motor, to keep the hovercraft
from accelerating too much. In the future an accelerometer
is to be added to be able to regulate the motor.

@author Prince Balabis
*/

static void Thread7(void *arg) {
	//START of one-run setup program

	// Pin for motor
	const int fPM_Pin = 6;

	//Setup motor pin
	pinMode(fPM_Pin, OUTPUT);

	// Manual start-parameter of PWM
	int fPM_Force = 140;
	analogWrite(fPM_Pin, fPM_Force);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		vTaskDelay((3000L * configTICK_RATE_HZ) / 1000L);
		analogWrite(fPM_Pin, 50);
		vTaskDelay((800L * configTICK_RATE_HZ) / 1000L);
		analogWrite(fPM_Pin, 255);
	} //END of infinite loop for thread
}
