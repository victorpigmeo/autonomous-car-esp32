#include "lora.h"

namespace LoRaSender{

    void setupLoRa(){
        Serial.println("===================================");

        LoRa.setPins(NSS, RST, DI0);

        if(!LoRa.begin(433E6)){
            Serial.print("LORA FAILED TO INITIALIZE");
            while(1);
        }

        LoRa.setSyncWord(0xFA);

        Serial.println("LoRa Initialized");
        Serial.println("===================================");
    }

    void send(const int8_t* packet){
        LoRa.beginPacket();

        for(int i = 0; i < sizeof(packet); i++){
            LoRa.write(packet[i]);
        }

        LoRa.endPacket();
    }

    void send(const uint8_t* packet){
        LoRa.beginPacket();

        for(int i = 0; i < sizeof(packet); i++){
            LoRa.write(packet[i]);
        }

        LoRa.endPacket();
    }
}
