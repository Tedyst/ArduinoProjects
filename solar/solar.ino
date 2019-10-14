#include <Arduino.h>
#include <Stepper.h>
#include <EEPROM.h>
#include <Servo.h>
// Hydro section
// Trigger is a value from (0, 255) which specifies when to trigger the watering system
#define HYDRO_MIN 100
#define HYDRO_MAX 0
#define HYDRO_TRIGGER 120

// Solar section
#define STEPPER_SPEED 5
#define STEPS_PER_REVOLUTION 2048
#define LIGHT_ALLOWANCE 0.45

// Pins
#define X1_PIN 1
#define X2_PIN 2
#define Y1_PIN 3
#define Y2_PIN 4
#define HYDRO_PIN 5
#define STEPPER_PIN1 11
#define STEPPER_PIN2 10
#define STEPPER_PIN3 9
#define STEPPER_PIN4 8

#define SERVO_Y 6
Servo servo_y;
Stepper stepper_y = Stepper(STEPS_PER_REVOLUTION, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);
int last_direction = -1;
int hydro_timeout = 0;

/* ADRESS MAP EEPROM
    0 -> last stepper position ( range 0-180 )
*/
unsigned int stepper_position;
void setup() {
    stepper_y.setSpeed(STEPPER_SPEED);
    servo_y.attach(SERVO_Y);
    Serial.begin(9600);
    stepper_position = EEPROM.read(0);

    if (stepper_position > 180) {
        // Init EEPROM
        stepper_position = 0;
        EEPROM.write(0, 0);
    }

    Serial.print("Pozitia initiala a stepperului: ");
    Serial.print(stepper_position);
    Serial.print('\n');
}

int direction() {
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

    // Initialize the maximum and its id with the first element from the array
    int id = 0;
    double maxim = vect[0];
    // Get the max value and its indices from the array
    for(int i = 1; i < 8 ; i++)
        if(maxim < vect[i]) {
            maxim = vect[i];
            id = i;
        }
    Serial.print("Selectat cadranul(cred) ");
    Serial.print(id + 1);
    Serial.print(" cu maxmimul ");
    Serial.print(maxim);
    Serial.print('\n');
    return id + 1;
}

void move_to_y(int direction) {
    int angle_needed = 0;
    // 22.5 degrees per direction
    if(direction * 22.5 + stepper_position > 180) {
        angle_needed = - direction * 22.5 - stepper_position;
        stepper_position = direction * 22.5 - stepper_position - 180;
    } else {
        angle_needed = direction * 22.5 + stepper_position;
        stepper_position = angle_needed;
    }
    // Write the new position to EEPROM
    EEPROM.write(0, stepper_position);

    Serial.print("Unghiul dorit pe y este de ");
    Serial.print(direction * 22.5 + stepper_position);
    Serial.print(", deci ne rotim ");
    Serial.print(angle_needed);
    Serial.print('\n');
    // roughly 11.333 steps per degree
    stepper_y.step(ceil(angle_needed * 11.333));
}

void move_to_x(int direction) {

}

void solar_axis_x(int new_direction = direction()) {
    Serial.print("Directia dorita din acest moment este: ");
    Serial.println(new_direction);
    if(last_direction == -1) {
        // 0 is the initial direction
        move_to_x(0);
        last_direction = 0;
        return;
    }
    if(last_direction != new_direction) {
        Serial.print("Directia dorita trebuie schimbata in ");
        Serial.print(new_direction);
        Serial.print(". Va fi schimbata in 3 secunde.");
        Serial.print('\n');
        for(int i = 1; i <= 3; i++) {
            if(new_direction != direction()) {
                Serial.println("Anulare schimbare directie.");
                return;
            }
            delay(1000);
        }
        move_to_x(new_direction);
    }
}

void serial() {
    String inString;
    int command = 0;
    /* Available commands:
        1. set_home_x <int> -> runs schimba_directia_x(<int>)
        2. water -> runs watering_system()
    */

    while (Serial.available() > 0) {
        int inChar = Serial.read();
        if(inChar == '\n') {
            if(command == 1) {
                Serial.print("Primit comanda set_home_x ");
                int val = inString.toInt();
                Serial.print(val);
                Serial.print('\n');
                solar_axis_x(val);
                last_direction = 0;
            } else if(command == 2) {
                Serial.print("Primit comanda water");
                watering_system();
            }
            inString = "";
        } else if(inChar == ' ') {
            if(inString == "set_home_x") {
                command = 1;
                inString = "";
            } else if(inString == "water") {
                command = 2;
                inString = "";
            }
        } else {
            inString += inChar;
        }
    }
}

void watering_system() {
    // TODO: Sa vad ce trb sa fac aici
}

void hydro() {
    // If the humidity reaches HYDRO_TRIGGER, run the watering system
    int raw = analogRead(HYDRO_PIN);
    int humidity = map(raw, HYDRO_MIN, HYDRO_MAX, 0, 255);
    if(humidity < HYDRO_TRIGGER) {
        Serial.print("A fost atins nivelul de apa necesar pornirii irigarii.\nNivelul actual este: ");
        Serial.print(humidity);
        Serial.print('\n');
        watering_system();
        hydro_timeout = 30;
    }
}

void loop() {
    solar_axis_x();
    serial();
    if(hydro_timeout > 0) {
        hydro_timeout --;
    } else {
        // hydro();
    }
    delay(1000);
}
