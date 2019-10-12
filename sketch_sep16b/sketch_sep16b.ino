String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  pinMode(13, OUTPUT);
}

void loop() {
  if (stringComplete) {
    if(inputString == "on\n"){
      Serial.println("pornit");
      digitalWrite(13, HIGH);
    } else if(inputString == "off\n"){
      Serial.println("oprit");
      digitalWrite(13, LOW);
    } else Serial.println("nu exista comanda asta");
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
