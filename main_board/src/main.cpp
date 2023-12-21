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
  now_time = (int)millis()/100;

  transmit1.execute();
  int x_coord = transmit1.x;
  x_coord = int(x_coord*0.00445);
  
  led.execute1(now_time,0,1000,x_coord);
}

//----------------------------------------

