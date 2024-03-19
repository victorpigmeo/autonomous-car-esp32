#include "mpu6050.h"
#include "lora.h"
#include "util.h"

namespace MPU6050{

    Adafruit_MPU6050 mpu;

    struct MPU6050Telemetry{
        float gyro[3];
        float acceleration[3];
        float temperature;

        MPU6050Telemetry(sensors_event_t g, sensors_event_t a, sensors_event_t temp){
            gyro[0] = g.gyro.x;
            gyro[1] = g.gyro.y;
            gyro[2] = g.gyro.z;

            acceleration[0] = a.acceleration.x;
            acceleration[1] = a.acceleration.y;
            acceleration[2] = a.acceleration.z;

            temperature = temp.temperature;
        }

// TODO make a fn that returns the packets from this struct data
//         const int8_t** toBytesPacket(){
// // ((gyro[0] - (int8_t)gyro[0])*1000)
//                         //  const int8_t temperature[4] = {2, 7, (int8_t)temperature, 0};

//             const int8_t* telemetryPackets[PACKETS_QUANTITY] =
//                 {gyroX,
//                  gyroY,
//                  // gyroZ,
//                  // accelerationX,
//                  // accelerationY,
//                  // accelerationZ,
//                  // temperature
//             };

//             return telemetryPackets;
//         }
    };
    
    void setupMPU6050(){
        Serial.println("===================================");

        if(!mpu.begin()){
            Serial.println("Failed to find MPU6050");
        }

        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
        mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
        mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

        Serial.println("Gyro intialized");
        Serial.println("===================================");
    }

    uint8_t getUnsignedFractional(float floatValue){
         return ((Util::precision(floatValue, 2) - (uint8_t)floatValue)*1000);
    }

    void telemetryTask(void *pvParameters){
        Serial.println("===================================");
        Serial.println("Gyro telemetry started");
        Serial.println("===================================");

        while(true){
            sensors_event_t a, g, temp;
            mpu.getEvent(&g, &a, &temp);

            MPU6050Telemetry telemetryPacket = MPU6050Telemetry(g, a, temp);

            int8_t gyroX[4] = {2, 1, (int8_t)telemetryPacket.gyro[0], getUnsignedFractional(telemetryPacket.gyro[0])};
            int8_t gyroY[4] = {2, 2, (int8_t)telemetryPacket.gyro[1], getUnsignedFractional(telemetryPacket.gyro[1])};
            int8_t gyroZ[4] = {2, 3, (int8_t)telemetryPacket.gyro[2], getUnsignedFractional(telemetryPacket.gyro[2])};
            int8_t accelerationX[4] = {2, 4, (int8_t)telemetryPacket.acceleration[0], getUnsignedFractional(telemetryPacket.acceleration[0])};
            int8_t accelerationY[4] = {2, 5, (int8_t)telemetryPacket.acceleration[1], getUnsignedFractional(telemetryPacket.acceleration[1])};
            int8_t accelerationZ[4] = {2, 6, (int8_t)telemetryPacket.acceleration[2], getUnsignedFractional(telemetryPacket.acceleration[2])};
            int8_t temperature[4] = {2, 7, (uint8_t)telemetryPacket.temperature, getUnsignedFractional(telemetryPacket.temperature)};

            LoRaSender::send(gyroX);
            LoRaSender::send(gyroY);
            LoRaSender::send(gyroZ);
            LoRaSender::send(accelerationX);
            LoRaSender::send(accelerationY);
            LoRaSender::send(accelerationZ);
            LoRaSender::send(temperature);

            delay(10);
        }
    }

}
