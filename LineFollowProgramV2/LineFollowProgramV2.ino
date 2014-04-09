// Photo resistor
int const s0pin = 51;
int const s1pin = 52;
int const s2pin = 53;
int const z = A0;
int lsb = 0;
int mid = 0;
int msb = 0;
int state = 0;
int photoValArray[8];
int photoValApproxArray[7];
int photoValFinalArray[15];

// Line-Follow system
int photoFrontBlackValues[15];
int lineFollowValArray[8];

// Buzzer
int buzzerPin = 30; // Buzzer

void setup() {
  // Log-output setup
  Serial.begin(9600);

  // Photo resistor array setup
  pinMode(s0pin, OUTPUT);    // s0
  pinMode(s1pin, OUTPUT);    // s1
  pinMode(s2pin, OUTPUT);    // s2

  //Buzzer Setup
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Line-Follow Sensor Calibration program
  delay(2000);
  getPhotoArrayValues();
  calculateApproxValues();
  for (int j = 0; j < 15; j++) {
    photoFrontBlackValues[j] = photoValFinalArray[j];
  }
  runBuzzerBeep();
  Serial.println('Black calibration values: ');
  for (int i = 0; i < 15; i++) {
    Serial.print(photoFrontBlackValues[i]);
    Serial.print('-');
  }
  Serial.println(' ');
} // end of void setup()();

void loop() {
  // Get values
  getPhotoArrayValues();

  // Create approx values
  calculateApproxValues();

  //  // Convert analog values to 1 or 0
  for (int i = 0; i < 15; i++) {
    if (photoValFinalArray[i] > (photoFrontBlackValues[i] + 200)) {
      lineFollowValArray[i] = 0;
      Serial.print(0);
    } else {
      lineFollowValArray[i] = 1;
      Serial.print(1);
    }
    Serial.print("-");
  }
  Serial.println(" "); //newline
} // end of loop();

void calculateApproxValues() {
  for (int i = 0; i < 8; i++) {
    photoValApproxArray[i] = ((photoValArray[i] + photoValArray[i + 1]) / 2);
  }

  for (int i = 0; i < 15; i += 2) {
    photoValFinalArray[i] = photoValArray[i / 2];
  }

  for (int i = 1; i < 15; i += 2) {
    photoValFinalArray[i] = photoValApproxArray[i / 2];
  }
}

void getPhotoArrayValues() {
  for (state = 0; state < 8; state++) {
    switch (state) {
      case 0:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        photoValArray[state] = getPhotoValue();
        break;
      case 1:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        photoValArray[state] = getPhotoValue();
        break;
      case 2:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        photoValArray[state] = getPhotoValue();
        break;
      case 3:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        photoValArray[state] = getPhotoValue();
        break;
      case 4:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        photoValArray[state] = getPhotoValue();
        break;
      case 5:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        photoValArray[state] = getPhotoValue();
        break;
      case 6:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        photoValArray[state] = getPhotoValue();
        break;
      case 7:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        photoValArray[state] = getPhotoValue();
        break;
    }
  }
}

int getPhotoValue() {
  return analogRead(z);
}

void runBuzzerBeep() {
  digitalWrite(buzzerPin, HIGH);
  delay(75);
  digitalWrite(buzzerPin, LOW);
}
