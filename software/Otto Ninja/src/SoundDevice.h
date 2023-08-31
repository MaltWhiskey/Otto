#ifndef SOUNDDEV_H
#define SOUNDDEV_H
#include <stdint.h>

#include "SoundData.h"

class SoundDevice {
 private:
  int16_t songnr = -1;
  int16_t offset = -1;
  long wait_ms = 0;

 private:
  // Differential signal for buzzer
  static const uint16_t PIN1 = 25;
  static const uint16_t PIN2 = 26;
  static const sound_dsc_t songs[];

 public:
  SoundDevice();
  void loop();
  void tone(uint16_t t);
  void play_song();
  void stop_song();
  void next_song();
  void prev_song();
  void play_sound(uint8_t i);
  void play_wave(uint8_t i);
  sound_dsc_t get_song();
};
#endif