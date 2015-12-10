![Codasign logo](http://codasign.com/wp-content/themes/codasign/library/images/logo.png)
Combination Dial Lock Workshop
======================

## What is a Combination Dial Lock?
![Combination Lock](https://media2.giphy.com/media/ABfNx2KM7dB7O/200.gif)

A single dial combination lock is a type of locking mechanism found on padlocks, lockers, or safes. It uses a single dial which interacts with several aligned discs or cams. A lock of this type is opened by rotating the dial clockwise to the first number, then counterclockwise to the second, and so on alternating direction until the last numeral is reached. 

![Mechanics](http://media.web.britannica.com/eb-media/64/2164-004-7B9FD482.gif)

Below is a link to a great video of a home made wooden dial lock. Shows the inner workings of a dial locking mechanism. [https://www.youtube.com/watch?v=1-fFCrLwhPo](https://www.youtube.com/watch?v=1-fFCrLwhPo)

This is how a mechanical dial locks work. Today we will be simluate the inner workings of a combination lock with electronic components and Arduino.


## 1. Analog input - Receiving the value of our potentiometer

** Question: ** Why is our potentiometer an analog input?

### Build the circuit


### Add your code
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

### Compile & Upload your code

Clicking on the tick icon/button will compile your code. Converting the code you've written into a format that Arduino understands. It will also tell you if you have any errors in your code. 

If everything is ok then click the 'right arrow' icon/button. This will upload your code to the Arduino.

### Open Serial Monitor

Cicking on the magnifying glass will open up the Serial Monitor and allow you to see what position the potentiometer is currently at.


## 2. Analog input and Analog output - Controlling our LED

### Build the circuit

### Add your code



