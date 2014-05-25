//Define Variables we'll be connecting to
double br_SetpointRight = 8;

double BRMControl;
double* pBRMControl = &BRMControl;

//Specify the links and initial tuning parameters
PID br_myPIDRight(pbr_BRMPID, pBRMControl, &br_SetpointRight, 56, 0, 0, DIRECT);

static void Thread6(void *arg) {

	//turn the PID on
	br_myPIDRight.SetMode(AUTOMATIC);

	br_myPIDRight.SetControllerDirection(REVERSE);
	br_myPIDRight.SetOutputLimits(0, 200);

	while (1){
		br_myPIDRight.Compute();
	}
}

