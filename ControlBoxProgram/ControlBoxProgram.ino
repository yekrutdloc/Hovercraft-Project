/*
  Example for different sending methods

  http://code.google.com/p/rc-switch/

  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

const int FrontWhiteCalibrationButtonPin = 2;
const int FrontBlackCalibrationButtonPin = 3;

const int ledPin =  13; // LED for diagnostics

void setup() {

  Serial.begin(9600);

  // LED settings
  pinMode(ledPin, OUTPUT);


  // Button settings
  pinMode(FrontWhiteCalibrationButtonPin, INPUT);
  pinMode(FrontBlackCalibrationButtonPin, INPUT);

  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(4);

}

void loop() {

  //  /* See Example: TypeA_WithDIPSwitches */
  //  mySwitch.switchOn("11111", "00010");
  //  delay(1000);
  //  mySwitch.switchOn("11111", "00010");
  //  delay(1000);

  /* Same switch as above, but using decimal code */
  if (digitalRead(FrontWhiteCalibrationButtonPin) == HIGH) {
    mySwitch.send(5393, 24); // Front LF-module White Light Calibration
    digitalWrite(ledPin, HIGH);
  } else if (digitalRead(FrontBlackCalibrationButtonPin) == HIGH) {
    mySwitch.send(5398, 24); // Front LF-module White Light Calibration
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  //  delay(1000);
  //  mySwitch.send(5396, 24);
  //  delay(1000);

  //  /* Same switch as above, but using binary code */
  //  mySwitch.send("000000000001010100010001");
  //  delay(1000);
  //  mySwitch.send("000000000001010100010100");
  //  delay(1000);

  //  /* Same switch as above, but tri-state code */
  //  mySwitch.sendTriState("00000FFF0F0F");
  //  delay(1000);
  //  mySwitch.sendTriState("00000FFF0FF0");
  //  delay(1000);

  delay(10);
}
