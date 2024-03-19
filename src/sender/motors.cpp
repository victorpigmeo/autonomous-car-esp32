#include "motors.h"
#include <Arduino.h>

namespace Motors{
    void setupMotors(){
        Serial.println("===================================");

        pinMode(BACK, OUTPUT);
        pinMode(FRONT, OUTPUT);
        pinMode(LEFT, OUTPUT);
        pinMode(RIGHT, OUTPUT);

        Serial.println("Motors setted up");
        Serial.println("===================================");
    }
}
