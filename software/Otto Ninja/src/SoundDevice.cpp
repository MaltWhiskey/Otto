
#include "SoundDevice.h"

#include <ESP32Tone.h>
#include <stdint.h>
#include <toneAC.h>

#include "SoundData.h"
#include "tos_intercom.h"

const sound_dsc_t SoundDevice::songs[] = {cantina_dsc,  hedwig_dsc, pacman_dsc,
                                          startrek_dsc, tetris_dsc, coffin_dsc,
                                          knight_dsc};

SoundDevice::SoundDevice() {
  //  pinMode(25, OUTPUT);
  //  pinMode(26, OUTPUT);
}

void SoundDevice::loop() {
  static long wait_ms2 = 0;
  if (wait_ms != 0 && millis() >= wait_ms2) {
    wait_ms2 = 0;
    noToneAC();
  }
  if (songnr >= 0 && offset >= 0 && millis() >= wait_ms) {
    const sound_t* song = songs[songnr].data;
    uint16_t size = songs[songnr].data_size;
    float note_duration = songs[songnr].note;

    if (offset < size) {
      note_duration /= song[offset].duration;
      if (note_duration < 0) {
        note_duration *= -1.5f;
      }
      wait_ms = millis() + (note_duration * 1.0f);
      wait_ms2 = millis() + (note_duration * 0.9f);
      toneAC(song[offset++].note, 10, note_duration * 1.0f, true);
    } else {
      offset = -1;
    }
  }
}

sound_dsc_t SoundDevice::get_song() {
  if (offset >= 0 && songnr >= 0) {
    return songs[songnr];
  }
  return none_dsc;
}

void SoundDevice::play_song() {
  offset = 0;
  wait_ms = 0;
}

void SoundDevice::next_song() {
  if (songnr + 1 < sizeof(songs) / sizeof(sound_dsc_t))
    songnr++;
  else
    songnr = 0;
}

void SoundDevice::prev_song() {
  if (songnr > 0)
    songnr--;
  else
    songnr = sizeof(songs) / sizeof(sound_dsc_t);
}

void SoundDevice::play_sound(uint8_t song) {}
void SoundDevice::play_wave(uint8_t nr) {
  wavAC(tos_intercom_wav, tos_intercom_wav_len, RESONANT_FREQ, RATE_8KHZ, true);
}
void SoundDevice::tone(uint16_t t) { toneAC(t, 10, 1000, false); }
