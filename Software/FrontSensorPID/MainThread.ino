void mainThread() {

  chThdCreateStatic(fr_LineSensorSystem, sizeof(fr_LineSensorSystem),
                    NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(re_LineSensorSystem, sizeof(re_LineSensorSystem),
                    NORMALPRIO + 2, Thread1, NULL);


  while (1) {
    // Infinite loop to keep all threads running
  }
}

