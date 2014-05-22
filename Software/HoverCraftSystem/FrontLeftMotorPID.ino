//Define Variables we'll be connecting to
double fr_SetpointLeft = 8;

double FLMControl;
double* pFLMControl = &FLMControl;

//Specify the links and initial tuning parameters
PID fr_myPIDLeft(pfr_FLMPID, pFLMControl, &fr_SetpointLeft, 25, 0, 0, DIRECT);

static void Thread3(void *arg) {

	//turn the PID on
	fr_myPIDLeft.SetMode(AUTOMATIC);

	fr_myPIDLeft.SetControllerDirection(REVERSE);
	fr_myPIDLeft.SetOutputLimits(40, 225);

	while (1){
		fr_myPIDLeft.Compute();
		//Serial.print(*pfr_FLMPID);
		//Serial.print(" - ");
		//Serial.print(*pFLMControl);
		//Serial.print(" - ");
		//Serial.print(*pfr_FRMPID);
		//Serial.print(" - ");
		//Serial.print(*pFRMControl);
		//Serial.println();
	}
}
