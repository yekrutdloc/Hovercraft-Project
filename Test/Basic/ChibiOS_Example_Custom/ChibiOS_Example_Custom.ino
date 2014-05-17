// Simple demo of three threads
// LED blink thread, print thread, and main thread
#include <ChibiOS_ARM.h>
// Redefine AVR Flash string macro as nop for ARM
#undef F
#define F(str) str

const uint8_t LED_PIN = 9;
const uint8_t LED_PIN2 = 10;

int photoresistor = 0;

volatile uint32_t count = 0;

//------------------------------------------------------------------------------
// thread 1 - high priority for blinking LED
// 64 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread1, 64);

static msg_t Thread1(void *arg) {
  pinMode(LED_PIN, OUTPUT);

  // Flash led every 200 ms.
  while (1) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);

    // Sleep for 50 milliseconds.
    chThdSleepMilliseconds(50);

    // Turn LED off.
    digitalWrite(LED_PIN, LOW);

    // Sleep for 150 milliseconds.
    chThdSleepMilliseconds(150);
  }
  return 0;
}
//------------------------------------------------------------------------------
// thread 2 - print main thread count every second
// 100 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread2, 64);

static msg_t Thread2(void *arg) {
  pinMode(LED_PIN2, OUTPUT);

  // Flash led every 200 ms.
  while (1) {
    // Turn LED on.
    digitalWrite(LED_PIN2, HIGH);

    // Sleep for 50 milliseconds.
    chThdSleepMilliseconds(300);

    // Turn LED off.
    digitalWrite(LED_PIN2, LOW);

    // Sleep for 150 milliseconds.
    chThdSleepMilliseconds(150);
  }
  return 0;
}

//------------------------------------------------------------------------------
// thread 2 - print main thread count every second
// 100 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread3, 100);

static msg_t Thread3(void *arg) {

  // print count every second
  while (1) {
    // Sleep for one second.
    chThdSleepMilliseconds(500);

    // Print count for previous second.
    Serial.print(F("Count: "));
    Serial.print(count);

    // Print unused stack for threads.
    Serial.print(F(", Unused Stack: "));
    Serial.print(chUnusedStack(waThread1, sizeof(waThread1)));
    Serial.print(' ');
    Serial.print(chUnusedStack(waThread2, sizeof(waThread2)));
    Serial.print(' ');
    Serial.print(chUnusedStack(waThread3, sizeof(waThread3)));
    Serial.print(' ');
    //    Serial.print(chUnusedStack(waThread4, sizeof(waThread4)));
    //    Serial.print(' ');
    Serial.println(chUnusedHeapMain());
    Serial.print(F("Photoresistor: "));
    Serial.println(photoresistor);

    // Zero count.
    count = 0;
  }
}

//------------------------------------------------------------------------------
// thread 2 - print main thread count every second
// 100 byte stack beyond task switch and interrupt needs
static WORKING_AREA(waThread4, 64);

static msg_t Thread4(void *arg) {

  // print count every second
  while (1) {
    photoresistor = analogRead(A0);
    chThdSleepMilliseconds(100);
  }
}

static WORKING_AREA(waThread5, 64);

static msg_t Thread5(void *arg) {

  pinMode(7, OUTPUT);

  // print count every second
  while (1) {
    for (int i = 0; i < 255; i++) {
      analogWrite(7, i);
      chThdSleepMilliseconds(10);
    }
  }
}

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  // wait for USB Serial
  while (!Serial) {}

  // read any input
  delay(200);
  while (Serial.read() >= 0) {}

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()
  while (1) {}
}
//------------------------------------------------------------------------------
// main thread runs at NORMALPRIO
void mainThread() {


  chThdCreateStatic(waThread1, sizeof(waThread1),
                    NORMALPRIO + 2, Thread1, NULL);


  chThdCreateStatic(waThread2, sizeof(waThread2),
                    NORMALPRIO + 1, Thread2, NULL);


  chThdCreateStatic(waThread3, sizeof(waThread3),
                    NORMALPRIO + 3, Thread3, NULL);


  chThdCreateStatic(waThread4, sizeof(waThread4),
                    NORMALPRIO + 4, Thread4, NULL);

  chThdCreateStatic(waThread5, sizeof(waThread5),
                    NORMALPRIO + 5, Thread5, NULL);

  // increment counter
  while (1) {
    // must insure increment is atomic in case of context switch for print
    // should use mutex for longer critical sections
    noInterrupts();
    count++;
    interrupts();
  }
}
//------------------------------------------------------------------------------
void loop() {
  // not used
}
