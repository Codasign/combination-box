![Codasign logo](https://raw.githubusercontent.com/Codasign/combination-box/master/handout/logo.png)
Combination Dial Lock Workshop
======================

### What is a Combination Dial Lock?
![Combination Lock](https://media2.giphy.com/media/ABfNx2KM7dB7O/200.gif)

A single dial combination lock is a type of locking mechanism found on padlocks, lockers, or safes. It uses a single dial which interacts with several aligned discs or cams. A lock of this type is opened by rotating the dial clockwise to the first number, then counterclockwise to the second, and so on alternating direction until the last numeral is reached. 

![Mechanics](http://media.web.britannica.com/eb-media/64/2164-004-7B9FD482.gif)

Below is a link to a great video of a home made wooden dial lock. Shows the inner workings of a dial locking mechanism. [https://www.youtube.com/watch?v=1-fFCrLwhPo](https://www.youtube.com/watch?v=1-fFCrLwhPo)

This is how a mechanical dial locks work. Today we will be simluate the inner workings of a combination lock with electronic components and Arduino.

### Before we start

* What are people's experience of Arduino?
* Open Arduino IDE
* Turn on line numbers
* Select board
* TODO...

### 1. Analog input - Receiving the value of a potentiometer

**Question:** Why is the potentiometer an analog input?

#### Build the circuit

![Potentiometer Fritzing](https://raw.githubusercontent.com/Codasign/combination-box/master/fritzing/potentiometer_bb.jpg)

#### Add the code
```
void setup() {
  // Start the serial communication between the Arduino and computer.
  Serial.begin(9600);
}

void loop() {
  // Store the main analog input values.
  int potValue = analogRead(A0);

  // Concatenate/join together strings for a neat outout.
  String output = "Sensor value: ";
  output += potValue;

  // Output into serial monitor for debugging.
  Serial.println(output);
}
```

#### Compile & upload your code

![Compile and Upload](https://raw.githubusercontent.com/Codasign/combination-box/master/handout/run-your-code.png)

Clicking on the tick icon/button will compile your code. Converting the code you've written into a format that Arduino understands. It will also tell you if you have any errors in your code. 

If everything is ok then click the 'right arrow' icon/button. This will upload your code to the Arduino.

#### Open Serial Monitor (*ctrl + shift + m*)
![Open the serial monitor](https://raw.githubusercontent.com/Codasign/combination-box/master/handout/open-serial-monitor.png)

Cicking on the magnifying glass will open up the Serial Monitor and allow you to see what position the potentiometer is currently at.


### 2. Analog input and Analog output - Controlling an LED

**Question:** What do the `setup()` and `loop()`  functions do?

#### Build the circuit

![Potentiometer + LED Fritzing](https://raw.githubusercontent.com/Codasign/combination-box/master/fritzing/potentiometer_led_bb.jpg)

#### Change your code

(1)  Add this line to your `setup()` function

```
pinMode(ledPin, OUTPUT);
```

(2)  Add this line to your `loop()` function
```
analogWrite(ledPin, potValue / 4);
```

#### Compile and upload 

Any errors? If so what do the error messages say?

#### Change your code

(3)  **Replace** this line of code:

```
analogWrite(ledPin, potValue / 4);
```

with this:

```
  if(potValue > 500 && potValue < 600){
    // Tell the LED pin to turn on
    digitalWrite(ledPin, HIGH);
  } else {
    // Tell the LED pin to turn off
    digitalWrite(ledPin, LOW);
  }
```

#### Compile and upload 

Any errors? No! Super.

### 3. Analog input and servo - Controlling a servo!

**Question:** What is a function?

#### Build the circuit

![Potentiometer + Servo Fritzing](https://raw.githubusercontent.com/Codasign/combination-box/master/fritzing/potentiometer_servo_bb.jpg)

#### Add some code

```
#include <Servo.h>

// Create 'Servo' object to control a servo 
Servo myServo;

int potPin = A0;
int ledPin = 5;
int servoPin = 6;
boolean isOpen = false;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Attaches the servo to correct pin.
  myServo.attach(servoPin);

  open();
}

void loop() {

  // Store the main analog input values.
  int potValue = analogRead(potPin);

  // Output into serial monitor for debugging.
  Serial.println(potValue);

  /*
  if(potValue > minPotValue && potValue < maxPotValue){
    open();
  }
  */
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
```

#### Discussion

Let's take a look at the code and see what has changed. What do we expect to happen when we upload our code?


#### Compile and upload 

Compile errors? Upload errors?

#### Change the code

(1) We don't want the servo to `open()` when the sketch starts. How do we stop that from happening?  

(2) We only want the servo to `open()` when the potentiometer is at a certain point. How do we make this happen? Look at line number 35.

#### Compile & upload 


### 4. Create our dial positions

**Question:** How many dial positions shall we have? And how does this change the strength of the lock? 

#### Add our code

```
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
```

#### Discussion

What's going on? How has the code changed and what are we expecting to happen?

#### Compile & upload

What is the result? We can change the output from an LED to a piezo?

### 5. Digital input - Read the value from our button

**Question:** Why is the button a digital input?
**Question:** How does a button work in a circuit?

### Build the circuit

![Potentiometer + Button + Servo Fritzing](https://raw.githubusercontent.com/Codasign/combination-box/master/fritzing/potentiometer_servo_bb.jpg)
### Change the code

(1) We want to prepare the buttonPin on Arduino to be a special input (`INPUT_PULLUP`). Add this line to your `setup()` function

```
pinMode(buttonPin, INPUT_PULLUP);
```

(2)  Add this line to your `loop()` function
```
int buttonState = digitalRead(buttonPin);
Serial.println(buttonState);
```

#### Compile and upload 

Compile errors? It happens. Not to worry. Where in our code do we define `buttonPin`? How does the code know to read from pin number 6?

### Open the Serial Monitor (*ctrl + shift + m*)

Let's take a look at the values that we get back from the button. What is interesting about this? Nothing?! Just ones and zeros! Perhaps but how does this effect our next coding task? 

### Change the code

(1) Add a new function
```
void reset(){
  isOpen = false;
}
```

(2) Replace the following lines
```
if(potValue > minPotValue && potValue < maxPotValue){
  open();
}
```
With the following
```
if( buttonState == LOW && lastButtonState == HIGH ){
  lastButtonState = LOW;
  open();
}
if( lastButtonState == LOW && buttonState == HIGH ){
  lastButtonState = HIGH;
  reset();
}
```

#### Discussion 

What is our `reset()` function doing?
What is the `lastButtonState` variable doing? 

### 6. Collecting the dial `positions[]`

**Question:** What is an array? 

### Add the code

```
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
```

#### Compile and upload 

Compile errors? Any bugs in our code? Gremlins in the system?

#### Open the Serial Monitor (*ctrl + shift + m*)

Move the potentiometer to any dial position. Push the button. Every time you push the button you should see the values you are storing on the serial monitor.   

#### Discussion

Why does the count start at 0 and not 1? Because...

### 7. Compare our dial positions with the lock `CODE[]` 

#### Change the code

(1) Add this new variable at the top of our sketch. Above the `setup()` function
```
int CODE[] = { 1, 2, 3 }; // Super secret code. Probably best to change this.  
```

(2) Add the following code to the bottom of our `loop()` function
```
  // If we have reached 3 values and the combination is correct.
  if( count == 3 ){
    if( CODE[0] == combinationAttempt[0] && CODE[1] == combinationAttempt[1] && CODE[2] == combinationAttempt[2]){
      open();  
    }
    reset();
  }
```

### Discussion

What are we doing here? What do we expect to happen?

### Compile & upload

We should now have a lockable box for your precious things. You can change the `CODE[]` to anything you want.

