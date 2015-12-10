#include <Servo.h>

Servo myServo;
int servoPin = 6;
int potPin = A0;

// The combination that will unlock our precious things.
const int CODE[] = { 5, 4, 5 };
// The attempted combination.
int combinationAttempt[3];
int count = 0;

// The current position of the dial.
int dialPosition = 0;
// The direction the dial has just moved.
int dialDirection = 1; // 1 = clockwise, -1 = anticlockwise, 0 = hasn't changed. 

boolean isOpen = false;

void setup() {
  Serial.begin(9600);
  // Attaches the servo to correct pin.
  myServo.attach(servoPin);
}

void loop() {
 
  // Store the main analog input values.
  int potValue = analogRead(potPin);

  // RESET - If the count is greater than 0 an attempt to unlock
  // has been made. Bringing the potentiometer back to position 0 
  // will reset our attempt and we can try again.
  if( count > 0 && potValue <= 10 ){
    reset();
  }

  // DIRECTION - Which direction is the potentiometer moving in.....?
  int nextDialPosition = round(potValue / 100);
  if( nextDialPosition > dialPosition ){
    // Clockwise
    dialDirection = 1;
    digitalWrite(4, HIGH);
  } else if( nextDialPosition < dialPosition ){
    // Anticlockwise
    dialDirection = -1;
    digitalWrite(4, HIGH);
  } else {
    // No change
    dialDirection = 0; 
  }

  dialPosition = nextDialPosition;

  // If this is part '0' of combination and direction is 'anticlockwise'
  if(count == 0 && dialDirection == -1){
    combinationAttempt[0] = dialPosition+1; 
    count = 1;
  }

  // If this is part '1' and direction is 'clockwise'
  if(count == 1 && dialDirection == 1){
    combinationAttempt[1] = dialPosition-1; 
    count = 2;
  }

  // If this is part '2' and direction is 'anticlockwise'
  if(count == 2){
    combinationAttempt[2] = dialPosition;
    if(isCombinationCorrect() == true){
      open();
    }
  }
  
  debug();
  delay(200);
  digitalWrite(4, LOW);
}

boolean isCombinationCorrect(){
  for(int i = 0; i < 3; i++){
    if(CODE[i] != combinationAttempt[i]){
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

void reset() {
  // Set all of the variables back to how they started.
  Serial.println("***** RESET *****");
  isOpen = false;
  count = 0;
  dialPosition = 0;
  dialDirection = 1;
  for (int i=0; i<3; i++) {
    combinationAttempt[i] = 0;
  }
}

