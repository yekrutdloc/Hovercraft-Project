const int rearLeftMotorPin = 5;

static WORKING_AREA(br_LeftmotorControl, 100);

static msg_t Thread7(void *arg) {

	pinMode(rearLeftMotorPin, OUTPUT);


	while (1){
		analogWrite(rearLeftMotorPin, (*pBLMControl / 1.5));

	}
	return 0;
}

