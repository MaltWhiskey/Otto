#ifndef SOUNDDATA_H
#define SOUNDDATA_H
#include <stdint.h>

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

struct sound_t {
  uint16_t note;
  int16_t duration;
};

struct sound_dsc_t {
  const uint16_t data_size;
  const sound_t* data;
  const uint16_t note;
  const char name[32];
};

const sound_dsc_t none_dsc = {0, 0, 0, "None"};
const sound_t cantina[] = {
    NOTE_B4,  -4, NOTE_E5,  -4, NOTE_B4,  -4, NOTE_E5,  -4, NOTE_B4, 8,
    NOTE_E5,  -4, NOTE_B4,  8,  REST,     8,  NOTE_AS4, 8,  NOTE_B4, 8,
    NOTE_B4,  8,  NOTE_AS4, 8,  NOTE_B4,  8,  NOTE_A4,  8,  REST,    8,
    NOTE_GS4, 8,  NOTE_A4,  8,  NOTE_G4,  8,  NOTE_G4,  4,  NOTE_E4, -2,
    NOTE_B4,  -4, NOTE_E5,  -4, NOTE_B4,  -4, NOTE_E5,  -4, NOTE_B4, 8,
    NOTE_E5,  -4, NOTE_B4,  8,  REST,     8,  NOTE_AS4, 8,  NOTE_B4, 8,

    NOTE_A4,  -4, NOTE_A4,  -4, NOTE_GS4, 8,  NOTE_A4,  -4, NOTE_D5, 8,
    NOTE_C5,  -4, NOTE_B4,  -4, NOTE_A4,  -4, NOTE_B4,  -4, NOTE_E5, -4,
    NOTE_B4,  -4, NOTE_E5,  -4, NOTE_B4,  8,  NOTE_E5,  -4, NOTE_B4, 8,
    REST,     8,  NOTE_AS4, 8,  NOTE_B4,  8,  NOTE_D5,  4,  NOTE_D5, -4,
    NOTE_B4,  8,  NOTE_A4,  -4, NOTE_G4,  -4, NOTE_E4,  -2, NOTE_E4, 2,
    NOTE_G4,  2,  NOTE_B4,  2,  NOTE_D5,  2,

    NOTE_F5,  -4, NOTE_E5,  -4, NOTE_AS4, 8,  NOTE_AS4, 8,  NOTE_B4, 4,
    NOTE_G4,  4};

const sound_dsc_t cantina_dsc = {sizeof(cantina) / sizeof(sound_t), cantina,
                                 857, "Cantina"};

const sound_t hedwig[] = {
    REST,     2,  NOTE_D4,  4, NOTE_G4,  -4, NOTE_AS4, 8,  NOTE_A4,  4,
    NOTE_G4,  2,  NOTE_D5,  4, NOTE_C5,  -2, NOTE_A4,  -2, NOTE_G4,  -4,
    NOTE_AS4, 8,  NOTE_A4,  4, NOTE_F4,  2,  NOTE_GS4, 4,  NOTE_D4,  -1,
    NOTE_D4,  4,

    NOTE_G4,  -4, NOTE_AS4, 8, NOTE_A4,  4,  NOTE_G4,  2,  NOTE_D5,  4,
    NOTE_F5,  2,  NOTE_E5,  4, NOTE_DS5, 2,  NOTE_B4,  4,  NOTE_DS5, -4,
    NOTE_D5,  8,  NOTE_CS5, 4, NOTE_CS4, 2,  NOTE_B4,  4,  NOTE_G4,  -1,
    NOTE_AS4, 4,

    NOTE_D5,  2,  NOTE_AS4, 4, NOTE_D5,  2,  NOTE_AS4, 4,  NOTE_DS5, 2,
    NOTE_D5,  4,  NOTE_CS5, 2, NOTE_A4,  4,  NOTE_AS4, -4, NOTE_D5,  8,
    NOTE_CS5, 4,  NOTE_CS4, 2, NOTE_D4,  4,  NOTE_D5,  -1, REST,     4,
    NOTE_AS4, 4,

    NOTE_D5,  2,  NOTE_AS4, 4, NOTE_D5,  2,  NOTE_AS4, 4,  NOTE_F5,  2,
    NOTE_E5,  4,  NOTE_DS5, 2, NOTE_B4,  4,  NOTE_DS5, -4, NOTE_D5,  8,
    NOTE_CS5, 4,  NOTE_CS4, 2, NOTE_AS4, 4,  NOTE_G4,  -1};

const sound_dsc_t hedwig_dsc = {sizeof(hedwig) / sizeof(sound_t), hedwig, 1667,
                                "Hedwig"};

