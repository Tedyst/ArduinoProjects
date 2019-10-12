#include <Stepper.h>
#include <EEPROM.h>
#define STEPS_PER_REVOLUTION 2048
#define MAX_HYDRO 100
#define MIN_HYDRO 0
#define HYDRO_PERCENTAGE 60
#define STEPPER_SPEED 5
#define X1_PIN 1
#define X2_PIN 2
#define Y1_PIN 3
#define Y2_PIN 4
#define LIGHT_ALLOWANCE 0.75
Stepper stepper_x = Stepper(STEPS_PER_REVOLUTION, 11, 10, 9, 8);
int last_direction = -1;
/* ADRESS MAP EEPROM
    0 -> last stepper position ( range 0-180 )
*/
unsigned int StepperPos;
void setup() {
  stepper_x.setSpeed(STEPPER_SPEED);
  Serial.begin(9600);
  StepperPos = EEPROM.read(0);
  
  if (StepperPos > 180) {
    // Init EEPROM
    StepperPos = 0;
    EEPROM.write(0, 0);
  }
  
  Serial.print("Pozitia initiala a stepperului: ");
  Serial.println(StepperPos);
}
int directie() {
  // Get sensors data
  double x1 = analogRead(X1_PIN);
  double x2 = analogRead(X2_PIN);
  double y1 = analogRead(Y1_PIN);
  double y2 = analogRead(X2_PIN);

  // Put the values in the array  
  double vect[] = {
    x1, 
    (int)(x1+y1)*LIGHT_ALLOWANCE, 
    y1, 
    (int)(y1+y2)*LIGHT_ALLOWANCE,
    y2,
    (int)(x2+y2)*LIGHT_ALLOWANCE,
    x2,
    (int)(x1+x2)*LIGHT_ALLOWANCE
  };

  // Get the max value and its indices from the array 
  int id = 0;
  double maxim = vect[1];
  for(int i = 1; i < 8 ; i++)
    if(maxim < vect[i]){
      maxim = vect[i];
      id = i+1;
    }

  return id;
}
int muta_spre_directie(int directie){
  
}
void schimba_directia_x(){
  Serial.print("Directia dorita din acest moment este: ");
  int new_direction = directie();
  Serial.println(new_direction);
  if(last_direction == -1){
    // 0 este directia initiala
    muta_spre_directie(0);
    last_direction = 0;
    return;
  }
  if(last_direction != new_direction){
    Serial.print("Directia dorita trebuie schimbata in ");
    Serial.print(new_direction);
    Serial.print(". Va fi schimbata in 3 secunde.");
    Serial.print('\n');
    for(int i = 1; i <= 3; i++){
      if(new_direction != directie()){
        Serial.println("Anulare schimbare directie.");
        return;
      }
      delay(1000);
    }
  }
}
void serial(){
  string inString = ""; 
  int command = 0;
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if(inChar == '\n'){
        if(command == 1){
          print("Received command set_home_x ");
          int val = inString.toInt();
          print(val);
          print('\n');
          schimba_directia_x(val);
          last_direction = 0;
        }
        inString = "";
    } else if(inChar == ' '){
      if(inString == "set_home_x"){
          command = 1;
          inString = "";
      }
    } else { 
      inString += inChar;
    }
  }
}
void loop() {
  schimba_directia_x();
  serial();
  delay(1000);
}
