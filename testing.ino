#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_3s;
bool leftButtonPressed;
bool rightButtonPressed;
const byte rightButton = 5;
const byte switchPin = 7;
volatile bool intFlag = 0;
volatile bool te = 0;
volatile bool tes = 0;
volatile bool state = 0;
volatile int count = 0;

unsigned long reactionTime;
unsigned long LeftorRight;
bool buttonPressed = false;
bool ledOn = false;

void setup(void) {
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(switchPin), off, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightButton), test, FALLING);
  state = digitalRead(switchPin);
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  //reactionTime = random(2000, 5000); // Generate random reaction time between 2 to 5 seconds
  delay_3s.start(1, AsyncDelay::MILLIS);
  reactionTime = random(2000, 5000);
  LeftorRight = random(1,20);
}
void off() {
  intFlag = 1;
}
void test() {
  te = 1;
}
void loop(void) {
if (intFlag) {
  delay(10);
  state = digitalRead(switchPin);
  intFlag = 0;
}
if (te) {
  delay(10);
  tes = digitalRead(rightButton);
  te = 0;
}

if (state) {
  CircuitPlayground.setPixelColor(2, 0, 0, 0);
  CircuitPlayground.setPixelColor(7, 0, 0, 0);
  CircuitPlayground.setPixelColor(0, 255, 0, 0);
  CircuitPlayground.setPixelColor(9, 255, 0, 0);
  Serial.println("OFF");
}
if (!state) {
  CircuitPlayground.setPixelColor(0, 0, 0, 0);
  CircuitPlayground.setPixelColor(9, 0, 0, 0);
  delay(10);
  LeftorRight = random(1,20);
  reactionTime = random(2000, 5000);
  count = 0;
  if (delay_3s.isExpired()) {
    count++;
  Serial.print("Time:  ");
  Serial.println(reactionTime);
//if (LeftorRight >= 10) { //2 is right
  CircuitPlayground.setPixelColor(0, 0, 255, 0);
  CircuitPlayground.setPixelColor(9, 0, 255, 0);
  delay(100);
  CircuitPlayground.setPixelColor(0, 0, 0, 0);
  CircuitPlayground.setPixelColor(9, 0, 0, 0);
  delay(reactionTime);
  CircuitPlayground.setPixelColor(7, 0, 255, 0);
 // rightButtonPressed = CircuitPlayground.rightButton();
  if (tes) {
  CircuitPlayground.setPixelColor(7, 0, 0, 0);
    unsigned long time = count - reactionTime;
    Serial.print(count);
    Serial.println("  ms");
  }
/* } else if (LeftorRight < 10) { //2 is left
  CircuitPlayground.setPixelColor(2, 0, 255, 0);
  leftButtonPressed = CircuitPlayground.leftButton();
  if (leftButtonPressed) {
  CircuitPlayground.setPixelColor(2, 0, 0, 0);
    unsigned long time = count - reactionTime;
    Serial.print(count);
    Serial.println("  ms");
}
  } */
  delay_3s.repeat();
}

 /* if (digitalRead(buttonPin) == LOW && !buttonPressed) {
    buttonPressed = true;
    unsigned long playerReactionTime = millis() - reactionTime;
    Serial.print("Your reaction time: ");
    Serial.print(playerReactionTime);
    Serial.println(" ms");
    delay(2000);
    reactionTime = random(2000, 5000); // Generate new reaction time for the next round
  } */

 /* if (ledOn && millis() - reactionTime > 1000) {
   // digitalWrite(ledPin, LOW);
    ledOn = false;
    buttonPressed = false;
  } */
}
LeftorRight = random(1,20);
reactionTime = random(2000, 5000);
delay(1000);
}
