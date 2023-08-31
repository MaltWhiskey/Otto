#include "main.h"

#include <Adafruit_LEDBackpack.h>
#include <ArduinoOTA.h>
#include <ESP32Servo.h>
#include <ESPmDNS.h>
#include <Ps3Controller.h>
#include <WiFi.h>
#include <Wire.h>
#include <math.h>
#include <string.h>

#include "SoundDevice.h"
//********************************************************
// Calibrate R leg to 120 than attach servo horn
// Calibrate L leg to 60 than attach servo horn
//
// Roll position for R leg is 120 moving towards 0
// Roll position for L leg is 60 moving towards 180
//********************************************************
void startSerial();
void startRemote();
void startPeripherals();

// OTTO anatomy
Servo LFoot;
Servo LLeg;
Servo RFoot;
Servo RLeg;

SoundDevice sounddev;
Adafruit_8x16matrix matrix = Adafruit_8x16matrix();

void moveLFoot(uint8_t angle) {
  if (!LFoot.attached()) LFoot.attach(LFPin, 544, 2400);
  LFoot.write(angle);
}
void moveLLeg(uint8_t angle) {
  if (!LLeg.attached()) LLeg.attach(LLPin, 544, 2400);
  LLeg.write(angle);
}
void moveRFoot(uint8_t angle) {
  if (!RFoot.attached()) RFoot.attach(RFPin, 544, 2400);
  RFoot.write(angle);
}
void moveRLeg(uint8_t angle) {
  if (!RLeg.attached()) RLeg.attach(RLPin, 544, 2400);
  RLeg.write(angle);
}

void startPeripherals() {
  // Sets trigger as an OUTPUT to HC-SR04
  // pinMode(trigPin, OUTPUT);
  // Sets echo as an INPUT from HC-SR04c (voltage divider 10k - 10k)
  // pinMode(echoPin, INPUT);
  // Set signal as OUTPUT to buzzer (connect GND and signal 2 wires!)
  // pinMode(buzzPin, OUTPUT);
  // toneAC uses pin 25 and 26 for differential signal to buzzer
  // Set signal as INPUT from button. (Connect GND and signal 2 wires!)
  pinMode(pushPin, INPUT_PULLUP);
}
/*
uint32_t getDistance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance = Speed of sound wave / 2 (go and back)
  uint32_t distance = duration * 0.034 / 2;
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
*/
void setup() {
  startSerial();
  startPeripherals();
  startRemote();
  matrix.begin(0x70);  // pass in the address
}

void startSerial() {
  Serial.begin(115200);
  Serial.println("ESP Serial ready");
}

void startRemote() {
  static bool walk = false;

  Ps3.attach([]() {
    float x, y, r;
    auto &stick = Ps3.data.analog.stick;
    auto &button = Ps3.event.button_down;
    if (button.l3) {
      LFoot.detach();
      RFoot.detach();
      if (walk) {
        // Put OTTO in rolling mode
        moveLLeg(160);
        moveRLeg(20);
        walk = false;
      } else {
        // Put OTTO in walking mode
        moveLLeg(60);
        moveRLeg(120);
        walk = true;
      }
      delay(1500);
      LLeg.detach();
      RLeg.detach();
    }
    if (button.cross) {
    }
    if (button.square) {
      sounddev.play_wave(0);
    }
    if (button.circle) {
      sounddev.next_song();
      sounddev.play_song();
    }
    // Left = -x. Right = +x. Up = -y. Down = +y. Range -128 to 127
    x = (stick.rx / 128.0f);
    // Flip up and down to correct for y value
    y = (-stick.ry / 128.0f);
    // The stick moves in a unit circle so x^2 + y^2 should be 1 or less
    r = sqrt(x * x + y * y);
    // Check for minimal radius to move
    if (r > 0.2) {
      if (walk) {
      } else {
        LLeg.detach();
        RLeg.detach();
        // Normalize when the radius is more than 1 (not inside a unit circle)
        if (r > 1) {
          x /= r;
          y /= r;
        }
        // Calculate velocities, but clip if over maximum
        float LS = (y + x);
        float RS = (y - x);
        if (LS > 1) LS = 1;
        if (LS < -1) LS = -1;
        if (RS > 1) RS = 1;
        if (RS < -1) RS = -1;
        moveLFoot(90 + 90 * LS);
        moveRFoot(90 - 90 * RS);
      }
    } else {
      // Turn off servos if not moving.
      LFoot.detach();
      RFoot.detach();
    }
  });
  Ps3.attachOnConnect([]() { Serial.println("PS3 Controller Connected"); });
  Ps3.begin("B1:6B:00:B1:E5:00");
}

void matrix_loop();
void knight_rider();
void angry();

void loop() {
  ArduinoOTA.handle();
  if (digitalRead(pushPin) == LOW) {
    // uint32_t distance = getDistance();
    // sounddev.tone(distance);
  } else {
    sounddev.loop();
  }
  // matrix_loop();
  const char *name = sounddev.get_song().name;
  if (String(name).equals("Knight Rider")) {
    knight_rider();
  } else {
    angry();
  }
}

void knight_rider() {
  static uint16_t angle = 0;
  static long wait_ms = 0;
  matrix.clear();
  matrix.setRotation(1);

  if (millis() >= wait_ms) {
    wait_ms = millis() + 30;
    angle = (angle + 1) % 360;
  }
  float f = sin(angle / (2 * PI));  // -1 to 1
  f *= 8;                           // -8 to 8;
  f += 8;                           // 0 to 16;
  if (f > 15) f = 15;
  for (int i = 3; i < 6; i++) {
    matrix.drawPixel(f, i, LED_ON);
  }
  matrix.writeDisplay();
}

void angry() {
  matrix.clear();
  matrix.setRotation(2);
  matrix.drawBitmap(0, 0, angry_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
}

void matrix_loop() {
  matrix.setTextSize(1);
  matrix.setTextWrap(true);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(3);
  for (int8_t x = 0; x >= -70; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("I am a Ninja!");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);

  matrix.clear();
  matrix.drawBitmap(0, 8, full_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawBitmap(0, 0, full_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  matrix.drawBitmap(0, 0, happy_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, eyes_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, sad_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, angry_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, sleep_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, freetful_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, love_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, confused_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, wave_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, magic_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(2000);
  matrix.clear();
  matrix.drawBitmap(0, 0, fail_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  matrix.drawBitmap(0, 0, xx_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(200);
  matrix.clear();
  matrix.drawBitmap(0, 0, XX_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawBitmap(0, 0, logo_bmp, 8, 16, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x = 7; x >= -36; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Otto DIY");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);

  matrix.clear();  // clear display
  matrix.drawPixel(0, 0, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawLine(0, 0, 7, 15, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 16, LED_ON);
  matrix.fillRect(2, 2, 4, 12, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3, 8, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
}
