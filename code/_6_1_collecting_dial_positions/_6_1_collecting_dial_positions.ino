 /*
 * Collecting dial positions - Using an array and our button to collect
 * potentiometer values.
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
int buttonPin = 2;
int lastButtonState = HIGH;

// Storing the dial positions in an array. The array can store 3 values.
int combinationAttempt[3];
int count = 0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Attaches the servo to correct pin.
  myServo.attach(servoPin);
  
  // Prepare the button
  pinMode(buttonPin, INPUT_PULLUP);
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

  // Store the current button state. 
  int buttonState = digitalRead(buttonPin);
  
  // When the button is pressed the pin is connected to 
  // ground, which means it will be LOW.
  if( buttonState == LOW && lastButtonState == HIGH ){
    lastButtonState = LOW;
    combinationAttempt[count] = dialPosition;
    count++;
    debug();
  }
  
  // This will run we the button is released.
  if( lastButtonState == LOW && buttonState == HIGH ){
    lastButtonState = HIGH;
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

