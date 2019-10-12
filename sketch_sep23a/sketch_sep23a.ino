/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup() {
  Serial.begin(9600);
  int i;
  // 
  for(i=EEPROM.begin(); i != EEPROM.length(); i++){
    EEPROM.write(i, 255);
    int x = EEPROM.read(i);
    Serial.print(i);
    Serial.print(' ');
    Serial.print(x);
    Serial.print('\n');    
    delay(10);
  }
}

void loop() {
  delay(500);
}
