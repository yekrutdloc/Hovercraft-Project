const int frontLeftMotorPin = 3;

static void Thread7(void *arg) {

	pinMode(frontLeftMotorPin, OUTPUT);


	while (1){
		analogWrite(frontLeftMotorPin, (*pFLMControl));
		//Serial.println((*pFLMControl / 1.5));
	}
}
