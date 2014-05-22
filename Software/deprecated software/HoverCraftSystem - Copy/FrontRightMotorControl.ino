const int frontRightMotorPin = 2;

static WORKING_AREA(fr_RightmotorControl, 100);

static msg_t Thread5(void *arg) {

	pinMode(frontRightMotorPin, OUTPUT);


	while (1){
		analogWrite(frontRightMotorPin, (*pFRMControl / 1.5));
		//Serial.println((*pFLMControl / 1.5));
	}
	return 0;
}
