#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  public:
    int BUTTON_PIN;
    bool toggleMode = true;
    bool pressed = false;
    int output = LOW;
    unsigned long lastUpdateTime = 0;
    unsigned long DEBOUNCE_DELAY = 50;
    int lastButtonState = LOW;
    bool outputDirectly = false;
    int outputPin;

    Button(int pin);
    Button(int pin, bool mode);
    void begin();
    void setupOutput(int pin);
    void outputValue();
    bool tick();
};

#endif
