#include <Servo.h>

Servo myServo;
int servoPin = 6;
int ledPin = 5;
int potPin = A0;
int buttonPin = 2;

// The combination that will unlock our precious things.
int CODE[] = { 5, 4, 5 };
// The attempted combination.
int combinationAttempt[3];
int count = 0;

// The current position of the dial.
int dialPosition = 0;
boolean isOpen = false;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  // Attaches the servo to correct pin.
  myServo.attach(servoPin);
  // Prepare the 
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  // Store the main analog input value.
  int potValue = analogRead(potPin);
  
  // Flash the light everytime the value is divisible by 100.
  if( dialPosition != round(potValue / 100) ){
    digitalWrite(ledPin, HIGH);
  }
  
  // Store the current button state. 
  int buttonState = digitalRead(buttonPin);

  // Dividing the potValue by 100 to give 10 positions.
  dialPosition = round(potValue / 100);
  
  // When the button is pressed the pin is connected to 
  // ground, which means it will be LOW.
  if( buttonState == LOW && lastButtonState == HIGH ){
    // Store the current dialPosition and move on one position.   
    combinationAttempt[count] = dialPosition;
    count++;
    // We use the lastButtonState to ensure that this code only
    // runs once for every button push.
    lastButtonState = LOW;
    debug();
  }
  
  // This will run we the button is released.
  if( lastButtonState == LOW && buttonState == HIGH ){
    lastButtonState = HIGH;
  }

  // If we have reached 3 values and the combination is correct.
  if( count == 3 ){
    if( isCombinationCorrect() == true ){
      open();
    } else {
      reset();
    }
  }

  // Wait and then turn off light, if it is on.
  delay(200);
  digitalWrite(ledPin, LOW);
}

boolean isCombinationCorrect(){
  // Loop through our combinationAttempt and check
  // if any of the values do not match.
  for(int i = 0; i < 3; i++){
    if( CODE[i] != combinationAttempt[i] ){
      return false;
    }
  }
  return true;
}

void open() {   
  
  if(isOpen == true){
    return;
  }
  
  // Goes from 0 to 180 in steps of 1 
  for(int pos = 0;  pos <= 180; pos += 1) {                  
    
    // Tell servo to go to position in variable 'pos'
    // This function is expecting degrees.
    myServo.write(pos);             
  
    // Waits 15ms for the servo to reach the position.
    delay(15);                 
  }
  
  isOpen = true;
}
