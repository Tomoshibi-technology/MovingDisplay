#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./led/led.h"
#include <Adafruit_NeoPixel.h>


TRANSMIT transmit1 = TRANSMIT(1);
TRANSMIT transmit2 = TRANSMIT(2);

LED led = LED();

void setup() {
  Serial.begin(115200);
  led.init();
  transmit1.init();
  transmit2.init();
}

void loop() {
  transmit2.execute();
  int x_coord = transmit2.hoge;
  x_coord = int(x_coord*0.00445);
  //Serial.println(x_coord);
  int mytime = micros();
  led.execute1(x_coord);
  Serial.println(micros()-mytime);
  //delay(10);
}

//----------------------------------------

