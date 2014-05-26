char recievedChar = 'a';

static void Thread9(void *arg) {
	Serial.print(recievedChar);
	while (1){
		if (Serial.available()) {
			recievedChar = Serial.read();
			Serial.print(recievedChar);
			if (recievedChar=='1'){
				runFrontCalibration = 1;
			}
			if (recievedChar == '2'){
				runRearCalibration = 1;
			}
			if (recievedChar == '3'){
				startDriving = 1;
			}
		}
	}
}