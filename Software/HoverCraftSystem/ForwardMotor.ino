// Pin for motor
const int fPM_Pin = 6;
xSemaphoreHandle fPM_Sem;

static void Thread7(void *arg) {
	//START of one-run setup program

	//Setup motor pin
	pinMode(fPM_Pin, OUTPUT);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
		xSemaphoreTake(fPM_Sem, portMAX_DELAY);
		analogWrite(fPM_Pin, fPM_Force);
	} //END of infinite loop for thread
}
