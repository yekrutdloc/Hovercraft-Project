
void mainThread() {

	Serial.begin(9600); // Start Serial

	chThdCreateStatic(fr_LineSensorSystem, sizeof(fr_LineSensorSystem),
		NORMALPRIO + 2, Thread1, NULL);

	while (1) {
		// Infinite loop to keep all threads running
	}
}
