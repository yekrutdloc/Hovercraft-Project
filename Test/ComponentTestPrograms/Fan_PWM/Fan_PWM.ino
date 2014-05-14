#include "/Users/Prince/Workspaces/P2/libraries/pwm01.h"

void setup()
{
  uint32_t  pwm_duty = 32767;
  uint32_t  pwm_freq1 = 2;
  uint32_t  pwm_freq2 = 25000;

  // Set PWM Resolution
  pwm_set_resolution(16);

  // Setup PWM Once (Up to two unique frequencies allowed
  //-----------------------------------------------------
  pwm_setup( 6, pwm_freq2, 1);  // Pin 6 freq set to "pwm_freq1" on clock A

  // Write PWM Duty Cycle Anytime After PWM Setup
  //-----------------------------------------------------
  pwm_write_duty( 6, 65000 );  
  delay(2000);  // 30sec Delay; PWM signal will still stream
  pwm_write_duty( 6, 15000 );  // 50% duty cycle on Pin 6
  delay(2000);  // 30sec Delay; PWM signal will still stream
  // Force PWM Stop On All Pins
  //-----------------------------
  pwm_stop( 6 );
}
