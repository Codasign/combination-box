 /*
 * Dial positions - Creating dial positions from the potentiometer input.
 * Flashing an LED when we go past each one.
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
int dialPosition = 0;
int lastButtonState = HIGH;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Attaches the servo to correct pin.
  myServo.attach(servoPin);

}

void loop() {

  // Store the main analog input values.
  int potValue = analogRead(potPin);

  // Flash the light everytime the value is divisible by 100.
  // Wait for 200ms and turn off.
  if( dialPosition != round(potValue / 100) ){
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
  // Dividing the potValue by 100 to give 10 positions.
  dialPosition = round(potValue / 100);
  
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

