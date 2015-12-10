 /*
 * Analog input & sweep - Using the analog input sensor (e.g. potenitometer) 
 * to decide when we want start moving the servo.
 * @author Your Name Here
 */

#include <Servo.h>

// Create 'Servo' object to control a servo 
Servo myServo;

int potPin = A0;
int ledPin = 5;
int servoPin = 6;
boolean isOpen = false;
int minPotValue = 500;
int maxPotValue = 600;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Attaches the servo to correct pin.
  myServo.attach(servoPin);

  // open();
}

void loop() {

  // Store the main analog input values.
  int potValue = analogRead(potPin);

  // Output into serial monitor for debugging.
  Serial.println(potValue);

  // If the potValue is above min and below max...
  if(potValue > minPotValue && potValue < maxPotValue){
    open();
  }

}

void open() {  
  
  if(isOpen == true){
    return;
  }
  
  // Goes from 0 to 180 in steps of 1 
  for(int pos = 0; pos <= 180; pos += 1) {                  
    
    // Tell servo to go to position in variable 'pos'
    // This function is expecting degrees.
    myServo.write(pos);             
  
    // Waits 15ms for the servo to reach the position.
    delay(15);                 
  }
  
  isOpen = true;
}

