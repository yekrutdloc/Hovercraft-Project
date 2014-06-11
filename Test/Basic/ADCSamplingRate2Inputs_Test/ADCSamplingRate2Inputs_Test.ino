// ADCSamplingRate2Inputs_Test 
//
// Purpose: This program is taken from: http://forum.arduino.cc/index.php?topic=137635.0
// It's made to benchmarks the ADC by reading TWO analog inputs
// in order to get its sampling rate.
// To calculate the sampling rate, get the microseconds
// from the Serial-output, and use
// this formula: 10^6/((10^-6)*(SAMPLING RATE))
//
// @author Prince Balabis


void setup() {
  Serial.begin(9600); // Enable Serial-output
  int t = analogRead(0);

  ADC->ADC_MR |= 0x80; // these lines set free running mode on adc 7 and adc 6 (pin A0 and A1 - see Due Pinout Diagram thread)
  ADC->ADC_CR = 2;
  ADC->ADC_CHER = 0xC0; // this is (1<<7) | (1<<6) for adc 7 and adc 6
}

void loop() {
  int t = micros(); // start time
  int q0 = 0, q1 = 0;
  int a0, a1;
  for (int i = 0; i < 500000; i++) {// Run ADC 500000 times
    while ((ADC->ADC_ISR & 0xC0) != 0xC0); // wait for two conversions (pin A0[7]  and A1[6])
    a0 = ADC->ADC_CDR[7];            // read data on A0 pin
    a1 = ADC->ADC_CDR[6];            // read data on A1 pin
    q0 += a0;
    q1 += a1;
  }
  t = micros() - t; // stop time
  Serial.print("500000 pairs of conversions in "); Serial.print(t); Serial.println(" micros");
  Serial.print("A0 total:"); Serial.println(q0);
  Serial.print("A1 total:"); Serial.println(q1);
}

