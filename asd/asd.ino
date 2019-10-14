#include <Arduino.h>
#include <Servo.h>
Servo s;
void setup(){
    s.attach(A0);
}
void loop(){
  for(int i=1;i<=180;i+=1){
    s.write(i);
    delay(100);//
  }
  for(int i=180;i>=1;i-=1){
    s.write(i);
    delay(100);
  }
}
