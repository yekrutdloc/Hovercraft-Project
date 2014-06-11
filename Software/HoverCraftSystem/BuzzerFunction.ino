/**
BuzzerFunction.ino

Purpose: This Sketch used to exist for the purpose of
returning feedback whenever an action was made.
It was former used to feedback calibration actions,
but due to different calibration algorithms,
this Sketch is currently no longer used.

@author Prince Balabis
*/

// buzzer pin
//int const fr_buzzerPin = 31;
//
//static void Thread9(void *arg) {
//
//	pinMode(fr_buzzerPin, OUTPUT);    // buzzer setup
//	digitalWrite(fr_buzzerPin, LOW);
//
//	while (1){
//		xSemaphoreTake(*pbuzzerSem, portMAX_DELAY);
//		digitalWrite(fr_buzzerPin, HIGH);
//		vTaskDelay((75L * configTICK_RATE_HZ) / 1000L);
//		digitalWrite(fr_buzzerPin, LOW);
//
//	}
//}