const sound_t startrek[] = {
    NOTE_D4, -8,  NOTE_G4, 16,  NOTE_C5, -4,  NOTE_B4, 8,
    NOTE_G4, -16, NOTE_E4, -16, NOTE_A4, -16, NOTE_D5, 2,
};

const sound_dsc_t startrek_dsc = {sizeof(startrek) / sizeof(sound_t), startrek,
                                  3000, "Startrek"};

const sound_t pacman[] = {
    NOTE_B4,  16,  NOTE_B5,  16, NOTE_FS5, 16,  NOTE_DS5, 16, NOTE_B5,  32,
    NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_C5,  16,  NOTE_C6,  16, NOTE_G6,  16,
    NOTE_E6,  16,  NOTE_C6,  32, NOTE_G6,  -16, NOTE_E6,  8,

    NOTE_B4,  16,  NOTE_B5,  16, NOTE_FS5, 16,  NOTE_DS5, 16, NOTE_B5,  32,
    NOTE_FS5, -16, NOTE_DS5, 8,  NOTE_DS5, 32,  NOTE_E5,  32, NOTE_F5,  32,
    NOTE_F5,  32,  NOTE_FS5, 32, NOTE_G5,  32,  NOTE_G5,  32, NOTE_GS5, 32,
    NOTE_A5,  16,  NOTE_B5,  8};

const sound_dsc_t pacman_dsc = {sizeof(pacman) / sizeof(sound_t), pacman, 2286,
                                "Pacman"};

const sound_t tetris[] = {
    NOTE_E5,  4,  NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5,  8, NOTE_B4, 8,
    NOTE_A4,  4,  NOTE_A4, 8, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5,  8, NOTE_C5, 8,
    NOTE_B4,  -4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4, NOTE_C5,  4, NOTE_A4, 4,
    NOTE_A4,  8,  NOTE_A4, 4, NOTE_B4, 8, NOTE_C5, 8,

    NOTE_D5,  -4, NOTE_F5, 8, NOTE_A5, 4, NOTE_G5, 8, NOTE_F5,  8, NOTE_E5, -4,
    NOTE_C5,  8,  NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4,  4, NOTE_B4, 8,
    NOTE_C5,  8,  NOTE_D5, 4, NOTE_E5, 4, NOTE_C5, 4, NOTE_A4,  4, NOTE_A4, 4,
    REST,     4,

    NOTE_E5,  4,  NOTE_B4, 8, NOTE_C5, 8, NOTE_D5, 4, NOTE_C5,  8, NOTE_B4, 8,
    NOTE_A4,  4,  NOTE_A4, 8, NOTE_C5, 8, NOTE_E5, 4, NOTE_D5,  8, NOTE_C5, 8,
    NOTE_B4,  -4, NOTE_C5, 8, NOTE_D5, 4, NOTE_E5, 4, NOTE_C5,  4, NOTE_A4, 4,
    NOTE_A4,  8,  NOTE_A4, 4, NOTE_B4, 8, NOTE_C5, 8,

    NOTE_D5,  -4, NOTE_F5, 8, NOTE_A5, 4, NOTE_G5, 8, NOTE_F5,  8, NOTE_E5, -4,
    NOTE_C5,  8,  NOTE_E5, 4, NOTE_D5, 8, NOTE_C5, 8, NOTE_B4,  4, NOTE_B4, 8,
    NOTE_C5,  8,  NOTE_D5, 4, NOTE_E5, 4, NOTE_C5, 4, NOTE_A4,  4, NOTE_A4, 4,
    REST,     4,

    NOTE_E5,  2,  NOTE_C5, 2, NOTE_D5, 2, NOTE_B4, 2, NOTE_C5,  2, NOTE_A4, 2,
    NOTE_GS4, 2,  NOTE_B4, 4, REST,    8, NOTE_E5, 2, NOTE_C5,  2, NOTE_D5, 2,
    NOTE_B4,  2,  NOTE_C5, 4, NOTE_E5, 4, NOTE_A5, 2, NOTE_GS5, 2};
const sound_dsc_t tetris_dsc = {sizeof(tetris) / sizeof(sound_t), tetris, 1667,
                                "Tetris"};

