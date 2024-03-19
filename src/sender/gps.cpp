#include "gps.h"
#include <Arduino.h>

namespace GPS{

    void setupGPS(){
        Serial.println("===================================");
        Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, RXD2, TXD2);

        Serial.println("GPS Initialized");
        Serial.println("===================================");
    }

}
