#include <LiquidCrystal.h>
#include "pitches.h"

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// learn to rewrite code with non const static class members
// add speedups, better memory allocation, levelups, OOP for main game logic

class Color {
  const static int LIGHT_TIME = 400;
  const static int SOUND_TIME = 50;
  const static int SOUND_OUT = 9;

  int button;
  bool pressed;
  int light;
  unsigned long onTime;
  int sound;
  int id;

  public: Color(int colorIn, int colorOut, int colorSound) {
    button = colorIn;
    pressed = false;

    light = colorOut;
    onTime = 0;
    sound = colorSound;

    id = colorOut - 10;
  }

  public: void init() {
    pinMode(button, INPUT);
    pinMode(light, OUTPUT);
  }

  public: void tick(bool generating, int (&pressedSequence)[20], int &pressedSequenceItem) {
    if (digitalRead(button) == HIGH && !this->pressed) {
      this->pressed = true;
    } else if (digitalRead(button) == LOW && this->pressed) {
      this->onTime = millis();
      this->pressed = false;
      if (!generating) {
        pressedSequence[pressedSequenceItem] = id;
        pressedSequenceItem++;
      }
      tone(SOUND_OUT, this->sound, SOUND_TIME);
    }
    if (abs(millis() - this->onTime) < LIGHT_TIME) {
      digitalWrite(this->light, HIGH);
    } else {
      digitalWrite(this->light, LOW);
    }
  }

  public: static int playRandom(Color colors[], int colorCount) {
    int selection = random(0, colorCount);
    colors[selection].pressed = true;
    return selection;
  }
};

// red yellow green blue
int colorCount = 0;
Color colors[4] = {Color(A2, 10, NOTE_C4), Color(A3, 11, NOTE_D4), Color(A4, 12, NOTE_E4), Color(A5, 13, NOTE_F4)};

int sequenceItem = 0;
unsigned long lastSequenceUpdate = 0;
int sequenceLength = 3;
int sequence[20];
int pressedSequenceItem = 0;
int pressedSequence[20];
bool generating = true;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Memory Game");

  Serial.begin(9600);

  randomSeed(A0);

  for (int i = 0; i < 20; i++) {
    sequence[i] = -1;
    pressedSequence[i] = -1;
  }

  for (Color &color: colors) {
    color.init();
  }
}

void loop() {
  for (Color &color: colors) {
    color.tick(generating, pressedSequence, pressedSequenceItem);
  }

  generating = !(sequenceLength == sequenceItem);

  if (abs(millis() - lastSequenceUpdate) > 1000 && generating) {
    sequence[sequenceItem] = (Color::playRandom(colors, sizeof(colors) / sizeof(colors[0])));
    sequenceItem++;
    lastSequenceUpdate = millis();
  }

  Serial.println(String(generating) + " | " + String(pressedSequenceItem) + " | " + String(sequenceItem));

  if (!generating && pressedSequenceItem == sequenceItem) {
    bool alive = true;
    for (int i = 0; i <= sequenceItem; i++) {
      if (sequence[i] != pressedSequence[i]) {
        alive = false;
        break;
      }
    }
    if (alive) {
      sequenceLength++;
    } else {
      sequenceLength = 3;
    }
    for (int i = 0; i < 20; i++) {
      sequence[i] = -1;
      pressedSequence[i] = -1;
    }
    sequenceItem = 0;
    pressedSequenceItem = 0;
    delay(1000);
  }

  lcd.setCursor(0, 1);
  lcd.print("Length: " + String(sequenceLength));
}