////
////// buzzer pin
//int const fr_buzzerPin = 31;
//
//static void Thread13(void *arg) {
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