// ADCSamplingRate1Input_Test.ino
//
// This program is taken from: http://forum.arduino.cc/index.php?topic=137635.0
// It's made to benchmarks the ADC by reading ONE analog input in order to get its sampling rate.
// To calculate the sampling rate, get the microseconds
// from the Serial-output, and use
// this formula: 10^6/((10^-6)*(SAMPLING RATE))
//
// @author Prince Balabis

void setup() {
  SerialUSB.begin(1152000); // Enable Serial-output
  int t = analogRead(0);

  ADC->ADC_MR |= 0x80; // these lines set free running mode on adc 7 (pin A0)
  ADC->ADC_CR = 2;
  ADC->ADC_CHER = 0x80;
}

void loop() {
  int t = micros(); // start time
  int q = 0;
  int a0;
  for (int i = 0; i < 1000000; i++) { // Run ADC 1 million times
    while ((ADC->ADC_ISR & 0x80) == 0); // wait for conversion
    a0 = ADC->ADC_CDR[7];            // read data
    q += a0;
  }
  t = micros() - t; // stop time
  SerialUSB.print("1 million conversions in ");
  SerialUSB.print(t);
  SerialUSB.println(" micros");
}

