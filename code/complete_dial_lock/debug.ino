void debug() {
  // An output string to allow us to see values in serial monitor for debugging.
  String output = "DEBUG: ";
  output += "(Index: ";
  output += count;
  output += ") ";
  output += "(Direction: ";
  output += dialDirection;
  output += ") ";
  output += "(Curent val: ";
  output += dialPosition;
  output += ") ";
  int i;
  for (i = 0; i < 3; i++) {
    output += combinationAttempt[i];
    output += ", ";
  }
  if(dialDirection != 0){
    Serial.println(output);
  }
}
