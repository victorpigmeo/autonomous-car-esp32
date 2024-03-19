// Received packet: SAT:6 | LATLNG:-25.435027,-49.303831 | BLNTH:435027167,303830667 | SPD:0.24 | ALT:954.20 | CRS:11900 |

#include <Arduino.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define NSS 4
#define RST 5
#define DI0 15
#define LED_BUILTIN 2

#define BACK 25
#define FRONT 26
#define LEFT 33
#define RIGHT 32

#define GPS_BAUDRATE 9600
#define RXD2 16
#define TXD2 17

TinyGPSPlus gps;
Adafruit_MPU6050 mpu;

// struct LoRaPacket {
//     int8_t sensor;
//     int8_t payloadSize;
//     String payload;

//     String toString(){
//         char buffer[257];

//         sprintf(buffer, "%d|%d|%s", sensor, payloadSize, payload);
//         return buffer;
//     }

// };

// struct GPSData {
//     int8_t latitude;
//     int latitudeBillion;
//     int16_t longitude;
//     int longitudeBillion;
//     float speed;
//     float altitude;

//     String toString(){
//         char buffer[255];

//         sprintf(buffer, "%d|%d|%d|%d", latitude, latitudeBillion, longitude, longitudeBillion);
//         return buffer;
//     }
// };

unsigned char* intToByte(const int& N) {

    unsigned char* byte = new unsigned char[4];

    byte[0] = (N >> 24) & 0xFF;
    byte[1] = (N >> 16) & 0xFF;
    byte[2] = (N >> 8) & 0xFF;
    byte[3] = N & 0xFF;

    return byte;
}

void telemetryTask(void *pvParameters){
    while(true){
        sensors_event_t a, g, temp;
        mpu.getEvent(&g, &a, &temp);

        digitalWrite(LED_BUILTIN, LOW);

        //1=GPS;1=LAT;<int>;<float>
        int packet_lat[4] = {1, 1, -25, 435027167};
        int packet_lng[4] = {1, 2, -49, 303830667};
        int packet_spd[4] = {1, 3, 0, 24};
        int packet_alt[4] = {1, 4, 954, 20};

        //GTA = giroscopio temperatura acelerometro
        //2=GTA;1=GYRO_X;1=<int>;<float>
        //2=GTA;1=GYRO_Y;2=<int>;<float>
        //2=GTA;1=GYRO_Z;3=<int>;<float>
        //2=GTA;1=ACEL_X;4=<int>;<float>
        //2=GTA;1=ACEL_Y;5=<int>;<float>
        //2=GTA;1=ACEL_Z;6=<int>;<float>
        //2=GTA;1=TEMP;7=<int>;<float>
        int8_t packet_gyro_x[4] = {2, 1, 1, 10};
        int8_t packet_gyro_y[4] = {2, 2, -9, 20};
        int8_t packet_gyro_z[4] = {2, 3, 10, 30};


        //MOTOR
        //3=MOTOR;1=MOTOR_LEFT;<on/off>;<zero-fill>
        uint8_t motor_packet[4] = {3, 1, digitalRead(LEFT), 0};
        // LoRaPacket gpsPacket;
        // gpsPacket.sensor = 1;

        // GPSData gpsData;
        // gpsData.latitude = -25;
        // gpsData.latitudeBillion = 435027167;
        // gpsData.longitude = -49;
        // gpsData.longitudeBillion = 303830667;
        // gpsData.speed = 0.24;
        // gpsData.altitude = 954.20;

        // gpsPacket.payload = gpsData.toString();
        // gpsPacket.payloadSize = sizeof(gpsPacket.payload);

        // Serial.println(gpsPacket.payload);
        // Serial.println(gpsPacket.payloadSize);

        // char packet[16];
        // sprintf(packet, "%d%d%d%d", packet_lat[0], packet_lat[1], packet_lat[2], packet_lat[3]);

        // LoRa.beginPacket();
        // for(int i = 0; i < 4; i++){
        //     byte* bytes = intToByte(packet_lat[i]);
        //     Serial.println((char *)bytes);
        //     LoRa.write(bytes, sizeof(bytes));
        // }
        // LoRa.endPacket();




        LoRa.beginPacket();
        for(int i = 0; i < 4; i++){
            byte bytes = motor_packet[i];
            Serial.println(bytes);
            LoRa.write(bytes);
        }
        LoRa.endPacket();


        // LoRa.beginPacket();
        // for(int i = 0; i < 4; i++){
        //     byte* bytes = intToByte(packet_lat[i]);
        //     Serial.println((char *)bytes);
        //     LoRa.write(bytes, sizeof(bytes));
        // }
        // LoRa.endPacket();

        // LoRa.beginPacket();
        // for(int i = 0; i < 4; i++){
        //     byte* bytes = intToByte(packet_lng[i]);
        //     Serial.println((char *)bytes);
        //     LoRa.write(bytes, sizeof(bytes));
        // }
        // LoRa.endPacket();

        // delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(10);
    }
}

