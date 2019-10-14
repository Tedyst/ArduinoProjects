/* Unipolar stepper motor library for Arduino
created by Ashutosh M Bhatt (+91-9998476150) - Gujarat (INDIA) 

this library is used to control all types of unipolar motors with 4 phase
it can control its speed-RPM with 95% accuracy
it can rotate motor clockwise - counter clockwise continuously at set speed (RPM) 
it can rotate motor to only one revolution or desire number of revolutions in required direction

just one has to select arduino pins for motor, number of steps of motor for one revolution and desire RPM to rotate motor
and then then start rotating motor using given library functions

ver 1.0 was created on 12/10/2016 with 9 functions that can rotate motor in single coil exciation mode only 
ver 1.1 was created on 10/1/2017 with two additional functions (total 11 functions) that can rotate motor in half step as well as
double coil exciation mode also 
*/
#include "Arduino.h"
#include "Uni_polar_Stepper.h"

Uni_polar_Stepper::Uni_polar_Stepper(int pin1,int pin2,int pin3,int pin4)   // this is a constructor
  {
     pinMode(pin1,OUTPUT);                                                  // this will create an instance of Uni_polar_Stepper
     pinMode(pin2,OUTPUT);                                                  // in the arduino sketch with stepper motor driver pins
     pinMode(pin3,OUTPUT);
     pinMode(pin4,OUTPUT);     
     digitalWrite(pin1,LOW);
     digitalWrite(pin2,LOW);
     digitalWrite(pin3,LOW);
     digitalWrite(pin4,LOW);
     pin_1 = pin1;
     pin_2 = pin2;
     pin_3 = pin3;
     pin_4 = pin4;
  }
///////////////////////////// this function will set number of steps required by stepper motor to complete 1 revolution ///////////////  
 void Uni_polar_Stepper::set_step_per_rev(int steps)                        
  {
      motor_steps = steps;                                                  // 
  }

 void Uni_polar_Stepper::set_RPM(int rpm)
  {
      //  motor_speed_del = 100;  
       motor_speed_del = 60000/(rpm*motor_steps);  
  }
/*this function will calculate and set the delay applied between pulses applied to stepper motor
to calculate delay it takes motor rpm and motor steps per revolutions
60 RPM = 1 RPS
1 RPS means - 1 revolution in 1 sec
means in 1 sec we have to apply N number of pulses to complete 1 revolution
but that is the frequency of applied pulses 
- means time period of pulses will be 1/N. 
So as the time period of pulses is changed in mili seconds - the RPM of motor is changed as
60 / (pulse time period in sec � N) / 1000 - that means
RPM = 60000 / (pulse time period � N)
and pulse time period = 60000 / (RPM * N) where N = number of steps required by motor to complete 1 revolution
*/  
//////////////////////// // this function will start rotating motor clockwise //////////////////////////////////////   
 void Uni_polar_Stepper::rotate_CW()                                
  {
      digitalWrite(pin_1,HIGH);
      delay(motor_speed_del);
      digitalWrite(pin_1,LOW); 
      digitalWrite(pin_2,HIGH);
      delay(motor_speed_del); 
      digitalWrite(pin_2,LOW); 
      digitalWrite(pin_3,HIGH);
      delay(motor_speed_del); 
      digitalWrite(pin_3,LOW);
      digitalWrite(pin_4,HIGH);
      delay(motor_speed_del);     
      digitalWrite(pin_4,LOW);   
  } 
/////////////////////// this function will start rotating motor counter clockwise /////////////////////////////////     
 void Uni_polar_Stepper::rotate_CCW()                               
  {
      digitalWrite(pin_4,HIGH);
      delay(motor_speed_del);
      digitalWrite(pin_4,LOW); 
      digitalWrite(pin_3,HIGH);
      delay(motor_speed_del); 
      digitalWrite(pin_3,LOW); 
      digitalWrite(pin_2,HIGH);
      delay(motor_speed_del); 
      digitalWrite(pin_2,LOW);
      digitalWrite(pin_1,HIGH);
      delay(motor_speed_del);     
      digitalWrite(pin_1,LOW);   
  } 
