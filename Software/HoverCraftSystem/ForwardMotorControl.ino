const int forwardPropulsionMotorPin = 6;

int forwardPropulsionForce = 100;

static void Thread11(void *arg) {

	pinMode(forwardPropulsionMotorPin, OUTPUT);

	while (1){
		analogWrite(forwardPropulsionMotorPin, forwardPropulsionForce);
	}
}
