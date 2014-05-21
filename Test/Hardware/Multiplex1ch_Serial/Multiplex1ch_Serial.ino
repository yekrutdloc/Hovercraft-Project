
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

  digitalWrite(s0pin, LOW);
  digitalWrite(s1pin, LOW);
  digitalWrite(s2pin, LOW);
  digitalWrite(s3pin, LOW);

}

void loop() {
  Serial.println(analogRead(z));
  delay(200);
}