////////////////////////// this function will rotate motor as per selected direction ///////////////////////////////////  
void Uni_polar_Stepper::rotate(int dir)                             
  {
     if(dir==1)                                                     // if direction flag is selected as 1 then it rotates CW
       {
         digitalWrite(pin_1,HIGH);
         delay(motor_speed_del);
         digitalWrite(pin_1,LOW); 
         digitalWrite(pin_2,HIGH);
         delay(motor_speed_del); 
         digitalWrite(pin_2,LOW); 
         digitalWrite(pin_3,HIGH);
         delay(motor_speed_del); 
         digitalWrite(pin_3,LOW);
         digitalWrite(pin_4,HIGH);
         delay(motor_speed_del);     
         digitalWrite(pin_4,LOW);  
       }   
      else                                                           // otherwise it will rotate CCW
       {
          digitalWrite(pin_4,HIGH);
          delay(motor_speed_del);
          digitalWrite(pin_4,LOW); 
          digitalWrite(pin_3,HIGH);
          delay(motor_speed_del); 
          digitalWrite(pin_3,LOW); 
          digitalWrite(pin_2,HIGH);
          delay(motor_speed_del); 
          digitalWrite(pin_2,LOW);
          digitalWrite(pin_1,HIGH);
          delay(motor_speed_del);     
          digitalWrite(pin_1,LOW);     
       }
   } 
void Uni_polar_Stepper::rotate_doublecoil(int dir)                             
  {
     if(dir==1)                                                     // if direction flag is selected as 1 then it rotates CW
       {
         digitalWrite(pin_1,HIGH);
         digitalWrite(pin_2,HIGH);
         delay(motor_speed_del);
         
         digitalWrite(pin_1,LOW); 
         digitalWrite(pin_3,HIGH);
         delay(motor_speed_del);
          
         digitalWrite(pin_2,LOW); 
         digitalWrite(pin_4,HIGH);
         delay(motor_speed_del); 
         
         digitalWrite(pin_3,LOW);
         digitalWrite(pin_1,HIGH);
         delay(motor_speed_del);   
          digitalWrite(pin_1,LOW); 
          digitalWrite(pin_4,LOW);         
       }   
      else                                                           // otherwise it will rotate CCW
       {
          digitalWrite(pin_4,HIGH);
          digitalWrite(pin_1,HIGH);
          delay(motor_speed_del);
          
          digitalWrite(pin_1,LOW); 
          digitalWrite(pin_3,HIGH);
          delay(motor_speed_del); 
          
          digitalWrite(pin_4,LOW); 
          digitalWrite(pin_2,HIGH);
          delay(motor_speed_del); 
          
          digitalWrite(pin_3,LOW);
          digitalWrite(pin_1,HIGH);
          delay(motor_speed_del);     
          digitalWrite(pin_1,LOW);   
          digitalWrite(pin_2,LOW);   
       }
   }        
/////////////////////////////// this function will rotate motor clockwise or anti clockwise in half step mode///////

void Uni_polar_Stepper::rotate_halfstep(int dir)                             
  {
     if(dir==1)                                                     // if direction flag is selected as 1 then it rotates CW
       {
         digitalWrite(pin_1,HIGH);
         delay(motor_speed_del);
         
         digitalWrite(pin_2,HIGH);
         delay(motor_speed_del); 
         
         digitalWrite(pin_1,LOW);         
         delay(motor_speed_del); 
         
         digitalWrite(pin_3,HIGH);
         delay(motor_speed_del); 
         
         digitalWrite(pin_2,LOW);
         delay(motor_speed_del); 
         
         
         digitalWrite(pin_4,HIGH);
         delay(motor_speed_del);  
         
            
         digitalWrite(pin_3,LOW); 
         delay(motor_speed_del);
         
         digitalWrite(pin_1,HIGH);
         delay(motor_speed_del);
         digitalWrite(pin_4,LOW); 
       }   
      else                                                           // otherwise it will rotate CCW
       {
           digitalWrite(pin_1,HIGH);
           digitalWrite(pin_4,HIGH);
           delay(motor_speed_del);
           
           digitalWrite(pin_1,LOW);
           delay(motor_speed_del);
           
           digitalWrite(pin_3,HIGH); 
           delay(motor_speed_del);
           
           digitalWrite(pin_4,LOW);
           delay(motor_speed_del); 
           
           digitalWrite(pin_2,HIGH); 
           delay(motor_speed_del);
           
           digitalWrite(pin_3,LOW); 
           delay(motor_speed_del);
           
           digitalWrite(pin_1,HIGH);
           delay(motor_speed_del);
           
           digitalWrite(pin_2,LOW); 
           delay(motor_speed_del);            
       }
   }   

