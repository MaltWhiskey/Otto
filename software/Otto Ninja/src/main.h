#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <stdint.h>
/*-----------------------------------------------------------------------------
 * Evil global Config parameters
 *
 * Animation init or draw routines need to apply config parameters to
 * dynamically set runtime parameters. Init only gets called when an animation
 * starts or restarts draw gets called every animation frame so choose wisely
 * where to apply.
 *---------------------------------------------------------------------------*/

static struct {
  struct {
    struct {
      char ssid[32] = "-^..^-";
      char password[64] = "qazwsxedc";
    } wifi;
    struct {
      char hostname[64] = "NINJA";
      uint16_t ota_port = 3232;
    } server;
  } network;
} Config;

extern struct Config config;

// OTTO Peripherals
//const uint8_t trigPin = 17;
//const uint8_t echoPin = 36;
const uint8_t pushPin = 16;
const uint8_t LFPin = 33;
const uint8_t LLPin = 02;
const uint8_t RFPin = 27;
const uint8_t RLPin = 32;
// Differential signal on 25 and 26 for buzzer
// const uint8_t buzzPin = 25;
// const uint8_t buzzPin = 26;

static const uint8_t
    logo_bmp[] = {B01111110, B10000001, B10111001, B10101001,
                  B10111001, B10010001, B10111001, B10010001,
                  B10010001, B10111001, B10010001, B10111001,
                  B10101001, B10111001, B10000001, B01111110},
    happy_bmp[] = {B00000000, B00111100, B00000010, B00000010,
                   B00000010, B00000010, B00111100, B00000000,
                   B00000000, B00111100, B00000010, B00000010,
                   B00000010, B00000010, B00111100, B00000000},
    eyes_bmp[] = {B00000000, B00111100, B01000010, B01001010,
                  B01000010, B01000010, B00111100, B00000000,
                  B00000000, B00111100, B01000010, B01001010,
                  B01000010, B01000010, B00111100, B00000000},
    sad_bmp[] = {B00000000, B00010000, B00010000, B00010000,
                 B00010000, B00010000, B00010000, B00000000,
                 B00000000, B00010000, B00010000, B00010000,
                 B00010000, B00010000, B00010000, B00000000},
    xx_bmp[] = {B00000000, B00100010, B00010100, B00001000,
                B00010100, B00100010, B00000000, B00000000,
                B00000000, B00000000, B00100010, B00010100,
                B00001000, B00010100, B00100010, B00000000},
    XX_bmp[] = {B01000001, B00100010, B00010100, B00001000,
                B00010100, B00100010, B01000001, B00000000,
                B00000000, B01000001, B00100010, B00010100,
                B00001000, B00010100, B00100010, B01000001},
    angry_bmp[] = {B00000000, B00011110, B00111100, B01111000,
                   B01110000, B00100000, B00000000, B00000000,
                   B00000000, B00000000, B00100000, B01110000,
                   B01111000, B00111100, B00011110, B00000000},
    angry2_bmp[] = {B00000000, B00000010, B00000100, B00001000,
                    B00010000, B00100000, B00000000, B00000000,
                    B00000000, B00000000, B00100000, B00010000,
                    B00001000, B00000100, B00000010, B00000000},
    sleep_bmp[] = {B00000000, B00100010, B00110010, B00101010,
                   B00100110, B00100010, B00000000, B00000000,
                   B00000000, B00000000, B00100010, B00110010,
                   B00101010, B00100110, B00100010, B00000000},
    freetful_bmp[] = {B00000000, B00100000, B00010000, B00001000,
                      B00000100, B00000010, B00000000, B00000000,
                      B00000000, B00000000, B00000010, B00000100,
                      B00001000, B00010000, B00100000, B00000000},
    love_bmp[] = {B00000000, B00001100, B00011110, B00111100,
                  B00111100, B00011110, B00001100, B00000000,
                  B00000000, B00001100, B00011110, B00111100,
                  B00111100, B00011110, B00001100, B00000000},
    confused_bmp[] = {B00000000, B01111100, B10000010, B10111010,
                      B10101010, B10001010, B01111000, B00000000,
                      B00000000, B01111100, B10000010, B10111010,
                      B10101010, B10001010, B01111000, B00000000},
    wave_bmp[] = {B00000000, B00100000, B00010000, B00001000,
                  B00010000, B00100000, B00010000, B00000000,
                  B00000000, B00100000, B00010000, B00001000,
                  B00010000, B00100000, B00010000, B00000000},
    magic_bmp[] = {B00000000, B00000000, B01111110, B11111111,
                   B01111110, B00000000, B00000000, B00000000,
                   B00000000, B00000000, B00000000, B01111110,
                   B11111111, B01111110, B00000000, B00000000},
    fail_bmp[] = {B00000000, B00110000, B01111000, B01111000,
                  B01111100, B00111100, B00001000, B00000000,
                  B00000000, B00001000, B00111100, B01111100,
                  B01111000, B01111000, B00110000, B00000000},
    full_bmp[] = {B11111111, B11111111, B11111111, B11111111,
                  B11111111, B11111111, B11111111, B11111111};

#endif