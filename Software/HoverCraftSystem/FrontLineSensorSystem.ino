// Front Line-Sensor pins
int const s0pin = 53;
int const s1pin = 52;
int const s2pin = 51;
int const s3pin = 50;
int const mux_1 = A1;


// buzzer pin
int const fr_buzzerPin = 31;

// Front Line Sensor variables
int const fr_BlackSensitivity = 40;
int fr_AdcValues[16];
int fr_BlackValues[16];
int fr_WhiteValues[16];
int fr_difference[16];
int fr_range[16];
int fr_PercentValues[16];
int fr_PercentValues_Middle[17];
int fr_OneZeroValues[17];
int fr_OneArray[17];
double fr_LinePosition;
double fr_FRMPID;
double fr_FLMPID;
double* pfr_FRMPID = &fr_FRMPID;
double* pfr_FLMPID = &fr_FLMPID;

static void Thread1(void *arg) {

	// Photo resistor array setup
	pinMode(s0pin, OUTPUT);    // s0
	pinMode(s1pin, OUTPUT);    // s1
	pinMode(s2pin, OUTPUT);    // s2
	pinMode(s3pin, OUTPUT);    // 3s

	pinMode(fr_buzzerPin, OUTPUT);    // buzzer setup
	digitalWrite(fr_buzzerPin, LOW);

	while (!runFrontCalibration){
		vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
	}

	runFrontCalibration = 0;

	frontCalibration();

	while (!startDriving){
		vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
	}

	while (1) {

		if (runFrontCalibration){
			frontCalibration();
			runFrontCalibration = 0;
			startDriving = 0;
		}

		while (!startDriving){
			vTaskDelay((100L * configTICK_RATE_HZ) / 1000L);
		}

		// Get values
		fr_getPhotoArrayValues();


		//for (int i = 0; i < 16; i++)
		//{
		//	Serial.print(fr_AdcValues[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println();

		for (int j = 0; j < 16; j++) {
			fr_PercentValues[j] = (double)100 * (fr_AdcValues[j] - fr_BlackValues[j]) / fr_range[j];
		}


		int middle_value = (fr_PercentValues[7] + fr_PercentValues[8]) / 2;


		for (int j = 0; j < 8; j++) {
			fr_PercentValues_Middle[j] = fr_PercentValues[j];
		}

		fr_PercentValues_Middle[8] = middle_value;

		for (int j = 9; j < 17; j++) {
			fr_PercentValues_Middle[j] = fr_PercentValues[j - 1];
		}

		vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);




		for (int j = 0; j < 17; j++) {

			if (fr_PercentValues_Middle[j] < fr_BlackSensitivity){
				fr_OneZeroValues[j] = 1;
			}

			else{
				fr_OneZeroValues[j] = 0;
			}
		}

		int counter = 0;

		for (int i = 0; i < 17; i++){
			if (fr_OneZeroValues[i] == 1){
				fr_OneArray[counter] = i;
				counter++;
			}
		}



		int temp = 0;

		for (int i = 0; i < counter; i++){
			temp = temp + fr_OneArray[i];
		}

		int min_index = temp / counter;

		if (counter == 0){
			min_index = 8;
		}



		if (min_index > 9){
			fr_FLMPID = min_index;
			fr_FRMPID = 8;
		}
		if (min_index < 9){
			fr_FLMPID = 8;
			fr_FRMPID = -1 * (min_index - 16);
		}

		//Serial.print("Front|  ");
		//Serial.print("FL: ");
		//Serial.print(fr_FLMPID);
		//Serial.print("  FR: ");
		//Serial.print(fr_FRMPID);
		//Serial.println();

	}// end of loop
}

void fr_DiffCalibration(){
	// Line-Follow Sensor Calibration program
	vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);// Wait 2 seconds before running calibration program
	fr_getPhotoArrayValues(); // Get each photoresistor value


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
void fr_getPhotoArrayValues() {
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

void frontCalibration(){
	Serial.println("Ran Front Calibration! ");

	vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

	fr_getPhotoArrayValues();

	vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

	fr_blackValueCalibration();

	//xSemaphoreGive(*pbuzzerSem);
	fr_runBuzzerBeep();
	vTaskDelay((6000L * configTICK_RATE_HZ) / 1000L);

	fr_getPhotoArrayValues();
	fr_whiteValueCalibration();

	fr_runBuzzerBeep();
	//xSemaphoreGive(*pbuzzerSem);
	vTaskDelay((2000L * configTICK_RATE_HZ) / 1000L);

	fr_findRange();
}

void fr_runBuzzerBeep(){
	digitalWrite(fr_buzzerPin, HIGH);
	vTaskDelay((75L * configTICK_RATE_HZ) / 1000L);
	digitalWrite(fr_buzzerPin, LOW);
}

