#include <FreeRTOS_ARM.h>

#include <PID_v1.h>

extern double* pfr_FRMPID;
extern double* pfr_FLMPID;

extern double* pbr_BRMPID;
extern double* pbr_BLMPID;

extern double* pFLMControl;
extern double* pFRMControl;

extern double* pBLMControl;
extern double* pBRMControl;


void setup() {
	portBASE_TYPE s1, s2;

	Serial.begin(9600);

	s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

	// check for creation errors
	if (s1 != pdPASS) {
		Serial.println(F("Creation problem"));
		while (1);
	}

	// start scheduler
	vTaskStartScheduler();
	Serial.println(F("Insufficient RAM"));
	while (1);

}

void loop() {
	// Not used

}