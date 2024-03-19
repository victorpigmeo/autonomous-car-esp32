# Notes

## Latitude 
90 degrees to north and south (-90 to 90)

## Longitude
180 degrees to east and west (-180 to 180)

## LoRa
gotta use LoRa.write to send bytes. LoRa.print can be used only with strings

## Protocolo "MIDI" de pobre (poor's midi protocol)
Pacote:

{INSTRUMENT_CODE, PROPERTY, INT_VALUE, FLOAT_POINT}

## Sender implementation
### Discord notes (Thanks @leniac_dev)
1 - gps (1 byte)
1 - lat (1 byte)
-38 - inteiro (2 bytes)
79879879 - float (4 bytes)

toBytes on struct

int16tobyte

int32tobyte

2 - gyro (1 byte)
1 - inst_axis (1 byte)
-9 - inteiro (1 byte)
78 - float (1 byte)

we see the first byte on the receiver and reads accordingly

## Instrument Definition
### GPS 
> INSTRUMENT_CODE: 1

| PROPERTY | DESCRIPTION |
| --- | --- |
| 1 | LATITUDE |
| 2 | LONGITUDE |
| 3 | SPEED |
| 4 | ALTITUDE |

### MPU6050
> INSTRUMENT_CODE: 2

| PROPERTY | DESCRIPTION |
| --- | --- |
| 1 | GYRO_X |
| 2 | GYRO_Y |
| 3 | GYRO_Z |
| 4 | ACEL_X |
| 5 | ACEL_Y |
| 6 | ACEL_Z |
| 7 | TEMP |

### MOTOR
> INSTRUMENT_CODE: 3 (ZERO_FILL on FLOAT_POINT)

| PROPERTY | DESCRIPTION |
| --- | --- |
| 1 | FRONT |
| 2 | BACK |
| 3 | LEFT |
| 4 | RIGHT |

| VALUE | DESCRIPTION |
| --- | --- |
| 1 | ON |
| 2 | OFF | 

## PinOut
### Sender
MPU6050 (Gyroscope, accelerometer, temperature)

| Instrument Pin | ESP32 Pin |
| --- | --- |
| 3.3v | 3.3v |
| GND | GND |
| SCL | GPIO22 |
| SDA | GPIO21 |

SX1278 (LoRa)

| Instrument Pin | ESP32 Pin |
| --- | --- |
| 3V3 | 3.3v |
| GND | GND |
| MISO | GPIO19 |
| MOSI | GPIO23 |
| SCK | GPIO18 |
| RST | GPIO5 |
| NSS | GPIO4 |
| DI00 | GPIO15 |

UBlox NEO 6M (GPS)

| Instrument Pin | ESP32 Pin |
| --- | --- |
| VCC | 5v (External) |
| GND | GND (External) |
| RX | TX2 |
| TX | RX2 |

L298N (H-Bridge)

> Need to remove the jumper (keep it if power with 12v) no need to connect to 5V if power with 12V

| Instrument Pin | ESP32 Pin | Description | 
| --- | --- | --- |
| 5V | 5V | External power supply |
| GND | GND | External power supply |
| 12V | 5V | Connect to 5V borne | 
| IN1 | 26 | FRONT |
| IN2 | 25 | BACK |
| IN3 | 33 | LEFT |
| IN4 | 32 | RIGHT |

### Receiver
SX1278 (LoRa)

| Instrument Pin | ESP32 Pin |
| --- | --- |
| 3V3 | 3.3v |
| GND | GND |
| MISO | GPIO19 |
| MOSI | GPIO23 |
| SCK | GPIO18 |
| RST | GPIO5 |
| NSS | GPIO4 |
| DI00 | GPIO22 |
