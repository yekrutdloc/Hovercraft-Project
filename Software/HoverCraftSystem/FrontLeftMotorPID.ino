//Define Variables we'll be connecting to
double SetpointLeft;

double FLMControl;
double* pFLMControl = &FLMControl;

//Specify the links and initial tuning parameters
PID myPIDLeft(pfr_FLMPID, pFLMControl, &SetpointLeft, 20, 0.04, 600, DIRECT);

static WORKING_AREA(fr_LeftmotorPID, 100);

static msg_t Thread2(void *arg) {

	//initialize the variables we're linked to
	SetpointLeft = 8;

	//turn the PID on
	myPIDLeft.SetMode(AUTOMATIC);

	myPIDLeft.SetControllerDirection(REVERSE);
	myPIDLeft.SetOutputLimits(40, 225);

	while (1){
		myPIDLeft.Compute();
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
