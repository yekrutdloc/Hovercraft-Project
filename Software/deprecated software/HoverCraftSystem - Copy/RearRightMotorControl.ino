const int rearRightMotorPin = 4;

static WORKING_AREA(br_RightmotorControl, 100);

static msg_t Thread10(void *arg) {

	pinMode(rearRightMotorPin, OUTPUT);


	while (1){
		analogWrite(rearRightMotorPin, (*pBRMControl / 1.5));
		//Serial.println((*pFLMControl / 1.5));
	}
	return 0;
}

