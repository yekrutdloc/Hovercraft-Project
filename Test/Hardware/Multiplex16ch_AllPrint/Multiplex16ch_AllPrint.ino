// Multiplex16ch_AllPrint.ino
//
// This program is made to test a 16 channel multiplex.
// Connect LEDs to each channel & 5V to common Input/Output on the multiplex
// Choosing the channel is done by writing the channel-number to Serial.
// Enter a number between 0-15 to choose a channel accordingly.
//
// @author Prince Balabis

// Multiplex pins
int const s0pin = 53;
int const s1pin = 52;
int const s2pin = 51;
int const s3pin = 50;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

  // Multiplex setup
  pinMode(s0pin, OUTPUT);    // s0
  pinMode(s1pin, OUTPUT);    // s1
  pinMode(s2pin, OUTPUT);    // s2
  pinMode(s3pin, OUTPUT);    // s3
}

void loop() {
  // Read the serial message and convert it to an integer

  lightLEDChannel();
  Serial.println();
  delay(100);
  // Print out the chosen channel
}

//This function takes in a channel number, and uses a case switch to alert the multiplex
// which channel is wanted. The truth table is converted from the datasheet of the multiplex.
void lightLEDChannel() {
  for (int i = 0; i < 16; i++) {
    switch (i) {
      case 0:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");
        break;
      case 1:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 2:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 3:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 4:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 5:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 6:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 7:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, LOW);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 8:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 9 :
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");


        break;
      case 10:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 11:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, LOW);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 12:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 13:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, LOW);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 14:
        digitalWrite(s0pin, LOW);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
      case 15:
        digitalWrite(s0pin, HIGH);
        digitalWrite(s1pin, HIGH);
        digitalWrite(s2pin, HIGH);
        digitalWrite(s3pin, HIGH);
        Serial.print(analogRead(1));
        Serial.print("-");

        break;
    }
  }
}

