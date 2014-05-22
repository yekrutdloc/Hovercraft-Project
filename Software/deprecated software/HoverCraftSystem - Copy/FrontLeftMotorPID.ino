//Define Variables we'll be connecting to
double fr_SetpointLeft;

double FLMControl;
double* pFLMControl = &FLMControl;

//Specify the links and initial tuning parameters
PID fr_myPIDLeft(pfr_FLMPID, pFLMControl, &fr_SetpointLeft, 2.5, 0.008, 65, DIRECT);

static WORKING_AREA(fr_LeftmotorPID, 100);

static msg_t Thread2(void *arg) {

	//initialize the variables we're linked to
	fr_SetpointLeft = 8;

	//turn the PID on
	fr_myPIDLeft.SetMode(AUTOMATIC);

	fr_myPIDLeft.SetControllerDirection(REVERSE);
	fr_myPIDLeft.SetOutputLimits(40, 225);

	while (1){
		fr_myPIDLeft.Compute();
		Serial.print(*pfr_FLMPID);
		Serial.print(" - ");
		Serial.print(*pFLMControl);
		Serial.print(" - ");
		Serial.print(*pfr_FRMPID);
		Serial.print(" - ");
		Serial.print(*pFRMControl);

		Serial.println();
	}
	return 0;
}
