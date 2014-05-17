// Front Line-Sensor pins
int const s0pin = 44;
int const s1pin = 45;
int const s2pin = 46;
int const s3pin = 47;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

  // Photo resistor array setup
  pinMode(s0pin, OUTPUT);    // s0
  pinMode(s1pin, OUTPUT);    // s1
  pinMode(s2pin, OUTPUT);    // s2
  pinMode(s3pin, OUTPUT);    // s3
}

void loop() {

  char buffer[] = {' ', ' ', ' ', ' ', ' ', ' ', ' '}; // Receive up to 7 bytes
  while (!Serial.available()); // Wait for characters
  Serial.readBytesUntil('\n', buffer, 7);
  int incomingValue = atoi(buffer);

  lightLEDChannel(incomingValue);

  // say what you got:
  Serial.print("Channel activated: ");
  Serial.println(incomingValue, DEC);
}


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

