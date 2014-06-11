// Multiplex1ch_PhotoresistorChoosePrint.ino
//
// Purpose: This Sketch is used to test specific multiplex-channels
// With the use of Serial - a multiplex channel can be chosen. by typing a number between 0-15
// When a channel has been chosen, the analog values from that specific channel are printed out.
//
// @author Prince Balabis


// Front Line-Sensor pins
int const s0pin = 53;
int const s1pin = 52;
int const s2pin = 51;
int const s3pin = 50;
int const z = A1;

void setup() {
  Serial.begin(9600);

  // Photo resistor array setup
  pinMode(s0pin, OUTPUT);    // s0
  pinMode(s1pin, OUTPUT);    // s1
  pinMode(s2pin, OUTPUT);    // s2
  pinMode(s3pin, OUTPUT);    // s3

  // Read the serial message and convert it to an integer
  char buffer[] = {' ', ' ', ' ', ' ', ' ', ' ', ' '}; // Receive up to 7 bytes
    while (!Serial.available()); // Wait for characters
  Serial.readBytesUntil('\n', buffer, 7);
  int incomingValue = atoi(buffer);

  lightLEDChannel(incomingValue);
}

void loop() {
  Serial.println(analogRead(z));
  delay(200);
}


//This function takes in a channel number, and uses a case switch to alert the multiplex
// which channel is wanted. The truth table is converted from the datasheet of the multiplex.
void lightLEDChannel(int photoChannel) {
  switch (photoChannel) {
    case 0:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, LOW);
      break;
    case 1:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, LOW);
      break;
    case 2:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, LOW);
      break;
    case 3:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, LOW);
      break;
    case 4:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, LOW);
      break;
    case 5:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, LOW);
      break;
    case 6:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, LOW);
      break;
    case 7:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, LOW);
      break;
    case 8:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, HIGH);
      break;
    case 9 :
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, HIGH);

      break;
    case 10:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, HIGH);
      break;
    case 11:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, LOW);
      digitalWrite(s3pin, HIGH);
      break;
    case 12:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, HIGH);
      break;
    case 13:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, LOW);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, HIGH);
      break;
    case 14:
      digitalWrite(s0pin, LOW);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, HIGH);
      break;
    case 15:
      digitalWrite(s0pin, HIGH);
      digitalWrite(s1pin, HIGH);
      digitalWrite(s2pin, HIGH);
      digitalWrite(s3pin, HIGH);
      break;
  }
}

