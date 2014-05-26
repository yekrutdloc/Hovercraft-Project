
// Front Line-Sensor pins
int const frMux_s0Pin = 53;
int const frMux_s1Pin = 52;
int const frMux_s2Pin = 51;
int const frMux_s3Pin = 50;
int const frMux_zPin = A1;



// buzzer pin
int const fr_buzzerPin = 31;

// USING
int fr_AdcValues[16];
int fr_ADCwithMiddle[17];
int fr_sorted_ADCwithMiddle[17];
int fr_OneZeroValues[17];
int fr_OneArray[17];
double fr_LinePosition;
double frRM_PIDInput;
double frLM_PIDInput;
double* pfrRM_PIDInput = &frRM_PIDInput;
double* pfrLM_PIDInput = &frLM_PIDInput;

static void Thread1(void *arg) {

	// Photo resistor array setup
	pinMode(frMux_s0Pin, OUTPUT);    // s0
	pinMode(frMux_s1Pin, OUTPUT);    // s1
	pinMode(frMux_s2Pin, OUTPUT);    // s2
	pinMode(frMux_s3Pin, OUTPUT);    // 3s

	pinMode(fr_buzzerPin, OUTPUT);    // buzzer setup
	digitalWrite(fr_buzzerPin, LOW);

	while (1) {

		fr_getPhotoArrayValues();

		int middle_value = (fr_AdcValues[7] + fr_AdcValues[8]) / 2;

		for (int j = 0; j < 8; j++) {
			fr_ADCwithMiddle[j] = fr_AdcValues[j];
		}

		fr_ADCwithMiddle[8] = middle_value;

		for (int j = 9; j < 17; j++) {
			fr_ADCwithMiddle[j] = fr_AdcValues[j - 1];
		}

		for (int i = 0; i < 17; i++){
			fr_sorted_ADCwithMiddle[i] = fr_ADCwithMiddle[i];
		}

		quick_sort(fr_sorted_ADCwithMiddle, 0, 16);

		int lowest_three, highest_three = 0;

		for (int i = 0; i < 2; i++){
			lowest_three = lowest_three + fr_sorted_ADCwithMiddle[i];
		}

		lowest_three = lowest_three / 3;

		for (int i = 14; i < 17; i++){
			highest_three = highest_three + fr_sorted_ADCwithMiddle[i];
		}

		highest_three = highest_three / 3;

		int line_exist = 0;
		double spridning;

		spridning = (double)(highest_three - lowest_three) / highest_three;

		if (spridning > 0.20){
			line_exist = 1;
		}
		else{
			line_exist = 0;
		}

		if (line_exist){

			for (int i = 0; i < 17; i++){
				if (fr_ADCwithMiddle[i] < (fr_sorted_ADCwithMiddle[16] * 0.8)){
					fr_OneZeroValues[i] = 1;
				}

				else{
					fr_OneZeroValues[i] = 0;
				}
			}

		}

		else{

			for (int i = 0; i < 17; i++){

				fr_OneZeroValues[i] = 0;

			}

		}

		vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

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

		Serial.println(min_index);

		if (min_index > 9){
			frLM_PIDInput = min_index;
			frLM_PIDInput = 8;
		}
		if (min_index < 9){
			frLM_PIDInput = 8;
			frLM_PIDInput = -1 * (min_index - 16);
		}
	}
}

void quick_sort(int fr_sorted_ADCwithMiddle[17], int low, int high)
{
	int pivot, j, temp, i;
	if (low<high)
	{
		pivot = low;
		i = low;
		j = high;

		while (i<j)
		{
			while ((fr_sorted_ADCwithMiddle[i] <= fr_sorted_ADCwithMiddle[pivot]) && (i<high))
			{
				i++;
			}

			while (fr_sorted_ADCwithMiddle[j]>fr_sorted_ADCwithMiddle[pivot])
			{
				j--;
			}

			if (i<j)
			{
				temp = fr_sorted_ADCwithMiddle[i];
				fr_sorted_ADCwithMiddle[i] = fr_sorted_ADCwithMiddle[j];
				fr_sorted_ADCwithMiddle[j] = temp;
			}
		}

		temp = fr_sorted_ADCwithMiddle[pivot];
		fr_sorted_ADCwithMiddle[pivot] = fr_sorted_ADCwithMiddle[j];
		fr_sorted_ADCwithMiddle[j] = temp;
		quick_sort(fr_sorted_ADCwithMiddle, low, j - 1);
		quick_sort(fr_sorted_ADCwithMiddle, j + 1, high);
	}
}

// Function to cycle through each multiplex-channel and store photoresistor value
void fr_getPhotoArrayValues() {
	for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
		switch (photoChannel) {
		case 0:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 1:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 2:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 3:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 4:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 5:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 6:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 7:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 8:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 9:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 10:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 11:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, LOW);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 12:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 13:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, LOW);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 14:
			digitalWrite(frMux_s0Pin, LOW);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		case 15:
			digitalWrite(frMux_s0Pin, HIGH);
			digitalWrite(frMux_s1Pin, HIGH);
			digitalWrite(frMux_s2Pin, HIGH);
			digitalWrite(frMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			fr_AdcValues[photoChannel] = analogRead(frMux_zPin);
			break;
		}
	}
}