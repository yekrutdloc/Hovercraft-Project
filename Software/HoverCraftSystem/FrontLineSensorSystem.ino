// Front Line-Sensor pins
int const s0pin = 53;
int const s1pin = 52;
int const s2pin = 51;
int const s3pin = 50;
int const mux_1 = A1;

// buzzer pin
int const buzzerPin = 47;

// Front Line Sensor variables
int const fr_BlackSensitivity = 60;
int fr_AdcValues[16];
int fr_BlackValues[16];
int fr_WhiteValues[16];
int fr_difference[16];
int fr_range[16];
int fr_PercentValues[16];
int fr_OneZeroValues[16];
int fr_linePosition;

static WORKING_AREA(fr_LineSensorSystem, 64);

static msg_t Thread1(void *arg) {

	// Photo resistor array setup
	pinMode(s0pin, OUTPUT);    // s0
	pinMode(s1pin, OUTPUT);    // s1
	pinMode(s2pin, OUTPUT);    // s2
	pinMode(s3pin, OUTPUT);    // 3s

	pinMode(buzzerPin, OUTPUT);    // buzzer setup
	digitalWrite(buzzerPin, LOW);

	getPhotoArrayValues();

	chThdSleepMilliseconds(200);

	fr_blackValueCalibration();

	runBuzzerBeep();
	chThdSleepMilliseconds(6000);
	getPhotoArrayValues();
	fr_whiteValueCalibration();

	runBuzzerBeep();
	chThdSleepMilliseconds(2000);
	
	fr_findRange();

	while (1) {
		// Get values
		getPhotoArrayValues();

		for (int j = 0; j < 16; j++) {
			fr_PercentValues[j] = (double)100*( fr_AdcValues[j] - fr_BlackValues[j] ) / fr_range[j] ;
		}

		for (int i = 0; i < 16; i++) {
			Serial.print(fr_PercentValues[i]);
			Serial.print("-");
		}
		Serial.println(" "); //newline

		// Convert analog values to 1 or 0
		//for (int i = 0; i < 16; i++) {
		//	if (fr_MergedValues[i] >(fr_BlackValues[i] + frontSensitivity)) {
		//		fr_OneZeroValues[i] = 0;
		//		Serial.print(0);
		//	}
		//	else {
		//		fr_OneZeroValues[i] = 1;
		//		Serial.print(1);
		//	}
		//	Serial.print("-");
		//}
		//Serial.println(" "); //newline
	}// end of loop
	return 0;
}

void fr_DiffCalibration(){
	// Line-Follow Sensor Calibration program
	chThdSleepMilliseconds(2000); // Wait 2 seconds before running calibration program
	getPhotoArrayValues(); // Get each photoresistor value


	// Sums together all photoresistor values
	int sumADC = 0;
	for (int j = 0; j < 16; j++){
		sumADC = fr_AdcValues[j];
	}

	// Calculates the average value
	int average = sumADC / 16;

	// Calculates fr_difference from average value of each photoresistor

	for (int j = 0; j < 16; j++){
		fr_difference[j] = fr_AdcValues[j] - average;
	}

}

void fr_blackValueCalibration(){
	for (int j = 0; j < 16; j++) {
		fr_BlackValues[j] = fr_AdcValues[j];
	}
}

void fr_whiteValueCalibration(){
	for (int j = 0; j < 16; j++) {
		fr_WhiteValues[j] = fr_AdcValues[j];
	}
}

void fr_findRange(){
	for (int j = 0; j < 16; j++) {
		fr_range[j] = fr_WhiteValues[j] - fr_BlackValues[j];
	}
}

// Function to cycle through each multiplex-channel and store photoresistor value
void getPhotoArrayValues() {
	for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
		switch (photoChannel) {
		case 0:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 1:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 2:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 3:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 4:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 5:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 6:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 7:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, LOW);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 8:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 9:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 10:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 11:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, LOW);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 12:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 13:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, LOW);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 14:
			digitalWrite(s0pin, LOW);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 15:
			digitalWrite(s0pin, HIGH);
			digitalWrite(s1pin, HIGH);
			digitalWrite(s2pin, HIGH);
			digitalWrite(s3pin, HIGH);
			fr_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		}
	}
}

void runBuzzerBeep(){
	digitalWrite(buzzerPin, HIGH);
	chThdSleepMilliseconds(75);
	digitalWrite(buzzerPin, LOW);
}