const sound_t coffin[] = {
    NOTE_G5,  4, NOTE_G5,  4, NOTE_G5,  4, NOTE_G5,  4, NOTE_C5,  4,
    NOTE_AS4, 4, NOTE_A4,  4, NOTE_F4,  4, NOTE_G4,  4, REST,     4,
    NOTE_G4,  4, NOTE_D5,  4, NOTE_C5,  4, REST,     4, NOTE_AS4, 4,
    REST,     4, NOTE_A4,  4, REST,     4, NOTE_A4,  4, NOTE_A4,  4,
    NOTE_C5,  4, REST,     4, NOTE_AS4, 4, NOTE_A4,  4, NOTE_G4,  4,
    REST,     4, NOTE_G4,  4, NOTE_AS5, 4, NOTE_A5,  4, NOTE_AS5, 4,
    NOTE_A5,  4, NOTE_AS5, 4, NOTE_G4,  4, REST,     4, NOTE_G4,  4,
    NOTE_AS5, 4, NOTE_A5,  4, NOTE_AS5, 4, NOTE_A5,  4, NOTE_AS5, 4,
    NOTE_G4,  4, REST,     4, NOTE_G4,  4, NOTE_D5,  4, NOTE_C5,  4,
    REST,     4, NOTE_AS4, 4, REST,     4, NOTE_A4,  4, REST,     4,
    NOTE_A4,  4, NOTE_A4,  4, NOTE_C5,  4, REST,     4, NOTE_AS4, 4,
    NOTE_A4,  4, NOTE_G4,  4, REST,     4, NOTE_G4,  4, NOTE_AS5, 4,
    NOTE_A5,  4, NOTE_AS5, 4, NOTE_A5,  4, NOTE_AS5, 4, NOTE_G4,  4,
    REST,     4, NOTE_G4,  4, NOTE_AS5, 4, NOTE_A5,  4, NOTE_AS5, 4,
    NOTE_A5,  4, NOTE_AS5, 4};
const sound_dsc_t coffin_dsc = {sizeof(coffin) / sizeof(sound_t), coffin, 750,
                                "Coffin Dance"};

const sound_t knight[] = {
    NOTE_A4, 8, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4,
    16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16,
    NOTE_GS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 8, NOTE_AS4,
    16, NOTE_A4, 16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16,
    NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_GS4, 16, NOTE_A4,
    16, NOTE_A4, 16, NOTE_A4, 16, NOTE_G4, 8, NOTE_GS4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4,
    16, NOTE_G4, 16, NOTE_G4, 16, NOTE_FS4, 16, NOTE_G4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_G4, 8, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4,
    16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_FS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_G4, 16,
    // 2
    NOTE_A4, 8, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4,
    16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16,
    NOTE_GS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 8, NOTE_AS4,
    16, NOTE_A4, 16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16,
    NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_GS4, 16, NOTE_A4,
    16, NOTE_A4, 16, NOTE_A4, 16, NOTE_G4, 8, NOTE_GS4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4,
    16, NOTE_G4, 16, NOTE_G4, 16, NOTE_FS4, 16, NOTE_G4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_G4, 8, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4,
    16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_FS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_G4, 16,
    // 3
    NOTE_A4, 8, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4,
    16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16,
    NOTE_GS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 8, NOTE_AS4,
    16, NOTE_A4, 16, NOTE_A4, 16, NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16,
    NOTE_AS4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_A4, 16, NOTE_GS4, 16, NOTE_A4,
    16, NOTE_A4, 16, NOTE_A4, 16, NOTE_G4, 8, NOTE_GS4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4,
    16, NOTE_G4, 16, NOTE_G4, 16, NOTE_FS4, 16, NOTE_G4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_G4, 8, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4,
    16, NOTE_G4, 16, NOTE_G4, 16, NOTE_GS4, 16, NOTE_G4, 16, NOTE_G4, 16,
    NOTE_G4, 16, NOTE_FS4, 16, NOTE_G4, 16, NOTE_G4, 16, NOTE_G4, 16,
    // solo
    NOTE_A4, 8, NOTE_AS4, 16, NOTE_A4, 16, NOTE_E5, -2, NOTE_A5, 8, NOTE_AS5,
    16, NOTE_A5, 16, NOTE_E5, -2, NOTE_A4, 8, NOTE_AS4, 16, NOTE_A4, 16,
    NOTE_E5, 8, NOTE_A5, 8, NOTE_G5, 1, NOTE_A4, 8, NOTE_AS4, 16, NOTE_A4, 16,
    NOTE_E5, -2, NOTE_A5, 8, NOTE_AS5, 16, NOTE_A5, 16, NOTE_E5, -2, NOTE_A4, 8,
    NOTE_AS4, 16, NOTE_A4, 16, NOTE_E5, 8, NOTE_A5, 8, NOTE_AS5, -1, NOTE_G5, 8,
    NOTE_A5, 4};

const sound_dsc_t knight_dsc = {sizeof(knight) / sizeof(sound_t), knight, 2000,
                                "Knight Rider"};

#endif
