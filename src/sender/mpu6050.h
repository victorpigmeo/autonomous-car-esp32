#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#ifndef MPU6050_H_
#define MPU6050_H_

namespace MPU6050{
    #define PACKETS_QUANTITY 2

    void setupMPU6050();
    void telemetryTask(void *pvParameters);
}

#endif // MPU6050_H_
