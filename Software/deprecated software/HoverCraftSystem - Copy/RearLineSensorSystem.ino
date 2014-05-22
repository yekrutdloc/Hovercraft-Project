// Front Line-Sensor pins
int const s4pin = 53;
int const s5pin = 52;
int const s6pin = 51;
int const s7pin = 50;
int const mux_2 = A0;

// buzzer pin
int const br_buzzerPin = 31;

// Front Line Sensor variables
int const br_BlackSensitivity = 60;
int br_AdcValues[16];
int br_BlackValues[16];
int br_WhiteValues[16];
int br_difference[16];
int br_range[16];
int br_PercentValues[16];
int br_PercentValues_Middle[17];
int br_OneZeroValues[17];
int br_OneArray[17];
double br_LinePosition;
double br_BRMPID;
double br_BLMPID;
double* pbr_BRMPID = &br_BRMPID;
double* pbr_BLMPID = &br_BLMPID;


static WORKING_AREA(waThread12, 64);

static msg_t Thread6(void *arg) {

	// Photo resistor array setup
	pinMode(s4pin, OUTPUT);    // s0
	pinMode(s5pin, OUTPUT);    // s1
	pinMode(s6pin, OUTPUT);    // s2
	pinMode(s7pin, OUTPUT);    // 3s

	pinMode(br_buzzerPin, OUTPUT);    // buzzer setup
	digitalWrite(br_buzzerPin, LOW);

	br_getPhotoArrayValues();

	chThdSleepMilliseconds(200);

	br_blackValueCalibration();

	br_runBuzzerBeep();
	chThdSleepMilliseconds(6000);
	br_getPhotoArrayValues();
	br_whiteValueCalibration();

	br_runBuzzerBeep();
	chThdSleepMilliseconds(2000);

	br_findRange();

	while (1) {
		// Get values
		br_getPhotoArrayValues();

		for (int j = 0; j < 16; j++) {
			br_PercentValues[j] = (double)100 * (br_AdcValues[j] - br_BlackValues[j]) / br_range[j];
		}


		int middle_value = (br_PercentValues[7] + br_PercentValues[8]) / 2;


		for (int j = 0; j < 8; j++) {
			br_PercentValues_Middle[j] = br_PercentValues[j];
		}

		br_PercentValues_Middle[8] = middle_value;

		for (int j = 9; j < 17; j++) {
			br_PercentValues_Middle[j] = br_PercentValues[j - 1];
		}


		chThdSleepMilliseconds(10);


		for (int j = 0; j < 17; j++) {

			if (br_PercentValues_Middle[j] < br_BlackSensitivity){
				br_OneZeroValues[j] = 1;
			}

			else{
				br_OneZeroValues[j] = 0;
			}
		}

		int counter = 0;

		for (int i = 0; i < 17; i++){
			if (br_OneZeroValues[i] == 1){
				br_OneArray[counter] = i;
				counter++;
			}
		}



		int temp = 0;

		for (int i = 0; i < counter; i++){
			temp = temp + br_OneArray[i];
		}

		int min_index = temp / counter;

		if (counter == 0){
			min_index = 8;
		}


		if (min_index > 9){
			br_BLMPID = min_index;
			br_BRMPID = 8;
		}
		if (min_index < 9){
			br_BLMPID = 8;
			br_BRMPID = -1 * (min_index - 16);
		}


	}// end of loop
	return 0;
}

void br_DiffCalibration(){
	// Line-Follow Sensor Calibration program
	chThdSleepMilliseconds(2000); // Wait 2 seconds before running calibration program
	br_getPhotoArrayValues(); // Get each photoresistor value


	// Sums together all photoresistor values
	int sumADC = 0;
	for (int j = 0; j < 16; j++){
		sumADC = br_AdcValues[j];
	}

	// Calculates the average value
	int average = sumADC / 16;

	// Calculates br_difference from average value of each photoresistor

	for (int j = 0; j < 16; j++){
		br_difference[j] = br_AdcValues[j] - average;
	}

}

void br_blackValueCalibration(){
	for (int j = 0; j < 16; j++) {
		br_BlackValues[j] = br_AdcValues[j];
	}
}

void br_whiteValueCalibration(){
	for (int j = 0; j < 16; j++) {
		br_WhiteValues[j] = br_AdcValues[j];
	}
}

void br_findRange(){
	for (int j = 0; j < 16; j++) {
		br_range[j] = br_WhiteValues[j] - br_BlackValues[j];
	}
}

// Function to cycle through each multiplex-channel and store photoresistor value
void br_getPhotoArrayValues() {
	for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
		switch (photoChannel) {
		case 0:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 1:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 2:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 3:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 4:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 5:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 6:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 7:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 8:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 9:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 10:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 11:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 12:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 13:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 14:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		case 15:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_1);
			break;
		}
	}
}

void br_runBuzzerBeep(){
	digitalWrite(br_buzzerPin, HIGH);
	chThdSleepMilliseconds(75);
	digitalWrite(br_buzzerPin, LOW);
}
