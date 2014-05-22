const int frontLeftMotorPin = 3;

static WORKING_AREA(fr_LeftmotorControl, 100);

static msg_t Thread4(void *arg) {

	pinMode(frontLeftMotorPin, OUTPUT);


	while (1){
		analogWrite(frontLeftMotorPin, (*pFLMControl/ 1.5));
		//Serial.println((*pFLMControl / 1.5));
	}
	return 0;
}
