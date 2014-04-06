// 433 MHz library
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

// Photoresistor array variables
int photoFrontPins[] = {0, 1, 2, 3};
int photoBackPins[] = {4, 5, 6, 7};
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

  // Setup 433 MHz Radio reciever
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2

}

// Loop function
void loop() {
  if (mySwitch.available()) {
    if (mySwitch.getReceivedValue() == 5393 && photoFrontWhiteCal == 0) {
      SerialUSB.println("Running Front PhotoArray White Light Calibration");
      calibrateFrontWhitePhotoArray();
      printValues();
      photoFrontWhiteCal = 1;
    }
  }
  mySwitch.resetAvailable();

  delay(500);
}

//Print all Front photoarray white lightvalues
void printValues() {
  for (int i = 0; i < photoAmount; i++) {
    SerialUSB.print(photoFrontWhiteValues[i]);
    SerialUSB.print("-");
  }
  SerialUSB.println("");
}

// Store Front photoarray white light values
void calibrateFrontWhitePhotoArray() {
  for (int i = 0; i < photoAmount; i++) {
    photoFrontWhiteValues[i] = getLightValue(photoFrontPins[i]);
  }
}

// Store Front photoarray black light values
void calibrateFrontBlackPhotoArray() {
  for (int i = 0; i < photoAmount; i++) {
    photoFrontBlackValues[i] = getLightValue(photoFrontPins[i]);
  }
}

void calibrateBackWhitePhotoArray() {
  for (int i = 0; i < photoAmount; i++) {
    photoBackWhiteValues[i] = getLightValue(photoFrontPins[i]);
  }
}

void calibrateBackBlackPhotoArray() {
  for (int i = 0; i < photoAmount; i++) {
    photoBackBlackValues[i] = getLightValue(photoFrontPins[i]);
  }
}

//Get B/W value
int getLightValue(int photoPin) {
  int photoBWValue;

  photoBWValue = analogRead(photoPin);

  return photoBWValue;
}
