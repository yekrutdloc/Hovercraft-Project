// Front Line-Sensor pins
int const s0pin = 51;
int const s1pin = 52;
int const s2pin = 53;
int const s3pin = 54;
int const mux_1 = A0;

// Front Line Sensor variables
int const frontSensitivity = 200;
int fr_AdcValues[16];
int fr_InterpolValues[15];
int fr_MergedValues[31];
int fr_BlackValues[31];
int fr_OneZeroValues[16];

static WORKING_AREA(fr_LineSensorSystem, 64);

static msg_t Thread1(void *arg) {

  // Photo resistor array setup
  pinMode(s0pin, OUTPUT);    // s0
  pinMode(s1pin, OUTPUT);    // s1
  pinMode(s2pin, OUTPUT);    // s2
  pinMode(s3pin, OUTPUT);    // s3

  // Line-Follow Sensor Calibration program
  delay(2000); // Wait 2 seconds before running calibration program
  getPhotoArrayValues(); // Get each photoresistor value
  calculateApproxValues(); // Interpolate photoresistor values
  for (int j = 0; j < 31; j++) { // Merge the interpolated values with the photoresistor values & store in calibration array
    fr_BlackValues[j] = fr_MergedValues[j];
  }
  Serial.println('Black calibration values: ');
  for (int i = 0; i < 31; i++) { // Print calibration values
    Serial.print(fr_BlackValues[i]);
    Serial.print('-');
  }
  Serial.println(' ');

  while (1) {
    // Get values
    getPhotoArrayValues();

    // Create approx values
    calculateApproxValues();

    // Convert analog values to 1 or 0
    for (int i = 0; i < 31; i++) {
      if (fr_MergedValues[i] > (fr_BlackValues[i] + frontSensitivity)) {
        fr_OneZeroValues[i] = 0;
        Serial.print(0);
      } else {
        fr_OneZeroValues[i] = 1;
        Serial.print(1);
      }
      Serial.print("-");
    }
    Serial.println(" "); //newline
  }// end of loop
  return 0;
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
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 1:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 2:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 3:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 4:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 5:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 6:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 7:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 8:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 9 :
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 10:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 11:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 12:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 13:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 14:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
      case 15:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        fr_AdcValues[photoChannel] = analogRead(mux_1);
        break;
    }
  }
}

// Function to interpolate the photoresistor values
void calculateApproxValues() {
  for (int i = 0; i < 16; i++) {
    fr_InterpolValues[i] = ((fr_AdcValues[i] + fr_AdcValues[i + 1]) / 2);
  }

  for (int i = 0; i < 31; i += 2) {
    fr_MergedValues[i] = fr_AdcValues[i / 2];
  }

  for (int i = 1; i < 31; i += 2) {
    fr_MergedValues[i] = fr_InterpolValues[i / 2];
  }
}



