#include <LiquidCrystal.h>
#include "pitches.h"


// display variables
#define RS 13
#define EN 12
#define D4 11
#define D5 10
#define D6 9
#define D7 8
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

#define ROTATE 7
bool rotatePressed = false;
int rotationState = 0;

// piano variables
#define CYCLE_UP 4
bool cycleUpPressed = false;
#define CYCLE_DOWN 5
bool cycleDownPressed = false;
#define SOUND_OUT 6
#define SOUND_TIME 50

// time variables
long timeOffset = 0;
#define timeH A1
bool pressedTimeH = false;
#define timeM A2
bool pressedTimeM = false;
#define timeS A3
bool pressedTimeS = false;

// temp variables
long tempReadTime = 0;
#define TEMP A0
#define TOGGLE_UNIT 4
bool toggleUnitPressed = false;
bool fahrenheit = false;


class Note {
  int input;
  int rotationID;
  int pitchID;
  int pitch;

  public:
    Note(int input, int rotationID) {
      this->input = input;
      this->rotationID = rotationID;
      this->pitchID = 49;
      this->pitch = PITCHES[this->pitchID];
    }

  public:
    void setupInput() {
      pinMode(input, INPUT);
    }

  public:
    void incPitch() {
      if (rotationState == this->rotationID) {
        if (digitalRead(CYCLE_UP) == HIGH && !cycleUpPressed) {
          cycleUpPressed = true;
          this->pitchID++;
          if (this->pitchID > 88) {
            this->pitchID = 0;
          }
          this->pitch = PITCHES[this->pitchID];
        } else if (digitalRead(CYCLE_UP) == LOW) {
          cycleUpPressed = false;
        }
      }
    }

  public:
    void decPitch() {
      if (rotationState == this->rotationID) {
        if (digitalRead(CYCLE_DOWN) == HIGH && !cycleDownPressed) {
          cycleDownPressed = true;
          this->pitchID--;
          if (this->pitchID < 0) {
            this->pitchID = 88;
          }
          this->pitch = PITCHES[this->pitchID];
        } else if (digitalRead(CYCLE_DOWN) == LOW) {
          cycleDownPressed = false;
        }
      }
    }

  public:
    String getPitch() {
      return String(PITCH_NAMES[this->pitchID]);
    }

  public:
    void play() {
      if (digitalRead(this->input) == HIGH) {
        tone(SOUND_OUT, this->pitch, SOUND_TIME);
      }
    }
};

const Note notes[] = {
  Note(A1, 1), Note(A2, 2), Note(A3, 3), Note(A4, 4), Note(A5, 5), Note(2, 6), Note(3, 7)
};

void setup() {
  lcd.begin(16, 2);

  for (auto &note : notes) {
    note.setupInput();
  }
  pinMode(TEMP, INPUT);
}

void loop() {
  lcd.setCursor(0, 0);
  if (rotationState >= 0 && rotationState <= 7) {
    pianoPrint();
    pianoButtons();
  } else if (rotationState == 8) {
    clockPrint();
    clockButtons();
  }

  rotateMode();
}

void rotateMode() {
  if (digitalRead(ROTATE) == HIGH && !rotatePressed) {
    rotatePressed = true;
    rotationState++;
    if (rotationState > 8) {
      rotationState = 0;
    }
  } else if (digitalRead(ROTATE) == LOW) {
    rotatePressed = false;
  }
}

void pianoPrint() {
  if (rotationState == 0) {
    for (int i = 0; i < 7; i++) {
      lcd.print(notes[i].getPitch() + " ");
      if (i == 3) {
        lcd.setCursor(0, 1);
      }
    }
    lcd.print("           ");
  } else if (rotationState > 0 && rotationState < 8) {
    lcd.print("Note " + String(rotationState) + ": " + notes[rotationState - 1].getPitch() + "       ");
    lcd.setCursor(0, 1);
    lcd.print("Cycle up or down");
  }
}

void pianoButtons() {
  for (auto &note : notes) {
    note.incPitch();
    note.decPitch();
    note.play();
  }
}

void clockPrint() {
  unsigned long time = millis() + timeOffset;
  String times[] = {String(int(time / 3600000) % 24), 
                    String(int(time % 3600000 / 60000) % 60),
                    String(int(time % 60000 / 1000) % 60)};
  
  for (int i = 0; i < 3; i++) {
    String timeStr = times[i];
    if (timeStr.length() == 1) {
      timeStr = "0" + timeStr;
    }
    lcd.print(timeStr);
    if (i < 2) {
      lcd.print(":");
    }
  }
  lcd.print("              ");

  if (millis() - tempReadTime > 1000) {
    tempReadTime = millis();
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    float voltage = analogRead(TEMP) / 1024.0 * 5.0;
    float C = (voltage - 0.5) * 100;
    float F = (C * 9.0 / 5.0) + 32;
    if (!fahrenheit) {
      lcd.print(String(C));
      lcd.print((char)0b11011111);
      lcd.print("C");
    } else {
      lcd.print(String(F));
      lcd.print((char)0b11011111);
      lcd.print("F");
    }
    lcd.print("              ");
  }
}

void clockButtons() {
  if (digitalRead(timeH) == HIGH && !pressedTimeH) {
    pressedTimeH = true;
    timeOffset += 3600000;
  } else if (digitalRead(timeH) == LOW) {
    pressedTimeH = false;
  }
  if (digitalRead(timeM) == HIGH && !pressedTimeM) {
    pressedTimeM = true;
    timeOffset += 60000;
  } else if (digitalRead(timeM) == LOW) {
    pressedTimeM = false;
  }
  if (digitalRead(timeS) == HIGH && !pressedTimeS) {
    pressedTimeS = true;
    timeOffset += 1000;
  } else if (digitalRead(timeS) == LOW) {
    pressedTimeS = false;
  }

  if (digitalRead(TOGGLE_UNIT) == HIGH && !toggleUnitPressed) {
    toggleUnitPressed = true;
    fahrenheit = !fahrenheit;
  } else if (digitalRead(TOGGLE_UNIT) == LOW) {
    toggleUnitPressed = false;
  }
}