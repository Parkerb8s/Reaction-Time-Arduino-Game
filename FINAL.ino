#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
const uint8_t spOFF[]           PROGMEM = {0x6B,0x4A,0xE2,0xBA,0x8D,0xBC,0xED,0x66,0xD7,0xBB,0x9E,0xC3,0x98,0x93,0xB9,0x18,0xB2,0xDE,0x7D,0x73,0x67,0x88,0xDD,0xC5,0xF6,0x59,0x15,0x55,0x44,0x56,0x71,0x6B,0x06,0x74,0x53,0xA6,0x01,0x0D,0x68,0x80,0x03,0x1C,0xF8,0x7F};
const uint8_t spGO[]            PROGMEM = {0x06,0x08,0xDA,0x75,0xB5,0x8D,0x87,0x4B,0x4B,0xBA,0x5B,0xDD,0xE2,0xE4,0x49,0x4E,0xA6,0x73,0xBE,0x9B,0xEF,0x62,0x37,0xBB,0x9B,0x4B,0xDB,0x82,0x1A,0x5F,0xC1,0x7C,0x79,0xF7,0xA7,0xBF,0xFE,0x1F};

const byte buttonPin = 5;
const byte buttonPin1 = 4;
const byte switchPin = 7;
volatile bool state = 0;
volatile bool intFlag = 0;
unsigned long timeDelay;
unsigned long LeftorRight;
float Time;

void setup() {
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(switchPin), off, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), rightPress, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin1), leftPress, RISING);
  state = digitalRead(switchPin);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  timeDelay = random(2000, 8000);
  LeftorRight = random(1,20);
}
void rightPress() {
if (LeftorRight >= 10) {
  if (!state) {
  CircuitPlayground.clearPixels();
  Time = millis()-Time;
  if (Time <= 1500.00) {
  Serial.print("You pressed the right button after ");
  Serial.print(Time/1000,3);
  Serial.println(" seconds");
  }
} else if (state) {
  CircuitPlayground.playTone(60, 100);
}
} else {
  CircuitPlayground.playTone(60, 100);
}
}
void leftPress() {
if (LeftorRight < 10) {
  if (!state) {
  CircuitPlayground.clearPixels();
  Time = millis()-Time;
  if (Time <= 1500.00) {
  Serial.print("You pressed the left button after ");
  Serial.print(Time/1000,3);
  Serial.println(" seconds");
  }
} else if (state) {
  CircuitPlayground.playTone(60, 100);
}
} else {
  CircuitPlayground.playTone(60, 100);
}
}
void off() {
  intFlag = 1;
}
void loop() {
if (intFlag) {
  delay(10);
  state = digitalRead(switchPin);
  intFlag = 0;
}
if (state) {
  CircuitPlayground.setPixelColor(2, 0, 0, 0);
  CircuitPlayground.setPixelColor(7, 0, 0, 0);
  CircuitPlayground.setPixelColor(0, 255, 0, 0);
  CircuitPlayground.setPixelColor(9, 255, 0, 0);
  Serial.println("OFF");
}
if (!state) {
  CircuitPlayground.setPixelColor(2, 0, 0, 0);
  CircuitPlayground.setPixelColor(7, 0, 0, 0);
  CircuitPlayground.setPixelColor(0, 0, 0, 0);
  CircuitPlayground.setPixelColor(9, 0, 0, 0);
  timeDelay = random(2000, 8000);
  delay(timeDelay);
  Time = millis();
  LeftorRight = random(1,20); //creates new random value to decide between right or left led
  if (LeftorRight >= 10) {
  //Serial.println("GO");
  CircuitPlayground.setPixelColor(7, 0, 255, 0); //right led
	CircuitPlayground.speaker.say(spGO);
  CircuitPlayground.speaker.set(255);
  delay(100); //how long led stays on
  } else if (LeftorRight < 10) {
    CircuitPlayground.setPixelColor(2, 0, 255, 0); //left led
  	CircuitPlayground.speaker.say(spGO);
    CircuitPlayground.speaker.set(255);
    //Serial.println("GO");
    delay(100); //how long led stays on
  }
}
delay(1000);
}
