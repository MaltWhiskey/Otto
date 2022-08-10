#include "main.h"

#include <ArduinoOTA.h>
#include <ESP32Servo.h>
#include <ESPmDNS.h>
#include <Ps3Controller.h>
#include <WiFi.h>
#include <string.h>
//********************************************************
// Calibrate R leg to 120 than attach servo horn
// Calibrate L leg to 60 than attach servo horn
//
// Roll position for R leg is 120 moving towards 0
// Roll position for L leg is 60 moving towards 180
//********************************************************
void startSerial();
void startWiFi();
void startOTA();
void startMDNS();
void startRemote();
void startPeripherals();

// OTTO anatomy
Servo LFoot;
Servo LLeg;
Servo RFoot;
Servo RLeg;
// OTTO Peripherals
const uint8_t trigPin = 17;
const uint8_t echoPin = 26;
const uint8_t buzzPin = 13;
const uint8_t pushPin = 16;
const uint8_t LFPin = 33;
const uint8_t LLPin = 14;
const uint8_t RFPin = 27;
const uint8_t RLPin = 32;

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
  pinMode(trigPin, OUTPUT);
  // Sets echo as an INPUT from HC-SR04
  pinMode(echoPin, INPUT);
  // Set signal as OUTPUT to buzzer
  pinMode(buzzPin, OUTPUT);
  // Set signal as INPUT from button. GND is connected, and will
  // override input pullup when pushed. Don't need VCC (IO15)
  pinMode(pushPin, INPUT_PULLUP);
}

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

void setup() {
  startSerial();
  startWiFi();
  startOTA();
  startMDNS();
  startPeripherals();
  startRemote();
}

void startSerial() {
  Serial.begin(115200);
  Serial.println("ESP Serial ready");
}

void startWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(Config.network.wifi.ssid, Config.network.wifi.password);
  Serial.println("Connecting to Wifi");
  uint16_t retries = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    if (retries++ >= 20) {
      Serial.println();
      Serial.println("Unable to connect to Wifi. Rebooting the ESP..");
      Serial.flush();
      ESP.restart();
    }
    delay(500);
  }
  // Functions below may or may not work
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  // Alternatively implement event handler on disconnect
  WiFi.onEvent([](WiFiEvent_t event) {
    if (event == WiFiEvent_t::SYSTEM_EVENT_ETH_DISCONNECTED) {
      Serial.println("Disconnected from Wi-Fi, trying to reconnect...");
      WiFi.disconnect();
      startWiFi();
    }
  });
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(Config.network.wifi.ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("ESP WiFi ready");
}

void startOTA() {
  ArduinoOTA.setPort(Config.network.server.ota_port);
  ArduinoOTA.setHostname(Config.network.server.hostname);
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else
      type = "filesystem";
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() { Serial.println("\nEnd"); });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("ESP OTA ready");
}

void startMDNS() {
  MDNS.begin(Config.network.server.hostname);
  Serial.printf("ESP mDNS responder %s.local ready\n",
                Config.network.server.hostname);
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
      delay(300);
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

void makeSound() {
  static bool soundMode = true;
  uint32_t distance = getDistance();
  if (digitalRead(pushPin) == LOW) {
    soundMode = !soundMode;
  }

  if (soundMode) {
    if ((distance >= 02) && (distance < 07)) tone(buzzPin, NOTE_C5);
    if ((distance >= 07) && (distance < 12)) tone(buzzPin, NOTE_D5);
    if ((distance >= 12) && (distance < 17)) tone(buzzPin, NOTE_E5);
    if ((distance >= 17) && (distance < 22)) tone(buzzPin, NOTE_F5);
    if ((distance >= 22) && (distance < 27)) tone(buzzPin, NOTE_G5);
    if ((distance >= 27) && (distance < 32)) tone(buzzPin, NOTE_A5);
    if ((distance >= 32) && (distance < 37)) tone(buzzPin, NOTE_B5);
    if ((distance >= 37) && (distance < 42)) tone(buzzPin, NOTE_C6);
  } else {
    noTone(buzzPin);
  }
}

void loop() {
  ArduinoOTA.handle();
  makeSound();
}