#ifndef LORA_H_
#define LORA_H_

#include <LoRa.h>

namespace LoRaSender {

#define NSS 4
#define RST 5
#define DI0 15

    void setupLoRa();
    void send(const int8_t* packet);
    void send(const uint8_t* packet);
}

#endif // LORA_H_
