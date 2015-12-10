/*
 * Analog input - Reading the analog input sensor (e.g. potenitometer) 
 * and displaying this in the Serial Monitor.
 * @author Your Name Here
 */

void setup() {
  // Start the serial communication between the Arduino and computer.
  Serial.begin(9600);
}

void loop() {
  // Store the main analog input values.
  int sensorValue = analogRead(A0);

  // Concatenate/join together strings for a neat outout.
  String output = "Sensor value: ";
  output += sensorValue;

  // Output into serial monitor for debugging.
  Serial.println(output);
}
