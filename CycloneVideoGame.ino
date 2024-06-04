#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_1s; // This is a 1 second timer that will be used later on in the code to read the switch.

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

int happySong[4][2] = { // this song will be used if the particle is stopped in the correct position.
    {55, 200},  
    {55, 200},  
    {57, 100},  
    {60, 300},
};

int sadSong[4][2] = { // this song will be used if the particle is stopped in the incorrect position.
    {60, 100},
    {57, 200},
    {55, 200},
    {55, 400},
};

int levelSong[5][2] = { // this song will be played when the level is displayed on the LEDs.
    {50, 100},
    {52, 100},
    {54, 100},
    {56, 100},
    {58, 100},
};

void setup() {
  Serial.begin(9600); // just in case we need to access it later to troubleshoot anything.
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(rightButtonPin), rightButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(leftButtonPin), leftButtonISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
  switchState = digitalRead(switchPin); // start out by first reading the switchstate so that if it is activated, the game will not start.
  generateMIDI(); // this function was copied from a previous code, it is used to generate a MIDI soundbite for my playTone functions.
  delay_1s.start(1000, AsyncDelay::MILLIS);
  if (!switchState) { // Once the switch is flipped, the game will begin.
    time = 100;
    level = map(time, 10, 100, 0, 9); // this is how we will display the level, the map will set the time to coordinate with the 10 pixels.
    CircuitPlayground.setPixelColor(level, 225, 0, 225); // show the level on the LEDs
      for(int i = 0; i < sizeof(levelSong) / sizeof(levelSong[0]); i++) {
        CircuitPlayground.playTone(midi[levelSong[i][0]], levelSong[i][1]);
        delay(1);
      }
    delay(1000);
    CircuitPlayground.clearPixels();
    delay(1000);
    goal = random(0, 10); // set a goal on a random pixel
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
  if (delay_1s.isExpired() && !switchState) { // once again checking the timer and switchstate to run the game
    Serial.print(time); // NOT NECESSARY, JUST HELPFUL FOR TROUBLESHOOTING.
    for (runner = 0; runner < 10; ++runner) {  // the runner, or the particle, will so around the CPX board in coordination with our time int.
      if (runner == 10) { // if the runner ends up equalling 10 somehow, this will reset it.
        runner = 0;
      }
      CircuitPlayground.setPixelColor(runner, 255, 255, 255);
      CircuitPlayground.playTone(midi[50], 10); // play a tone with everytime an LED lights up.
      delay(time); // MOST IMPORTANT, the speed of delay will effect the difficulty of the game, or, as int time approaches 0, the particle will move faster.
      CircuitPlayground.clearPixels();
      if (rightButtonFlag || leftButtonFlag) { // if either button is pushed, this function will run.
        CircuitPlayground.setPixelColor(runner, 0, 0, 255); // will stop the particle where it was when the button was pushed and turn it blue.
        delay(1000);
        if (runner == goal) { // this will run if the spot where the runner was when the button was pushed matches with the goal.
          for (int i = 0; i < 10; ++i) {
            CircuitPlayground.setPixelColor(i, 0, 255, 0); // light up CPX board green.
          }
          for(int i = 0; i < sizeof(happySong) / sizeof(happySong[0]); i++) {
            CircuitPlayground.playTone(midi[happySong[i][0]], happySong[i][1]);
            delay(1);
          }
          delay(1000);
          time = time-10; // decreases time increment, or speeds up the speed of the particle, and also increasing the level by 1.
          if (time == 10) { // this is what will run if the player wins the game, and gets to time = 10.
            if (delay_1s.isExpired() && !switchState) { // check the timer and switchstate
            winLED = random(0, 10);
            CircuitPlayground.setPixelColor(winLED, 0, 225, 0); // light up random LEDs in green
            delay(10);
            CircuitPlayground.clearPixels();
            winTone = random(50, 60);
            CircuitPlayground.playTone(midi[winTone], 10); // play random MIDIs
            }
          }
        } else { // this will run if the spot where the runner was when the button was pushed does not match with the goal.
          for (int i = 0; i < 10; ++i) {
            CircuitPlayground.setPixelColor(i, 255, 0, 0); // light up CPX board red.
          }
          for(int i = 0; i < sizeof(sadSong) / sizeof(sadSong[0]); i++) {
            CircuitPlayground.playTone(midi[sadSong[i][0]], sadSong[i][1]);
            delay(1);
          }
          delay(1000);
          time = 100; // resets the time increment, also reseting the level to level 1.
        }
        CircuitPlayground.clearPixels();
        delay(500);
        runner = 0; // reset the runner to be equal to 0 so it restarts in the same spot.
        level = map(time, 10, 100, 0, 9);
        CircuitPlayground.setPixelColor(level, 225, 0, 225); // display the current level to the LEDs using the map function.
          for(int j = 0; j < sizeof(levelSong) / sizeof(levelSong[0]); j++) {
            CircuitPlayground.playTone(midi[levelSong[j][0]], levelSong[j][1]);
            delay(1);
          }
        delay(100);
        CircuitPlayground.clearPixels();
        delay(1000);
        goal = random(0, 10);
        CircuitPlayground.setPixelColor(goal, 0, 0, 225); // set a goal on a random pixel
        delay(1000);
        CircuitPlayground.clearPixels();
        rightButtonFlag = false;
        leftButtonFlag = false;
      }
    }
  }

  if (switchFlag) { // this will run if the switch is activated.
    delay(25);
    switchState = digitalRead(switchPin);
    CircuitPlayground.clearPixels();
    if (switchState == HIGH) { // if the switch is read to be off, this function will run until it isn't
      delay_1s.start(1000, AsyncDelay::MILLIS);
    }
    if (!switchState) { // if the switch is turned back on after being off.
      time = 100; // reset the time and the level to the easiest ones.
      level = map(time, 10, 100, 0, 9);
      CircuitPlayground.setPixelColor(level, 225, 0, 225); // display the current level to the LEDs using the map function.
          for(int i = 0; i < sizeof(levelSong) / sizeof(levelSong[0]); i++) {
            CircuitPlayground.playTone(midi[levelSong[i][0]], levelSong[i][1]);
            delay(1);
          }
      delay(1000);
      CircuitPlayground.clearPixels();
      delay(1000);
      goal = random(0, 10);
      CircuitPlayground.setPixelColor(goal, 0, 0, 225); // set a goal on a random pixel
      delay(1000);
      CircuitPlayground.clearPixels();
    }
    switchFlag = false;
  }
}

void generateMIDI() { // this function generates a MIDI value for the playTone functions.
  for (int x = 0; x < 127; ++x) {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}