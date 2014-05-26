
// Rear Line-Sensor pins
int const reMux_s0Pin = 38;
int const reMux_s1Pin = 39;
int const reMux_s2Pin = 40;
int const reMux_s3Pin = 41;
int const reMux_zPin = A0;

// buzzer pin
int const re_buzzerPin = 31;

// USING
int re_AdcValues[16];
int re_ADCwithMiddle[17];
int re_sorted_ADCwithMiddle[17];
int re_OneZeroValues[17];
int re_OneArray[17];
double re_LinePosition;
double reRM_PIDInput;
double reLM_PIDInput;
double* preRM_PIDInput = &reRM_PIDInput;
double* preLM_PIDInput = &reLM_PIDInput;

static void Thread2(void *arg) {
	Serial.begin(9600);
	// Photo resistor array setup
	pinMode(reMux_s0Pin, OUTPUT);    // s0
	pinMode(reMux_s1Pin, OUTPUT);    // s1
	pinMode(reMux_s2Pin, OUTPUT);    // s2
	pinMode(reMux_s3Pin, OUTPUT);    // 3s

	pinMode(re_buzzerPin, OUTPUT);    // buzzer setup
	digitalWrite(re_buzzerPin, LOW);

	while (1) {

		re_getPhotoArrayValues();

		//for (int i = 0; i < 16; i++)
		//{
		//	Serial.print(re_AdcValues[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println(" ");

		int middle_value = (re_AdcValues[7] + re_AdcValues[8]) / 2;

		for (int j = 0; j < 8; j++) {
			re_ADCwithMiddle[j] = re_AdcValues[j];
		}

		re_ADCwithMiddle[8] = middle_value;

		for (int j = 9; j < 17; j++) {
			re_ADCwithMiddle[j] = re_AdcValues[j - 1];
		}

		//for (int i = 0; i < 17; i++)
		//{
		//	Serial.print(re_ADCwithMiddle[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println(" ");

		for (int i = 0; i < 17; i++){
			re_sorted_ADCwithMiddle[i] = re_ADCwithMiddle[i];
		}

		re_quick_sort(re_sorted_ADCwithMiddle, 0, 16);

		int lowest_three, highest_three = 0;

		for (int i = 0; i < 2; i++){
			lowest_three = lowest_three + re_sorted_ADCwithMiddle[i];
		}

		lowest_three = lowest_three / 3;

		for (int i = 14; i < 17; i++){
			highest_three = highest_three + re_sorted_ADCwithMiddle[i];
		}

		highest_three = highest_three / 3;

		int line_exist = 0;
		double spridning;

		spridning = (double)(highest_three - lowest_three) / highest_three;

		//Serial.print("Spridning: ");
		//Serial.println(spridning);

		if (spridning > 0.40){
			line_exist = 1;
		}
		else{
			line_exist = 0;
		}

		//Serial.print("Line Exist: ");
		//Serial.println(line_exist);

		if (line_exist){

			for (int i = 0; i < 17; i++){
				if (re_ADCwithMiddle[i] < (re_sorted_ADCwithMiddle[16] * 0.55)){
					re_OneZeroValues[i] = 1;
				}

				else{
					re_OneZeroValues[i] = 0;
				}
			}

		}

		else{

			for (int i = 0; i < 17; i++){

				re_OneZeroValues[i] = 0;

			}

		}

		//for (int i = 0; i < 16; i++)
		//{
		//	Serial.print(re_OneZeroValues[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println(" ");

		vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

		int counter = 0;

		for (int i = 0; i < 17; i++){
			if (re_OneZeroValues[i] == 1){
				re_OneArray[counter] = i;
				counter++;
			}
		}

		int temp = 0;

		for (int i = 0; i < counter; i++){
			temp = temp + re_OneArray[i];
		}

		int min_index = temp / counter;


		int last_turn;

		if (min_index < 2){
			last_turn = 0;
		}
		else if (min_index > 13){
			last_turn = 1;
		}

		if (counter == 0){

				//if (last_turn){
				//	min_index = 13;
				//}
				//else if(!last_turn){
				//	min_index = 3;
				//}

			min_index = 8;
		}



		//Serial.println(min_index);

		if (min_index > 9){
			reRM_PIDInput = min_index;
			reLM_PIDInput = 8;
		}
		if (min_index < 9){
			reRM_PIDInput = 8;
			reLM_PIDInput = -1 * (min_index - 16);
		}

	/*		Serial.print("Right - ");
		Serial.print(reRM_PIDInput);
		Serial.print(" - Left");
		Serial.println(reLM_PIDInput);*/
	}
}

void re_quick_sort(int re_sorted_ADCwithMiddle[17], int low, int high)
{
	int pivot, j, temp, i;
	if (low < high)
	{
		pivot = low;
		i = low;
		j = high;

		while (i < j)
		{
			while ((re_sorted_ADCwithMiddle[i] <= re_sorted_ADCwithMiddle[pivot]) && (i < high))
			{
				i++;
			}

			while (re_sorted_ADCwithMiddle[j] > re_sorted_ADCwithMiddle[pivot])
			{
				j--;
			}

			if (i < j)
			{
				temp = re_sorted_ADCwithMiddle[i];
				re_sorted_ADCwithMiddle[i] = re_sorted_ADCwithMiddle[j];
				re_sorted_ADCwithMiddle[j] = temp;
			}
		}

		temp = re_sorted_ADCwithMiddle[pivot];
		re_sorted_ADCwithMiddle[pivot] = re_sorted_ADCwithMiddle[j];
		re_sorted_ADCwithMiddle[j] = temp;
		re_quick_sort(re_sorted_ADCwithMiddle, low, j - 1);
		re_quick_sort(re_sorted_ADCwithMiddle, j + 1, high);
	}
}

// Function to cycle through each multiplex-channel and store photoresistor value
void re_getPhotoArrayValues() {
	for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
		switch (photoChannel) {
		case 0:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 1:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 2:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 3:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 4:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 5:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 6:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 7:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, LOW);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 8:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 9:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 10:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 11:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, LOW);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 12:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 13:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, LOW);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 14:
			digitalWrite(reMux_s0Pin, LOW);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		case 15:
			digitalWrite(reMux_s0Pin, HIGH);
			digitalWrite(reMux_s1Pin, HIGH);
			digitalWrite(reMux_s2Pin, HIGH);
			digitalWrite(reMux_s3Pin, HIGH);
			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
			re_AdcValues[photoChannel] = analogRead(reMux_zPin);
			break;
		}
	}
}