const int RS = 2;
const int RW = 3;
const int E = 4;

const int H_I = 7;
bool pressedH = false;
const int M_I = 8;
bool pressedM = false;
const int S_I = 9;
bool pressedS = false;

const int DB4 = 10; // 4th and 8th | 000x000x
const int DB5 = 11; // 3rd and 7th | 00x000x0
const int DB6 = 12; // 2nd and 6th | 0x000x00
const int DB7 = 13; // 1st and 5th | x000x000

const int STD_DELAY = 2;
const int OFFSET = 48;

unsigned long lastTickTime = 0;
bool AM = true;
int s2 = 0;
int s1 = 0;
int m2 = 0;
int m1 = 0;
int h2 = 2;
int h1 = 1;

/*
rewrite using OOP
clean up delay/lag
fix AM/PM using OOP
clean up counting using OOP
*/

void setup() {
  pinMode(RS, OUTPUT);
  pinMode(RW, OUTPUT);
  pinMode(E, OUTPUT);

  pinMode(H_I, INPUT);
  pinMode(M_I, INPUT);
  pinMode(S_I, INPUT);

  pinMode(DB4, OUTPUT);
  pinMode(DB5, OUTPUT);
  pinMode(DB6, OUTPUT);
  pinMode(DB7, OUTPUT);

  delay(100);
  resetSequence();
}

void loop() {
  cmd(0x80); // reset cursor

  checkButtons();

  draw(32);
  draw(32);

  draw(h1, true);
  draw(h2, true);
  draw(58);
  draw(m1, true);
  draw(m2, true);
  draw(58);
  draw(s1, true);
  draw(s2, true);

  draw(32);
  draw(32);

  if (AM) {
    draw(65);
  } else {
    draw(80);
  }
  draw(77);

  tick();
}

// helpers
void pulseE() {
  digitalWrite(E, HIGH);
  delay(STD_DELAY);
  digitalWrite(E, LOW);
}

void slowPulseE() {
  digitalWrite(E, HIGH);
  delay(STD_DELAY * 5);
  digitalWrite(E, LOW);
}

void resetSequence() {
  digitalWrite(RS, LOW);
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(DB4, HIGH);
    digitalWrite(DB5, HIGH);
    digitalWrite(DB6, LOW);
    digitalWrite(DB7, LOW);
    slowPulseE();
  }

  digitalWrite(DB4, LOW);
  digitalWrite(DB5, HIGH);
  digitalWrite(DB6, LOW);
  digitalWrite(DB7, LOW);
  slowPulseE();

  cmd(0x0C); // display on, cursor/blink off
  cmd(0x01); // clear screen
}

void checkButtons() {
  if (!pressedH && digitalRead(H_I) == HIGH) {
    pressedH = true;
    h2++;
    if (h2 == 2 && h1 == 1) {
      AM = !AM;
    }
  } else if (pressedH && digitalRead(H_I) == LOW) {
    pressedH = false;
  }

  if (!pressedM && digitalRead(M_I) == HIGH) {
    pressedM = true;
    m2++;
  } else if (pressedM && digitalRead(M_I) == LOW) {
    pressedM = false;
  }

  if (!pressedS && digitalRead(S_I) == HIGH) {
    pressedS = true;
    s2++;
  } else if (pressedS && digitalRead(S_I) == LOW) {
    pressedS = false;
  }

  if (pressedH || pressedM || pressedS) {
    wrapValues();
  }
}

void tick() {
  if (abs(millis() - lastTickTime) >= 1000) {
    s2++;
    lastTickTime += 1000;
    wrapValues();
    if (h2 == 2 && h1 == 1 && m2 == 0 && m1 == 0 && s2 == 0 && s1 == 0) {
      AM = !AM;
    }
  }
}

void wrapValues() {
  if (s2 > 9) {
    s2 = 0;
    s1++;
  }
  if (s1 > 5) {
    s1 = 0;
    m2++;
  }
  if (m2 > 9) {
    m2 = 0;
    m1++;
  }
  if (m1 > 5) {
    m1 = 0;
    h2++;
  }
  if (h2 > 9) {
    h2 = 0;
    h1++;
  }
  if (h1 > 1) {
    h1 = 0;
  }
  if (h2 > 2 && h1 == 1) {
    h2 = 1;
    h1 = 0;
  }
}

// https://circuitdigest.com/article/16x2-lcd-display-module-pinout-datasheet
// https://circuitdigest.com/sites/default/files/HD44780U.pdf

void draw(byte value) {
  digitalWrite(RS, HIGH);

  digitalWrite(DB7, (value & 0b1 << 7));
  digitalWrite(DB6, (value & 0b1 << 6));
  digitalWrite(DB5, (value & 0b1 << 5));
  digitalWrite(DB4, (value & 0b1 << 4));
  pulseE();
  digitalWrite(DB7, (value & 0b1 << 3));
  digitalWrite(DB6, (value & 0b1 << 2));
  digitalWrite(DB5, (value & 0b1 << 1));
  digitalWrite(DB4, (value & 0b1 << 0));
  pulseE();
}

void draw(byte value, bool offset) {
  digitalWrite(RS, HIGH);
  if (offset) {
    value = value + OFFSET;
  }

  digitalWrite(DB7, (value & 0b1 << 7));
  digitalWrite(DB6, (value & 0b1 << 6));
  digitalWrite(DB5, (value & 0b1 << 5));
  digitalWrite(DB4, (value & 0b1 << 4));
  pulseE();
  digitalWrite(DB7, (value & 0b1 << 3));
  digitalWrite(DB6, (value & 0b1 << 2));
  digitalWrite(DB5, (value & 0b1 << 1));
  digitalWrite(DB4, (value & 0b1 << 0));
  pulseE();
}

void cmd(byte value) {
  digitalWrite(RS, LOW);

  digitalWrite(DB7, (value & 0b1 << 7));
  digitalWrite(DB6, (value & 0b1 << 6));
  digitalWrite(DB5, (value & 0b1 << 5));
  digitalWrite(DB4, (value & 0b1 << 4));
  pulseE();
  digitalWrite(DB7, (value & 0b1 << 3));
  digitalWrite(DB6, (value & 0b1 << 2));
  digitalWrite(DB5, (value & 0b1 << 1));
  digitalWrite(DB4, (value & 0b1 << 0));
  pulseE();
}