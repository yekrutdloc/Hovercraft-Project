#include "/Applications/Arduino.app/Contents/Resources/Java/hardware/arduino/sam/libraries/pwm01.h"

uint32_t  pwm_freq = 25000;

void setup()
{
  Serial.begin(9600);

  // Set PWM Resolution
  pwm_set_resolution(16);

  // Setup PWM Once (Up to two unique frequencies allowed
  //-----------------------------------------------------
  pwm_setup( 6, pwm_freq, 1);  // Pin 6 freq set to "pwm_freq1" on clock A
  pwm_setup( 7, pwm_freq, 2);  // Pin 7 freq set to "pwm_freq2" on clock B
  pwm_setup( 8, pwm_freq, 2);  // Pin 8 freq set to "pwm_freq2" on clock B
  pwm_setup( 9, pwm_freq, 2);  // Pin 9 freq set to "pwm_freq2" on clock B
}

void loop()
{
  // Write PWM Duty Cycle Anytime After PWM Setup
  //-----------------------------------------------------
  pwm_write_duty( 6, 19661 );  // 50% duty cycle on Pin 6
  pwm_write_duty( 7, 19661 );  // 50% duty cycle on Pin 7
  pwm_write_duty( 8, 655360 );  // 50% duty cycle on Pin 8
  pwm_write_duty( 9, 5000 );  // 50% duty cycle on Pin 9

  Serial.print(30);
  Serial.print("-");
  delay(5000);

//  // Write PWM Duty Cycle Anytime After PWM Setup
//  //-----------------------------------------------------
//  pwm_write_duty( 6, percentDutyCycle(75) );
//  pwm_write_duty( 7, percentDutyCycle(75) );
//  pwm_write_duty( 8, percentDutyCycle(75) );
//  pwm_write_duty( 9, percentDutyCycle(75) );

//  Serial.print(75);
//  Serial.print("-");
//  delay(5000);
}

//int percentDutyCycle(int percent) {
//  return (((percent - 100) / 100) * (2 ^ 16))*-1;
//}
