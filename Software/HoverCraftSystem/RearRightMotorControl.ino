const int rearRightMotorPin = 5;

static void Thread10(void *arg) {

	pinMode(rearRightMotorPin, OUTPUT);

	while (1){
		analogWrite(rearRightMotorPin, (*pBRMControl / 1.5));
		//Serial.println((*pFLMControl / 1.5));
	}
}

