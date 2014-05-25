//Define Variables we'll be connecting to
double fr_SetpointLeft = 8;

double FLMControl;
double* pFLMControl = &FLMControl;

//Specify the links and initial tuning parameters
PID fr_myPIDLeft(pfr_FLMPID, pFLMControl, &fr_SetpointLeft, 35, 0.008, 55, DIRECT);

static void Thread3(void *arg) {

	//turn the PID on
	fr_myPIDLeft.SetMode(AUTOMATIC);

	fr_myPIDLeft.SetControllerDirection(REVERSE);
	fr_myPIDLeft.SetOutputLimits(0, 200);

	while (1){
		fr_myPIDLeft.Compute();
	}
}
