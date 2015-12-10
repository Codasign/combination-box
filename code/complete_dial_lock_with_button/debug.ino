void reset() {
  // Set all of the variables back to how they started.
  Serial.println("***** RESET *****");
  isOpen = false;
  count = 0;
  dialPosition = 0;
  for (int i=0; i<3; i++) {
    combinationAttempt[i] = 0;
  }
}

void debug() {
  // An output string to allow us to see values in serial monitor for debugging.
  String output = "DEBUG: ";
  output += "(Count: ";
  output += count;
  output += ") ";
  output += "(Curent val: ";
  output += dialPosition;
  output += ") ";
  int i;
  for (i = 0; i < 3; i++) {
    output += combinationAttempt[i];
    output += ", ";
  }
  Serial.println(output);
}
