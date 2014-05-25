
// Front Line-Sensor pins
int const s4pin = 38;
int const s5pin = 39;
int const s6pin = 40;
int const s7pin = 41;
int const mux_2 = A0;

// buzzer pin
int const br_buzzerPin = 31;

// Front Line Sensor variables
int const br_BlackSensitivity = 40;
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

static void Thread2(void *arg) {

	// Photo resistor array setup
	pinMode(s4pin, OUTPUT);    // s0
	pinMode(s5pin, OUTPUT);    // s1
	pinMode(s6pin, OUTPUT);    // s2
	pinMode(s7pin, OUTPUT);    // 3s

	pinMode(br_buzzerPin, OUTPUT);    // buzzer setup
	digitalWrite(br_buzzerPin, LOW);

	while (!runRearCalibration){
		vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
	}

	runRearCalibration = 0;

	rearCalibration();

	while (!startDriving){
		vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
	}

	while (1) {

		if (runRearCalibration){
			rearCalibration();
			runRearCalibration = 0;
			startDriving = 0;
		}

		while (!startDriving){
			vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
		}

		// Get values
		br_getPhotoArrayValues();

		//// Print out Analogvalues
		/*for (int i = 0; i < 16; i++)
		{
			Serial.print(br_AdcValues[i]);
			Serial.print(" - ");
		}
		Serial.println();*/

		for (int j = 0; j < 16; j++) {
			br_PercentValues[j] = (double)100 * (br_AdcValues[j] - br_BlackValues[j]) / br_range[j];
		}

		//Print out percentvalues
		//for (int i = 0; i < 17; i++)
		//{
		//	Serial.print(br_PercentValues[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println();


		int middle_value = (br_PercentValues[7] + br_PercentValues[8]) / 2;


		for (int j = 0; j < 8; j++) {
			br_PercentValues_Middle[j] = br_PercentValues[j];
		}

		br_PercentValues_Middle[8] = middle_value;

		for (int j = 9; j < 17; j++) {
			br_PercentValues_Middle[j] = br_PercentValues[j - 1];
		}

		vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);



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

		////Print out OneZeroValues
		//for (int i = 0; i < 17; i++)
		//{
		//	Serial.print(br_OneZeroValues[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println();


		if (min_index > 9){
			br_BRMPID = min_index;
			br_BLMPID = 8;
		}
		if (min_index < 9){
			br_BRMPID = 8;
			br_BLMPID = -1 * (min_index - 16);
		}

		Serial.print("Back|  ");
		Serial.print("BL: ");
		Serial.print(br_BLMPID);
		Serial.print("  BR: ");
		Serial.print(br_BRMPID);
		Serial.println();

	}// end of loop
}

void br_DiffCalibration(){
	// Line-Follow Sensor Calibration program
	vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);// Wait 2 seconds before running calibration program
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
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 1:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 2:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 3:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 4:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 5:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 6:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 7:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, LOW);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 8:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 9:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 10:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 11:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, LOW);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 12:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 13:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, LOW);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 14:
			digitalWrite(s4pin, LOW);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		case 15:
			digitalWrite(s4pin, HIGH);
			digitalWrite(s5pin, HIGH);
			digitalWrite(s6pin, HIGH);
			digitalWrite(s7pin, HIGH);
			br_AdcValues[photoChannel] = analogRead(mux_2);
			break;
		}
	}
}

void rearCalibration(){
	Serial.println("Ran Rear Calibration! ");

	vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

	br_getPhotoArrayValues();

	vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

	br_blackValueCalibration();

	br_runBuzzerBeep();
	vTaskDelay((6000L * configTICK_RATE_HZ) / 1000L);

	br_getPhotoArrayValues();
	br_whiteValueCalibration();

	br_runBuzzerBeep();
	vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);

	br_findRange();
}

void br_runBuzzerBeep(){
	digitalWrite(br_buzzerPin, HIGH);
	vTaskDelay((75L * configTICK_RATE_HZ) / 1000L);
	digitalWrite(br_buzzerPin, LOW);
}
