#define PHOTO_AMOUNT 4 //Change value to amount of photoresistors

int photoPins[PHOTO_AMOUNT];
int photoWhiteValues[PHOTO_AMOUNT];
int photoBlackValues[PHOTO_AMOUNT];

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < PHOTO_AMOUNT; i++) {
    photoPins[i] = i;
  }
  calibrateWhiteValues();
  //  calibrateBlackValues();
  delay(500);
}

void calibratefrontPhotoArray() {

}


void calibratebakrehotoArray() {

}

void calibrateWhiteValues() {
  //Get white value
  for (int i = 0; i < PHOTO_AMOUNT; i++) {
    photoWhiteValues[i] = analogRead(photoPins[i]);
  }
  Serial.println("");

  for (int i = 0; i < PHOTO_AMOUNT; i++) {
    Serial.print(photoWhiteValues[i]);
    Serial.print("-");
  }
}

void calibrateBlackValues() {
  //Get black value
  for (int i = 0; i < PHOTO_AMOUNT; i++) {
    photoBlackValues[i] = analogRead(photoPins[i]);
  }
  Serial.println("");

  for (int i = 0; i < PHOTO_AMOUNT; i++) {
    Serial.print(photoBlackValues[i]);
    Serial.print("-");
  }
}

