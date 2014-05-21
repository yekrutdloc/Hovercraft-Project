
void mainThread() {

	Serial.begin(9600); // Start Serial

	chThdCreateStatic(fr_LineSensorSystem, sizeof(fr_LineSensorSystem), NORMALPRIO + 3, Thread1, NULL);

	chThdCreateStatic(fr_LeftmotorPID, sizeof(fr_LeftmotorPID), NORMALPRIO + 2, Thread2, NULL);

	chThdCreateStatic(fr_LeftmotorControl, sizeof(fr_LeftmotorControl), NORMALPRIO + 1, Thread4, NULL);

	//chThdCreateStatic(fr_RightmotorPID, sizeof(fr_RightmotorPID), NORMALPRIO, Thread3 + 2, NULL);

	//chThdCreateStatic(fr_RightmotorControl, sizeof(fr_RightmotorControl) + 1, NORMALPRIO, Thread5, NULL);



	while (1) {
		// Infinite loop to keep all threads running
	}
}
