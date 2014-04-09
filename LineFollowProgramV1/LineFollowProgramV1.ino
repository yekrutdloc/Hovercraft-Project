// 433 MHz library
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

int buzzerPin = 30; // Buzzer

// Photoresistor array variables
int lightFollowModuleFrontPins[] = {0, 1, 2, 3};
int lightFollowModuleBackPins[] = {4, 5, 6, 7};
int const photoAmount = 4;
int photoFrontWhiteValues[photoAmount];
int photoFrontWhiteCal = 0;
int photoFrontBlackValues[photoAmount];
int photoFrontBlackCal = 0;
int photoBackWhiteValues[photoAmount];
int photoBackWhiteCal = 0;
int photoBackBlackValues[photoAmount];
int photoBackBlackCal = 0;

// Setup function
void setup() {
  //  Serial.begin(9600);
  SerialUSB.begin(9600);

  //Buzzer Setup
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Setup 433 MHz Radio reciever
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 --> RX0
}

// Loop function
void loop() {

  // Check 433 MHz radio signals
  if (mySwitch.available()) {
    checkReceivedCommand();
    mySwitch.resetAvailable();

  }
  SerialUSB.println("looptest");

  delay(500);
}


void checkReceivedCommand() {
  if (mySwitch.getReceivedValue() == 5393 && photoFrontWhiteCal == 0) {
    SerialUSB.println("Running FRONT Light-follow module WHITE Light Calibration");
    calibrateFrontWhiteLFM();
    photoFrontWhiteCal = 1;
    runBeep();
    printValues(photoFrontWhiteValues);
  } else if (mySwitch.getReceivedValue() == 5398 && photoFrontBlackCal == 0) {
    SerialUSB.println("Running FRONT Light-follow module BLACK Light Calibration");
    calibrateFrontBlackLFM();
    photoFrontBlackCal = 1;
    runBeep();
    printValues(photoFrontBlackValues);
  }
  else {
    SerialUSB.println("Error! 433 MHz Command Unknown or previously already pressed!");
  }
}

void runBeep() {
  digitalWrite(buzzerPin, HIGH);
  delay(75);
  digitalWrite(buzzerPin, LOW);
}

//Print all Front photoarray white lightvalues
void printValues(int lFMValues[]) {
  SerialUSB.println("Photoresistor Values:");
  for (int i = 0; i < photoAmount; i++) {
    SerialUSB.print(lFMValues[i]);
    SerialUSB.print(" ");
  }
  SerialUSB.println("");
}

// Store Front photoarray white light values
void calibrateFrontWhiteLFM() {
  for (int i = 0; i < photoAmount; i++) {
    photoFrontWhiteValues[i] = getLightValue(lightFollowModuleFrontPins[i]);
  }
}

// Store Front photoarray black light values
void calibrateFrontBlackLFM() {
  for (int i = 0; i < photoAmount; i++) {
    photoFrontBlackValues[i] = getLightValue(lightFollowModuleFrontPins[i]);
  }
}

void calibrateBackWhiteLFM() {
  for (int i = 0; i < photoAmount; i++) {
    photoBackWhiteValues[i] = getLightValue(lightFollowModuleFrontPins[i]);
  }
}

void calibrateBackBlackLFM() {
  for (int i = 0; i < photoAmount; i++) {
    photoBackBlackValues[i] = getLightValue(lightFollowModuleFrontPins[i]);
  }
}

//Get light value from a photoresistor
int getLightValue(int photoPin) {
  int photoresValue;

  photoresValue = analogRead(photoPin);

  return photoresValue;
}
