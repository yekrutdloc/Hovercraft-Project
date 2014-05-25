//Define Variables we'll be connecting to
double br_SetpointLeft = 8;

double BLMControl;
double* pBLMControl = &BLMControl;

//Specify the links and initial tuning parameters
PID br_myPIDLeft(pbr_BLMPID, pBLMControl, &br_SetpointLeft, 56, 0, 0, DIRECT);

static void Thread5(void *arg) {

	//turn the PID on
	br_myPIDLeft.SetMode(AUTOMATIC);

	br_myPIDLeft.SetControllerDirection(REVERSE);
	br_myPIDLeft.SetOutputLimits(0, 200);

	while (1){
		br_myPIDLeft.Compute();
		//Serial.print(*pbr_BLMPID);
		//Serial.print(" - ");
		//Serial.print(*pBLMControl);
		//Serial.print(" - ");
		//Serial.print(*pbr_BRMPID);
		//Serial.print(" - ");
		//Serial.print(*pBRMControl);
		//Serial.println();
	}
}

