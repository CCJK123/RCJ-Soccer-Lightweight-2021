#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#ifndef led_h
#define led_h

class LED : public Adafruit_NeoPixel {
  public:
    LED(int pin);
    void on();  
    void off();
  private:
    int _pin;
    
};

#endif