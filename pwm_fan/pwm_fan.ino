void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  analogWrite(3, 5);
  delay(4000);
  analogWrite(3, 244);
  delay(4000);
}
