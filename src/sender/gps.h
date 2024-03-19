#ifndef GPS_H_
#define GPS_H_

#include <TinyGPS++.h>

namespace GPS{
#define GPS_BAUDRATE 9600
#define RXD2 16
#define TXD2 17

    void setupGPS();
}
#endif // GPS_H_