void walkTask(void *pvParameters){
    while(true){
        sensors_event_t a, g, temp;
        mpu.getEvent(&g, &a, &temp);

        Serial.print("OI | ");
        Serial.println(g.gyro.x);

        delay(500);
    }
}

void setup(){
    Serial.begin(115200);
    delay(3000);
    Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, RXD2, TXD2);

    Serial.println("===================================");
    Serial.println("Pins");
    Serial.println("===================================");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BACK, OUTPUT);
    pinMode(FRONT, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(RIGHT, OUTPUT);

    Serial.println("Pins setted");

    Serial.println("===================================");
    Serial.println("Gyro");
    Serial.println("===================================");

    if(!mpu.begin()){
        Serial.println("Failed to find MPU6050");
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    Serial.println("Gyro intialized");

    Serial.println("===================================");
    Serial.println("LoRa Sender");
    Serial.println("===================================");

    LoRa.setPins(NSS, RST, DI0);

    while(!LoRa.begin(433E6)){
        Serial.print(".");
        delay(500);
    }

    LoRa.setSyncWord(0xFA);
    Serial.println("LoRa Initialized");

    xTaskCreate(telemetryTask, "telemetryTask", 2048, NULL, 1, NULL);
    // xTaskCreate(walkTask, "walkTask", 2048, NULL, 1, NULL);
}

void loop(){
    digitalWrite(LEFT, HIGH);
    delay(2000);

    digitalWrite(LEFT, LOW);
    delay(2000);
}

// void loop(){
// digitalWrite(LED_BUILTIN, LOW);


// delay(500);
// digitalWrite(LED_BUILTIN, HIGH);


// if (Serial2.available() > 0) {
    //     if (gps.encode(Serial2.read())) {
    //         LoRa.beginPacket();

    //         LoRa.print("SAT:");
    //         LoRa.print(gps.satellites.value());
    //         LoRa.print(String(" | "));

    //         LoRa.print("LATLNG:");
    //         LoRa.print(gps.location.lat(), 6);
    //         LoRa.print(",");
    //         LoRa.print(gps.location.lng(), 6);
    //         LoRa.print(String(" | "));

    //         LoRa.print("BLNTH:");
    //         LoRa.print(gps.location.rawLat().billionths);
    //         LoRa.print(",");
    //         LoRa.print(gps.location.rawLng().billionths);
    //         LoRa.print(String(" | "));

    //         LoRa.print("SPD:");
    //         LoRa.print(gps.speed.kmph());
    //         LoRa.print(String(" | "));

    //         LoRa.print("ALT:");
    //         LoRa.print(gps.altitude.meters());
    //         LoRa.print(String(" | "));

    //         LoRa.print("CRS:");
    //         LoRa.print(gps.course.value());
    //         LoRa.print(String(" | "));

    //         Serial.println("Packet sent");
    //         delay(2000);
    //         digitalWrite(LED_BUILTIN, HIGH);
    //         delay(100);

    //         LoRa.endPacket();
    //     }
    // }else{
    //     LoRa.beginPacket();

    //     Serial.println("GPS Not Available");
    //     LoRa.println("GPS Not Available");

    //     LoRa.endPacket();

    //     digitalWrite(LED_BUILTIN, HIGH);
    //     delay(500);
    // }

// }
