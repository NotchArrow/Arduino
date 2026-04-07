#include "Button.h"

Button::Button(int pin) {
  BUTTON_PIN = pin;
}

Button::Button(int pin, bool mode) {
  BUTTON_PIN = pin;
  toggleMode = mode;
}

void Button::begin() {
  pinMode(BUTTON_PIN, INPUT);
}

void Button::setupOutput(int pin) {
  if (!outputDirectly) {
    outputDirectly = true;
    outputPin = pin;
    pinMode(pin, OUTPUT);
  }
}

void Button::outputValue() {
  if (outputDirectly) {
    digitalWrite(outputPin, output);
  }
}

bool Button::tick() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != lastButtonState) {
    lastUpdateTime = millis();
  }

  if (millis() - lastUpdateTime > DEBOUNCE_DELAY) {
    if (!toggleMode) {
      output = buttonState;
    } else {
      if (!pressed && buttonState == HIGH) {
        pressed = true;
        output = !output;
      } else if (pressed && buttonState == LOW) {
        pressed = false;
      }
    }
  }

  lastButtonState = buttonState;
  return output;
}
