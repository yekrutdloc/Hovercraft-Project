#include <ChibiOS_ARM.h>
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
	chBegin(mainThread); // Start threads
	while (1) {
	}
}

void loop() {
	// Not used

}