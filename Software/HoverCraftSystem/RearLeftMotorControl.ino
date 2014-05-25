const int rearLeftMotorPin = 4;

static void Thread9(void *arg) {
	
	pinMode(rearLeftMotorPin, OUTPUT);

	while (1){
		analogWrite(rearLeftMotorPin, (*pBLMControl));
		//Serial.println((*pFLMControl / 1.5));
	}
}

