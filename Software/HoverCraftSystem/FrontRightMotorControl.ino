const int frontRightMotorPin = 2;

static void Thread8(void *arg) {

	pinMode(frontRightMotorPin, OUTPUT);


	while (1){
		analogWrite(frontRightMotorPin, (*pFRMControl / 1.5));
		//Serial.println((*pFLMControl / 1.5));
	}
}
