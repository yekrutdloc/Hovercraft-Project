// Pin for motor
const int fPM_Pin = 6;
xSemaphoreHandle fPM_Sem;



static void Thread7(void *arg) {
	//START of one-run setup program

	//Setup motor pin
	pinMode(fPM_Pin, OUTPUT);

	// Manual start-parameter of PWM
	int fPM_Force = 140;
	analogWrite(fPM_Pin, fPM_Force);
	//vTaskDelay((10000L * configTICK_RATE_HZ) / 1000L);
	//analogWrite(fPM_Pin, 0);
	//vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
	//analogWrite(fPM_Pin, 90);

	//vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread
	vTaskDelay((3000L * configTICK_RATE_HZ) / 1000L);
	analogWrite(fPM_Pin, 50);
	vTaskDelay((800L * configTICK_RATE_HZ) / 1000L);
	analogWrite(fPM_Pin, 200);
		
	} //END of infinite loop for thread
}
