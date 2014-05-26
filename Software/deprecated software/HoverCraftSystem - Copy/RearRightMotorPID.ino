//Define Variables we'll be connecting to
double br_SetpointRight;

double BRMControl;
double* pBRMControl = &FRMControl;

//Specify the links and initial tuning parameters
PID br_myPIDRight(pbr_BRMPID, pBRMControl, &br_SetpointRight, 2.5, 0.008, 65, DIRECT);

static WORKING_AREA(br_RightmotorPID, 100);

static msg_t Thread9(void *arg) {

	//initialize the variables we're linked to
	br_SetpointRight = 8;

	//turn the PID on
	br_myPIDRight.SetMode(AUTOMATIC);

	br_myPIDRight.SetControllerDirection(REVERSE);
	br_myPIDRight.SetOutputLimits(40, 225);

	while (1){
		br_myPIDRight.Compute();
	}
	return 0;
}

