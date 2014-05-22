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

extern int runFrontCalibration = 0;
extern int runRearCalibration = 0;
extern int startDriving = 0;

//Buzzer-beep Semaphore
//xSemaphoreHandle buzzerSem;
//extern double* pbuzzerSem = &buzzerSem;

void setup() {
	// Start serial
	Serial.begin(38400);

	//Makes sure calibration-programs doesnt run automatically at start
	runFrontCalibration = 0;
	runRearCalibration = 0;
	startDriving = 0;

	// Tasks for front systems
	xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //FrontLineSensorSystem
	xTaskCreate(Thread3, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //FrontLeftMotorPID
	xTaskCreate(Thread4, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //FrontRIghtMotorPID
	xTaskCreate(Thread7, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //FrontLeftMotorControl
	xTaskCreate(Thread8, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //FrontRightMotorControl

	// Tasks for rear systems
	xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //RearLineSensorSystem
	xTaskCreate(Thread5, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //RearLeftMotorPID
	xTaskCreate(Thread6, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //RearRightMotorPID
	xTaskCreate(Thread9, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //RearLeftMotorControl
	xTaskCreate(Thread10, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //RearRightMotorControl

	//Tasks for forwardPropulsionFan
	//xTaskCreate(Thread11, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //LiftFanMotorControl

	//Tasks for Liftfan
	xTaskCreate(Thread12, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //LiftFanMotorControl

	//Tasks for additional functions
	//xTaskCreate(Thread13, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //Buzzer
	xTaskCreate(Thread14, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //BluetoothModule


	// start scheduler
	vTaskStartScheduler();

	Serial.println(F("Insufficient RAM"));

	while (1);
}

void loop() {
	// Not used

}