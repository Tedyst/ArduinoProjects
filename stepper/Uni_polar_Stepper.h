/* Unipolar stepper motor library for Arduino
created by Ashutosh M Bhatt (+91-9998476150) - Gujarat (INDIA) 

this library is used to control all types of unipolar motors with 4 phase
it can control its RPM with 95% accuracy
it can rotate motor clockwise - counter clockwise continuously at set speed (RPM) 
it can rotate motor to desire number of rotations in required direction
and also it can rotate motor only one revolution
just one has to select arduino pins for motor, number of steps of motor and desire RPM to rotate motor
and then then start rotating motor using given library functions

ver 1.0 was created on 12/10/2016 with 9 functions that can rotate motor in single coil exciation mode only 
ver 1.1 was created on 10/1/2017 with two additional functions (total 11 functions) that can rotate motor in half step as well as
double coil exciation mode also 

*/
#ifndef Uni_polar_Stepper_h
#define Uni_polar_Stepper_h

#include "Arduino.h"

class Uni_polar_Stepper
  { 
    private:
            int pin_1,pin_2,pin_3,pin_4,motor_steps,motor_speed_del;
    public:
    Uni_polar_Stepper(int pin1,int pin2,int pin3,int pin4);
    void rotate_CW(void);
    void rotate_CCW(void);
    void set_RPM(int rpm);
    void set_step_per_rev(int steps);
    void rotate(int dir);
    void rotate_halfstep(int dir);
    void rotate_doublecoil(int dir);
    void rotate_one_rev(int dir);
    void rotate_n_rev(int dir,int num);
    void rotate_x_deg(int deg);
  };
  
#endif
