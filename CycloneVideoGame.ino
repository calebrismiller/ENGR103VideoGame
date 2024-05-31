#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_1s;

float midi[127];
int A_four = 440;

int time;
int runner = 0;
int level;

long goal;
long winLED;
long winTone;

const int switchPin = 7;
const int leftButtonPin = 4;
const int rightButtonPin = 5;

volatile bool rightButtonFlag = false;
volatile bool leftButtonFlag = false;
volatile bool switchFlag = false;

bool switchState = HIGH; 

int happySong[4][2] = {
    {55, 200},  
    {55, 200},  
    {57, 100},  
    {60, 300},
};

int sadSong[4][2] = {
    {60, 100},
    {57, 200},
    {55, 200},
    {55, 400},
};

int levelSong[5][2] = {
    {50, 100},
    {52, 100},
    {54, 100},
    {56, 100},
    {58, 100},
};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(rightButtonPin), rightButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(leftButtonPin), leftButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
  switchState = digitalRead(switchPin);
  generateMIDI();
  delay_1s.start(1000, AsyncDelay::MILLIS);
  if (!switchState) {
    time = 100;
    level = map(time, 10, 100, 0, 9);
    CircuitPlayground.setPixelColor(level, 225, 0, 225);
      for(int i = 0; i < sizeof(levelSong) / sizeof(levelSong[0]); i++) {
        CircuitPlayground.playTone(midi[levelSong[i][0]], levelSong[i][1]);
        delay(1);
      }
    delay(1000);
    CircuitPlayground.clearPixels();
    delay(1000);
    goal = random(0, 10);
    CircuitPlayground.setPixelColor(goal, 0, 0, 225);
    delay(1000);
    CircuitPlayground.clearPixels();
  }
}

void switchISR() {
  switchFlag = true;
}

void rightButtonISR() {
  rightButtonFlag = true;
}

void leftButtonISR() {
  leftButtonFlag = true;
}

void loop() {
  if (delay_1s.isExpired() && !switchState) {
    Serial.print(time);
    for (runner = 0; runner < 10; ++runner) {
      if (runner == 10) {
        runner = 0;
      }
      CircuitPlayground.setPixelColor(runner, 255, 255, 255);
      CircuitPlayground.playTone(midi[50], 10);
      delay(time);
      CircuitPlayground.clearPixels();
      if (rightButtonFlag || leftButtonFlag) {
        CircuitPlayground.setPixelColor(runner, 0, 0, 255);
        delay(1000);
        if (runner == goal) {
          for (int i = 0; i < 10; ++i) {
            CircuitPlayground.setPixelColor(i, 0, 255, 0);
          }
          for(int i = 0; i < sizeof(happySong) / sizeof(happySong[0]); i++) {
            CircuitPlayground.playTone(midi[happySong[i][0]], happySong[i][1]);
            delay(1);
          }
          delay(1000);
          time = time-10;
          if (time == 10) {
            if (delay_1s.isExpired() && !switchState) {
            winLED = random(0, 10);
            CircuitPlayground.setPixelColor(winLED, 0, 225, 0);
            delay(10);
            CircuitPlayground.clearPixels();
            winTone = random(50, 60);
            CircuitPlayground.playTone(midi[winTone], 10);
            }
          }
        } else {
          for (int i = 0; i < 10; ++i) {
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          for(int i = 0; i < sizeof(sadSong) / sizeof(sadSong[0]); i++) {
            CircuitPlayground.playTone(midi[sadSong[i][0]], sadSong[i][1]);
            delay(1);
          }
          delay(1000);
          time = 100;
        }
        CircuitPlayground.clearPixels();
        delay(500);
        runner = 0;
        level = map(time, 10, 100, 0, 9);
        CircuitPlayground.setPixelColor(level, 225, 0, 225);
          for(int j = 0; j < sizeof(levelSong) / sizeof(levelSong[0]); j++) {
            CircuitPlayground.playTone(midi[levelSong[j][0]], levelSong[j][1]);
            delay(1);
          }
        delay(100);
        CircuitPlayground.clearPixels();
        delay(1000);
        goal = random(0, 10);
        CircuitPlayground.setPixelColor(goal, 0, 0, 225);
        delay(1000);
        CircuitPlayground.clearPixels();
        rightButtonFlag = false;
        leftButtonFlag = false;
      }
    }
  }

  if (switchFlag) {
    delay(25);
    switchState = digitalRead(switchPin);
    CircuitPlayground.clearPixels();
    if (switchState == HIGH) {
      delay_1s.start(1000, AsyncDelay::MILLIS);
    }
    if (!switchState) {
      time = 100;
      level = map(time, 10, 100, 0, 9);
      CircuitPlayground.setPixelColor(level, 225, 0, 225);
          for(int i = 0; i < sizeof(levelSong) / sizeof(levelSong[0]); i++) {
            CircuitPlayground.playTone(midi[levelSong[i][0]], levelSong[i][1]);
            delay(1);
          }
      delay(1000);
      CircuitPlayground.clearPixels();
      delay(1000);
      goal = random(0, 10);
      CircuitPlayground.setPixelColor(goal, 0, 0, 225);
      delay(1000);
      CircuitPlayground.clearPixels();
    }
    switchFlag = false;
  }
}

void generateMIDI() {
  for (int x = 0; x < 127; ++x) {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}