// Front Line-Sensor pins
int const s0pin = 51;
int const s1pin = 52;
int const s2pin = 53;
int const s3pin = 54;
int const z = A0;

// Line Sensors
int photoValArray[16];
int photoValApproxArray[15];
int photoValFinalArray[31];

// Line-Sensor System
int photoFrontBlackValues[31];
int lineFol0ValArray[16];

// Buzzer
int buzzerPin = 30; // Buzzer set to "Digital pin 30"

void setup() {
  // Log-output setup
  Serial.begin(9600);

  // Photo resistor array setup
  pinMode(s0pin, OUTPUT);    // s0
  pinMode(s1pin, OUTPUT);    // s1
  pinMode(s2pin, OUTPUT);    // s2
  pinMode(s3pin, OUTPUT);    // s3

  //Buzzer Setup
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, 0);

  // Line-Fol0 Sensor Calibration program
  delay(2000);
  getPhotoArrayValues();
  calculateApproxValues();
  for (int j = 0; j < 31; j++) {
    photoFrontBlackValues[j] = photoValFinalArray[j];
  }
  runBuzzerBeep();
  Serial.println('Black calibration values: ');
  for (int i = 0; i < 31; i++) {
    Serial.print(photoFrontBlackValues[i]);
    Serial.print('-');
  }
  Serial.println(' ');
} // end of void setup();

void loop() {
  // Get values
  getPhotoArrayValues();

  // Create approx values
  calculateApproxValues();

  //  // Convert analog values to 1 or 0
  for (int i = 0; i < 31; i++) {
    if (photoValFinalArray[i] > (photoFrontBlackValues[i] + 200)) {
      lineFol0ValArray[i] = 0;
      Serial.print(0);
    } else {
      lineFol0ValArray[i] = 1;
      Serial.print(1);
    }
    Serial.print("-");
  }
  Serial.println(" "); //newline
} // end of loop();

void calculateApproxValues() {
  for (int i = 0; i < 16; i++) {
    photoValApproxArray[i] = ((photoValArray[i] + photoValArray[i + 1]) / 2);
  }

  for (int i = 0; i < 31; i += 2) {
    photoValFinalArray[i] = photoValArray[i / 2];
  }

  for (int i = 1; i < 31; i += 2) {
    photoValFinalArray[i] = photoValApproxArray[i / 2];
  }
}

void getPhotoArrayValues() {
 for (int photoChannel = 0; photoChannel < 16; photoChannel++) {
   switch (photoChannel) {
     case 0:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 1:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 2:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 3:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 4:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 5:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 6:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 7:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, LOW);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 8:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 9 :
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 10:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
     case 11:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, LOW);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
       case 12:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
      case 13:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, LOW);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
      case 14:
       digitalWrite(s0pin, LOW);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
      case 15:
       digitalWrite(s0pin, HIGH);
       digitalWrite(s1pin, HIGH);
       digitalWrite(s2pin, HIGH);
       digitalWrite(s3pin, HIGH);
       photoValArray[photoChannel] = analogRead(z);
       break;
   }
 }
}

void runBuzzerBeep() {
  digitalWrite(buzzerPin, 1);
  delay(75);
  digitalWrite(buzzerPin, 0);
}
