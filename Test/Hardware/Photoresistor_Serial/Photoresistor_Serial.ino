// A simple program to print out the value of a photoresistor

// Photoresistor pin
int photoResistorPin = 0;

void setup()
{
  Serial.begin(9600); // Start Serial
}

void loop()
{
  // Print out the analog value of the photoresistor
  Serial.println(analogRead(photoResistorPin));
  delay(20);
}