//////////////////////// // this function will rotate motor exact 1 revolution //////////////////////////////////     
 void Uni_polar_Stepper::rotate_one_rev(int dir)                     
   {
      int i,j;
      if(dir==1)                                                     // in selected direction
        {
                for(i=0;i<motor_steps/4;i++)
                  {
                    digitalWrite(pin_1,HIGH);
                    delay(motor_speed_del);
                    digitalWrite(pin_1,LOW); 
                    digitalWrite(pin_2,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_2,LOW); 
                    digitalWrite(pin_3,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_3,LOW);
                    digitalWrite(pin_4,HIGH);
                    delay(motor_speed_del);     
                    digitalWrite(pin_4,LOW);  
                  } 
           }
       else 
         {
                for(i=0;i<motor_steps/4;i++)
                  {
                    digitalWrite(pin_4,HIGH);
                    delay(motor_speed_del);
                    digitalWrite(pin_4,LOW); 
                    digitalWrite(pin_3,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_3,LOW); 
                    digitalWrite(pin_2,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_2,LOW);
                    digitalWrite(pin_1,HIGH);
                    delay(motor_speed_del);     
                    digitalWrite(pin_1,LOW);
                  } 
           }     
   }  
//////////// this function will rotate motor required number of revolutions in selected directions ////////////////        
 void Uni_polar_Stepper::rotate_n_rev(int dir,int num)               
   {                                                                 // 
      int i;
      if(dir==1)
        {
                for(i=0;i<(motor_steps*num/4);i++)
                  {
                    digitalWrite(pin_1,HIGH);
                    delay(motor_speed_del);
                    digitalWrite(pin_1,LOW); 
                    digitalWrite(pin_2,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_2,LOW); 
                    digitalWrite(pin_3,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_3,LOW);
                    digitalWrite(pin_4,HIGH);
                    delay(motor_speed_del);     
                    digitalWrite(pin_4,LOW);  
                  } 
           }
       else 
         {
                for(i=0;i<(motor_steps*num/4);i++)
                  {
                    digitalWrite(pin_4,HIGH);
                    delay(motor_speed_del);
                    digitalWrite(pin_4,LOW); 
                    digitalWrite(pin_3,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_3,LOW); 
                    digitalWrite(pin_2,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_2,LOW);
                    digitalWrite(pin_1,HIGH);
                    delay(motor_speed_del);     
                    digitalWrite(pin_1,LOW);
                  } 
           }                               
   }
//////////////// this function will rotate motor to desire angle from 0 - 360 deg in either direction ///////////////////   
 void Uni_polar_Stepper::rotate_x_deg(int deg)               
   {                                                                 // 
      int i,degree,dir;
      if(deg>180) 
        {
          deg = 360 - deg;
          dir = 0;
          }
       else dir = 1;     
      degree = (motor_steps*deg)/360;
      if(dir==1)
        {
                for(i=0;i<(degree/4);i++)
                  {
                    digitalWrite(pin_1,HIGH);
                    delay(motor_speed_del);
                    digitalWrite(pin_1,LOW); 
                    digitalWrite(pin_2,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_2,LOW); 
                    digitalWrite(pin_3,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_3,LOW);
                    digitalWrite(pin_4,HIGH);
                    delay(motor_speed_del);     
                    digitalWrite(pin_4,LOW);  
                  } 
           }
       else 
         {
                for(i=0;i<(degree/4);i++)
                  {
                    digitalWrite(pin_4,HIGH);
                    delay(motor_speed_del);
                    digitalWrite(pin_4,LOW); 
                    digitalWrite(pin_3,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_3,LOW); 
                    digitalWrite(pin_2,HIGH);
                    delay(motor_speed_del); 
                    digitalWrite(pin_2,LOW);
                    digitalWrite(pin_1,HIGH);
                    delay(motor_speed_del);     
                    digitalWrite(pin_1,LOW);
                  } 
           }                               
   }
