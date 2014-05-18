#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo. A maximum of eight servo objects can be created 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
    myservo.write(50);
    delay(500);
    myservo.write(140);
    delay(500);
  } 


