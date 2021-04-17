#include <led.h>

LED led(12);

void setup() {
}

void loop() {
  led.on();
  delay(1000);
  led.off();
  delay(1000);
}
