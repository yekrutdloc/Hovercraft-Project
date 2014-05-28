// This Sketch contains actual code for controlling and receiving values from the line sensor modules
// It's capable of reading each photoresistor connected to the multiplex, by using a function to switch 
// to each channel and store its value in an array
// After reading all phototransistor values at that time, a filterloop-functions are executed,
// which is a function within LineSensorFilter.
// The thread loop has a delay of 50ms, with the time it takes to read all the values,
// a single run through the loop takes between 100-200ms

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

// Thread1-function for FreeRTOS
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

	//END of one-run setup program
	while (1){ //Start of infinite loop for thread

		fr_getPhotoArrayValues();
		fr_filterLoop();
		re_getPhotoArrayValues();
		re_filterLoop();
	//	Print out raw values for front sensor
		//for (int i = 0; i < 16; i++)
		//{
		//	Serial.print(reLS_RAW[i]);
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

	vTaskDelay((50L * configTICK_RATE_HZ) / 1000L); //100ms delay
	}
}


// Function to cycle through each multiplex-channel and store photoresistor value.
// When running the functions to read all the photoresistor values, the reading occurs twice, and then average is calculated,
// this occurs to mildy cancel out any noise and spikes of the phototransistor sensors, before sending them out for PID-regulation
void fr_getPhotoArrayValues() {
	for (int i = 0; i < 2; i++){
		for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
			switch (photoChannel) {
			case 0:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 1:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 2:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 3:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 4:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 5:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 6:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 7:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, HIGH);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;

			case 8:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 9:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 10:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 11:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, HIGH);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 12:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 13:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, HIGH);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 14:
				digitalWrite(frMux_s0Pin, HIGH);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			case 15:
				digitalWrite(frMux_s0Pin, LOW);
				digitalWrite(frMux_s1Pin, LOW);
				digitalWrite(frMux_s2Pin, LOW);
				digitalWrite(frMux_s3Pin, LOW);
				vTaskDelay((1L * configTICK_RATE_HZ) / 1000L);
				frLS_RAW[photoChannel] += analogRead(frMux_zPin);
				break;
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		frLS_RAW[i] = frLS_RAW[i] / 2;
	}
}

void re_getPhotoArrayValues() {
	for (int i = 0; i < 3; i++){
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
		reLS_RAW[i] = reLS_RAW[i] / 3;
	}
}