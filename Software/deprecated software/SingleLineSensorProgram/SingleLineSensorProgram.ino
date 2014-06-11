//SingleLineSensorProgram.ino 
//
// This Arduino Sketch is to run a single Line Sensor System.
// Before starting the program, hover the line sensor above the line.
// When starting the program, a calibration is executed which reads the photoresistor values,
// and stores the values in an array(photoFrontBlackValues).
// When calibration is finished, the loop begins where realtime photoresistor 
// values are compared to the calibration values.
// If the realtime value of a photoresistor are far from the calibration value - the white track is assumed
// If the realtime value of a photoresistor is close to the calibration value - the black line is assumed
// Change pin-variables below if needed
// Change calibration sensitivity below if needed
//
// @author Prince Balabis


// Front Line-Sensor pins
int const s0pin = 51;
int const s1pin = 52;
int const s2pin = 53;
int const s3pin = 54;
int const z = A0;

// Buzzer pin
int const buzzerPin = 30;

// Line Sensors variables
int const calibrationSensitivity = 200;
int photoValArray[16];
int photoValApproxArray[15];
int photoValMergedArray[31];
int photoFrontBlackValues[31];
int lineFollowValArray[16];

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

  // Line-Follow Sensor Calibration program
  delay(2000); // Wait 2 seconds before running calibration program
  getPhotoArrayValues(); // Get each photoresistor value
  calculateApproxValues(); // Interpolate photoresistor values
  for (int j = 0; j < 31; j++) { // Merge the interpolated values with the photoresistor values & store in calibration array
    photoFrontBlackValues[j] = photoValMergedArray[j];
  }
  runBuzzerBeep(); // Run beep to feedback a finished calibration
  Serial.println('Black calibration values: ');
  for (int i = 0; i < 31; i++) { // Print calibration values
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

  // Convert analog values to 1 or 0
  for (int i = 0; i < 31; i++) {
    if (photoValMergedArray[i] > (photoFrontBlackValues[i] + calibrationSensitivity)) {
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

// Function to interpolate the photoresistor values
void calculateApproxValues() {
  for (int i = 0; i < 16; i++) {
    photoValApproxArray[i] = ((photoValArray[i] + photoValArray[i + 1]) / 2);
  }

  for (int i = 0; i < 31; i += 2) {
    photoValMergedArray[i] = photoValArray[i / 2];
  }

  for (int i = 1; i < 31; i += 2) {
    photoValMergedArray[i] = photoValApproxArray[i / 2];
  }
}

// Function to cycle through each multiplex-channel and store photoresistor value
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

// function to run beep with the buzzer
void runBuzzerBeep() {
  digitalWrite(buzzerPin, 1);
  delay(75);
  digitalWrite(buzzerPin, 0);
}
