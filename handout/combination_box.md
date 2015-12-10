![Codasign logo](http://codasign.com/wp-content/themes/codasign/library/images/logo.png)
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

POT

#### Add some code
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

Clicking on the tick icon/button will compile your code. Converting the code you've written into a format that Arduino understands. It will also tell you if you have any errors in your code. 

If everything is ok then click the 'right arrow' icon/button. This will upload your code to the Arduino.

#### Open Serial Monitor

Cicking on the magnifying glass will open up the Serial Monitor and allow you to see what position the potentiometer is currently at.


### 2. Analog input and Analog output - Controlling an LED

**Question:** What do the `setup()` and `loop()`  functions do?

#### Build the circuit

POT AND LED

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

POT AND SERVO

#### Add some code

```
 /*
 * Analog input & sweep - Using the analog input sensor (e.g. potenitometer) 
 * to decide when we want start moving the servo.
 * @author Your Name Here
 */

#include <Servo.h>

// Create 'Servo' object to control a servo 
Servo myServo;

int potPin = A0;
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

#### PAUSE

What do we expect to happen when we upload our code??


#### Compile and upload 

Compile errors? Upload errors?

#### Change the code

(1) We don't want the servo to `open()` when the sketch starts. How do we stop that from happening?
(2) We only want the servo to `open()` when the potentiometer is at a certain point. How do we make this happen? Look at line number 35.

#### Compile and upload 


### 4. Create our dial positions and add the button



