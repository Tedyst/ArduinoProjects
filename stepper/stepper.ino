#include <Arduino.h>
#include "Uni_polar_Stepper.h"
#include <Servo.h>

Uni_polar_Stepper s = Uni_polar_Stepper(8, 9, 10, 11);
Servo s1;

void setup() {
  Serial.begin(9600);
  s.set_step_per_rev(2048);
  s1.attach(2);
}

void loop() {
    s1.write(90);
    s.set_RPM(300);
    for(int i=1;i<=180;i++){
        s1.write(i);
        s.rotate(0);
        s.rotate(0);
    }
    for(int i=1;i<=180;i++){
        s1.write(180-i);
        s.rotate(1);
        s.rotate(1);
    }
    for(int i=1;i<=180;i++){
        s1.write(i);
        s.rotate(1);
        s.rotate(1);
    }
    for(int i=1;i<=180;i++){
        s1.write(180-i);
        s.rotate(1);
        s.rotate(1);
    }
}
