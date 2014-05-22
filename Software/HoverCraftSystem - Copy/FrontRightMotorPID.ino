//Define Variables we'll be connecting to
double fr_SetpointRight;

double FRMControl;
double* pFRMControl = &FRMControl;

//Specify the links and initial tuning parameters
PID fr_myPIDRight(pfr_FRMPID, pFRMControl, &fr_SetpointRight, 2.5, 0.008, 65, DIRECT);

static WORKING_AREA(fr_RightmotorPID, 100);

static msg_t Thread3(void *arg) {

	//initialize the variables we're linked to
	fr_SetpointRight = 8;

	//turn the PID on
	fr_myPIDRight.SetMode(AUTOMATIC);

	fr_myPIDRight.SetControllerDirection(REVERSE);
	fr_myPIDRight.SetOutputLimits(40, 225);

	while (1){
		fr_myPIDRight.Compute();
	}
	return 0;
}

