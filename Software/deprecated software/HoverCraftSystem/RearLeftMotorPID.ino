//Define Variables we'll be connecting to
double br_SetpointLeft;

double BLMControl;
double* pBLMControl = &BLMControl;

//Specify the links and initial tuning parameters
PID br_myPIDLeft(pbr_BLMPID, pBLMControl, &br_SetpointLeft, 2.5, 0.008, 65, DIRECT);

static WORKING_AREA(br_LeftmotorPID, 100);

static msg_t Thread8(void *arg) {

	//initialize the variables we're linked to
	br_SetpointLeft = 8;

	//turn the PID on
	br_myPIDLeft.SetMode(AUTOMATIC);

	br_myPIDLeft.SetControllerDirection(REVERSE);
	br_myPIDLeft.SetOutputLimits(40, 225);

	while (1){
		br_myPIDLeft.Compute();
		Serial.print(*pbr_BLMPID);
		Serial.print(" - ");
		Serial.print(*pBLMControl);
		Serial.print(" - ");
		Serial.print(*pbr_BRMPID);
		Serial.print(" - ");
		Serial.print(*pBRMControl);

		Serial.println();
	}
	return 0;
}

