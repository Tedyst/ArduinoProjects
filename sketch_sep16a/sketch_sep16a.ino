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
Stepper stepper = Stepper(STEPS_PER_REVOLUTION, 11, 10, 9, 8);
int ultima_directie = -1;
/* ADRESS MAP EEPROM
    0 -> last stepper position byte 1
*/
unsigned int StepperPos;
void setup() {
  stepper.setSpeed(STEPPER_SPEED);
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
  int x1 = analogRead(X1_PIN);
  int x2 = analogRead(X2_PIN);
  int y1 = analogRead(Y1_PIN);
  int y2 = analogRead(X2_PIN);
  
  // Si pe mine ma doare cand ma uit
  int maxim = 0;
  maxim = max(maxim, x1);
  maxim = max(maxim, x2);
  maxim = max(maxim, y1);
  maxim = max(maxim, y2);
  maxim = max(maxim, (x1+y1)*LIGHT_ALLOWANCE);
  maxim = max(maxim, (x1+x2)*LIGHT_ALLOWANCE);
  maxim = max(maxim, (y1+y2)*LIGHT_ALLOWANCE);
  maxim = max(maxim, (x2+y2)*LIGHT_ALLOWANCE);

  // Ia directia
  if(maxim == x1) return 1;
  if(maxim == (x1+y1)*LIGHT_ALLOWANCE) return 2;
  if(maxim == y1) return 3;
  if(maxim == (y1+y2)*LIGHT_ALLOWANCE) return 4;
  if(maxim == y2) return 5;
  if(maxim == (x2+y2)*LIGHT_ALLOWANCE) return 6;
  if(maxim == x2) return 7;
  if(maxim == (x1+x2)*LIGHT_ALLOWANCE) return 8;
}
int muta_spre_directie(int directie){
  
}
void schimba_directia(){
  Serial.print("Directia dorita din acest moment este: ");
  int nouadirectie = directie();
  Serial.println(nouadirectie);
  if(ultima_directie == -1){
    // 0 este directia initiala
    mutaspredirectie(0);
    ultimadirectie = 0;
    return;
  }
  if(ultimadirectie != nouadirectie){
    Serial.print("Directia dorita trebuie schimbata in ");
    Serial.print(nouadirectie);
    Serial.print(". Va fi schimbata in 3 secunde.");
    Serial.print('\n');
    for(int i = 1; i <= 3; i++){
      if(nouadirectie != directie()){
        Serial.println("Anulare schimbare directie.");
        return;
      }
      delay(1000);
    }
  }
}
void loop() {
  schimba_directia();
  delay(1000);
}
