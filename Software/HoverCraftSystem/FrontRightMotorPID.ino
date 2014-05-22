//Define Variables we'll be connecting to
double fr_SetpointRight = 8;

double FRMControl;
double* pFRMControl = &FRMControl;

//Specify the links and initial tuning parameters
PID fr_myPIDRight(pfr_FRMPID, pFRMControl, &fr_SetpointRight, 25, 0, 0, DIRECT);

static void Thread4(void *arg) {

	//turn the PID on
	fr_myPIDRight.SetMode(AUTOMATIC);

	fr_myPIDRight.SetControllerDirection(REVERSE);
	fr_myPIDRight.SetOutputLimits(40, 225);

	while (1){
		fr_myPIDRight.Compute();
	}
}

