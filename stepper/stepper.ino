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
    for(int i=0;i<=180;i++){
        s1.write(i);
        delay(30);
        // delay(30);
        // for(int j=1;j<=10;j++)
        //     s.rotate(0);
    }
    delay(2000);
    s1.write(0);
    delay(2000);
}
