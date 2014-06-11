/**
HoverCraftSystem.ino

Purpose: This Sketch is the actual .ino file to contain the setup- and loop-functions.
In here all the library includes are present.
Global variables which are used as communication between threads are declared
and thread-declarations of FreeRTOS threads are created and started.

@author Prince Balabis
*/

// Library includes
#include <FreeRTOS_ARM.h>
#include <PID_v1.h>

// Public variables for communication between threads
extern double* pfrRM_PIDInput;
extern double* pfrLM_PIDInput;

extern double* preRM_PIDInput;
extern double* preLM_PIDInput;

extern int frLS_RAW[16];
extern int reLS_RAW[16];

void setup() {

	// Start serial, which can be used throughout the whole program
	Serial.begin(115200);

	// Set software-ADC to 12 bit
	analogReadResolution(12);

	xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 4, NULL); //Front LineSensorSystems

	// Tasks for fan controllers
	//xTaskCreate(Thread8, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL); //LiftFanMotorController
	xTaskCreate(Thread3, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL); //FrontLeftMotorController
	xTaskCreate(Thread4, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL); //FrontRightMotorController
	xTaskCreate(Thread5, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL); //RearRightMotorController
	xTaskCreate(Thread6, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL); //RearLeftMotorController
	xTaskCreate(Thread7, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL); //ForwardPropulsionController

	//Tasks for additional functions
	//xTaskCreate(Thread9, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //Buzzer
	//xTaskCreate(Thread10, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL); //BluetoothModule

	// Start scheduler
	vTaskStartScheduler();

	Serial.println(F("Insufficient RAM"));
	while (1);
}

void loop() {
	// Not used
}