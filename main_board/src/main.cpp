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

int now_time = 0;

void loop() {
  transmit2.execute();
  int x_coord = transmit2.hoge;
  // x_coord = int(x_coord*0.00445);
  x_coord = 24;

  Serial.println(x_coord);

  // led.execute2(now_time,0,40,x_coord);
  led.execute1(now_time,0,1000,x_coord);
}

//----------------------------------------

