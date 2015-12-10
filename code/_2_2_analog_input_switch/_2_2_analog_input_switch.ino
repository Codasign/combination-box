/*
 * Analog input & digital ouptput - Reading the analog input sensor 
 * (potentiometer) and turning an LED on.
 * @author Your Name Here
 */

// These are variables. We will use over and over again in 
// or setup() and loop() functions.
int potPin = A0;
int ledPin = 5;


void setup() {
  // Start the serial communication between the Arduino and computer.
  Serial.begin(9600);

  // Prepare the LED pin to be used as an 'OUTPUT'.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Store the potentiometer input value.
  int potValue = analogRead(potPin);

  // Output into serial monitor for debugging.
  Serial.println(potValue);
  
  if(potValue > 500 && potValue < 600){
    // Tell the LED pin to turn on
    digitalWrite(ledPin, HIGH);
  } else {
    // Tell the LED pin to turn off
    digitalWrite(ledPin, LOW);
  }
  
}
