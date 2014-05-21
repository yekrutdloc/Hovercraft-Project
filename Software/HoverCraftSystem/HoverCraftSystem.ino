#include <ChibiOS_ARM.h>
#include <PID_v1.h>

extern double* pfr_FRMPID;
extern double* pfr_FLMPID;

extern double* pFLMControl;
extern double* pFRMControl;


void setup() {
	chBegin(mainThread); // Start threads
	while (1) {
	}
}

void loop() {
	// Not used

}