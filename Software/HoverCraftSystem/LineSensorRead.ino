
// Front Line-Sensor pins
int const frMux_s0Pin = 53;
int const frMux_s1Pin = 52;
int const frMux_s2Pin = 51;
int const frMux_s3Pin = 50;
int const frMux_zPin = 1;

// Rear Line-Sensor pins
int const reMux_s0Pin = 38;
int const reMux_s1Pin = 39;
int const reMux_s2Pin = 40;
int const reMux_s3Pin = 41;
int const reMux_zPin = 0;

//Raw-values
int frLS_RAW[16];
int reLS_RAW[16];

static void Thread1(void *arg) {

	// Front line sensor setup setup
	pinMode(frMux_s0Pin, OUTPUT);    // s0
	pinMode(frMux_s1Pin, OUTPUT);    // s1
	pinMode(frMux_s2Pin, OUTPUT);    // s2
	pinMode(frMux_s3Pin, OUTPUT);    // 3s

	// Photo resistor array setup
	pinMode(reMux_s0Pin, OUTPUT);    // s0
	pinMode(reMux_s1Pin, OUTPUT);    // s1
	pinMode(reMux_s2Pin, OUTPUT);    // s2
	pinMode(reMux_s3Pin, OUTPUT);    // 3s

	while (1) {

		fr_getPhotoArrayValues();

		re_getPhotoArrayValues();

		//Print out raw values for front sensor
		//for (int i = 0; i < 16; i++)
		//{
		//	Serial.print(frLS_RAW[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println(" ");

		//Print out raw values for rear sensor
		//for (int i = 0; i < 16; i++)
		//{
		//	Serial.print(reLS_RAW[i]);
		//	Serial.print(" - ");
		//}
		//Serial.println(" ");

		fr_filterLoop();
		re_filterLoop();

		// DONT FORGET TO SAMPLE RATE SET 			vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);

	}
}


// Function to cycle through each multiplex-channel and store photoresistor value
void fr_getPhotoArrayValues() {
	for (int i = 0; i < 5;	i++){
		for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
			switch (photoChannel) {
			case 0:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 1:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 2:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 3:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 4:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 5:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 6:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 7:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 8:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 9:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 10:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 11:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 12:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 13:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 14:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 15:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		frLS_RAW[i] = frLS_RAW[i] / 5;
	}
}

void re_getPhotoArrayValues() {
	for (int i = 0; i < 5; i++){
		for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
			switch (photoChannel) {
			case 0:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 1:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 2:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 3:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 4:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 5:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 6:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 7:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 8:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 9:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 10:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 11:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, LOW);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 12:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 13:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, LOW);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 14:
				digitalWrite(reMux_s0Pin, LOW);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			case 15:
				digitalWrite(reMux_s0Pin, HIGH);
				digitalWrite(reMux_s1Pin, HIGH);
				digitalWrite(reMux_s2Pin, HIGH);
				digitalWrite(reMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				reLS_RAW[photoChannel] += analogRead(reMux_zPin);
				break;
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		reLS_RAW[i] = reLS_RAW[i] / 5;
	}
}