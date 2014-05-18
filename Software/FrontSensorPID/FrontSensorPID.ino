#include <ChibiOS_ARM.h>

void setup() {
  Serial.begin(9600); // Start Serial

  chBegin(mainThread); // Start threads
  while (1) {
  }
}

void loop() {
  // not used
}
