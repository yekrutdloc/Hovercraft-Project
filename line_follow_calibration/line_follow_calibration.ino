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
  SerialUSB.begin(115200);

  //Buzzer Setup
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Setup 433 MHz Radio reciever
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2

}

// Loop function
void loop() {
  // Check 433 MHz radio signals
  if (mySwitch.available()) {
    if (mySwitch.getReceivedValue() == 5393 && photoFrontWhiteCal == 0) {
      SerialUSB.println("Running Front Light-follow module White Light Calibration");
      calibrateFrontWhiteLFM();
      printValues(photoFrontWhiteValues);
      photoFrontWhiteCal = 1;
      digitalWrite(buzzerPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);               // wait for a second
      digitalWrite(buzzerPin, LOW);    // turn the LED off by making the voltage LOW
    }
  }
  mySwitch.resetAvailable();

  delay(500);
}

//Print all Front photoarray white lightvalues
void printValues(int lFMValues[]) {
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

//Get B/W value
int getLightValue(int photoPin) {
  int photoBWValue;

  photoBWValue = analogRead(photoPin);

  return photoBWValue;
}
