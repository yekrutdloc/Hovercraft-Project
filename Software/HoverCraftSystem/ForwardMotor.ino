// Pin for motor
const int fPM_Pin = 6;
xSemaphoreHandle fPM_Sem;



static void Thread7(void *arg) {
	//START of one-run setup program

	//Setup motor pin
	pinMode(fPM_Pin, OUTPUT);

	// Manual start-parameter of PWM
	int fPM_Force = 255;

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		analogWrite(fPM_Pin, fPM_Force);
		xSemaphoreTake(fPM_Sem, portMAX_DELAY);
	} //END of infinite loop for thread
}
