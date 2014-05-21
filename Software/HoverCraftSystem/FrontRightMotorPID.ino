//Define Variables we'll be connecting to
double SetpointRight;

double FRMControl;
double* pFRMControl = &FRMControl;

//Specify the links and initial tuning parameters
PID myPIDRight(pfr_FRMPID, pFRMControl, &SetpointRight, 20, 0.04, 600, DIRECT);

static WORKING_AREA(fr_RightmotorPID, 100);

static msg_t Thread3(void *arg) {

	//initialize the variables we're linked to
	SetpointRight = 8;

	//turn the PID on
	myPIDRight.SetMode(AUTOMATIC);

	myPIDRight.SetControllerDirection(REVERSE);
	myPIDRight.SetOutputLimits(40, 225);

	while (1){
		myPIDRight.Compute();
	}
	return 0;
}

