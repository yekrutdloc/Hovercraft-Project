const int frontRightMotorPin = 2;

static void Thread8(void *arg) {

	pinMode(frontRightMotorPin, OUTPUT);


	while (1){
		analogWrite(frontRightMotorPin, (*pFRMControl));
		//Serial.println((*pFLMControl / 1.5));
	}
}
