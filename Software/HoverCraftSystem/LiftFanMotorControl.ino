const int liftFanPin = 7;

int liftForce = 150;

static void Thread12(void *arg) {

	pinMode(liftFanPin, OUTPUT);

	while (1){
		analogWrite(liftFanPin, liftForce);
	}
}
