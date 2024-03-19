#include <Arduino.h>
#include <LoRa.h>

#define NSS 4
#define RST 5
#define DI0 22
#define LED_BUILTIN 2

void onReceive(int packetSize){

    // if the packer size is not 0, then execute this if condition
    // received a packet
    // Serial.print("Received packet '");

    // // read packet
    // for (int i = 0; i < packetSize; i++) {
    //   Serial.print((char)LoRa.read());
    // }

    // // print RSSI of packet
    // Serial.print("' with RSSI ");
    // Serial.println(LoRa.packetRssi());

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("ACESO");
    delay(500);

    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("APAGADO");
    delay(500);
}

void setup(){
    Serial.begin(115200);
    delay(3000);

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("===================================");
    Serial.println("LoRa Receiver");
    Serial.println("===================================");

    LoRa.setPins(NSS, RST, DI0);

    if(!LoRa.begin(433E6)){
        Serial.print("DEU RUIM");
        while(1);
    }

    Serial.println("LoRa Initialized");

    LoRa.setSyncWord(0xFA);

    // register the receive callback
    // LoRa.onReceive(onReceive);

    // LoRa.receive();
}

void loop(){
    int packetSize = LoRa.parsePacket();

    if(packetSize) {
        // Serial.println(packetSize);
        // Serial.print("Received: '");
        char lagalaga[packetSize];
        int i = 0;

        while(LoRa.available()){
          lagalaga[i] = LoRa.read();

          i++;
        }

        // int instrument = (int)(lagalaga[0] << 24 | lagalaga[1] << 16 | lagalaga[2] << 8 | lagalaga[3]);
        // int  property = (int)(lagalaga[4] << 24 | lagalaga[5] << 16 | lagalaga[6] << 8 | lagalaga[7]);
        // int integer = (int)(lagalaga[8] << 24 | lagalaga[9] << 16 | lagalaga[10] << 8 | lagalaga[11]);
        // int fraction = (int)(lagalaga[12] << 24 | lagalaga[13] << 16 | lagalaga[14] << 8 | lagalaga[15]);

        int8_t instrument = (lagalaga[0]);
        int8_t property = (lagalaga[1]);
        int8_t integer = (lagalaga[2]);
        //TODO fraction must be uint_8 for 1byte fraction packets
        uint8_t fraction = (uint8_t) lagalaga[3];

        Serial.print("INS: ");
        Serial.print(instrument);
        Serial.print(" PROP: ");
        Serial.print( property);
        Serial.print(" INT: ");
        Serial.print(integer);
        Serial.print(" FRAC: ");
        Serial.println(fraction);
        Serial.println("--------------------------------------------");

        // int motor =
    }
}
