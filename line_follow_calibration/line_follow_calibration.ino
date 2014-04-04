
int photoFrontPins[] = {0, 1, 2, 3};
int photoBackPins[] = {4, 5, 6, 7};
int const photoAmount = sizeof(photoFrontPins);
int photoFrontWhiteValues[photoAmount];

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Store Front photoarray white light values locally
  for (int i = 0; i < photoAmount / 2; i++) {
    photoFrontWhiteValues[i] = getLightValue(photoFrontPins[i]);
  }

  //Print all Front photoarray white lightvalues
  for (int i = 0; i < photoAmount  / 2; i++) {
    Serial.print(photoFrontWhiteValues[i]);
  }

  delay(500);
}

//void calibratefrontPhotoArray() {
//
//}
//
//
//void calibratebakrehotoArray() {
//
//}



//Get B/W value
int getLightValue(int photoPin) {
  int photoWhiteValue;

  photoWhiteValue = analogRead(photoPin);

  return photoWhiteValue;
}
