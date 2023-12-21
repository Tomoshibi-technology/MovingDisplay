#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./led/led.h"
#include "./move/move.h"
#include <Adafruit_NeoPixel.h>


TRANSMIT transmit1 = TRANSMIT(1);


MOVE move = MOVE();
LED led = LED();

void setup() {
  Serial.begin(115200);
  led.init();
  move.init();
  transmit1.init();
}

int now_time = 0;

void loop() {
  now_time = (int)millis()/1000;

  transmit1.execute();
  int x_coord = transmit1.x;
  x_coord = int(x_coord*0.00445);
  
  led.execute1(now_time,0,1000,x_coord);
  move.execute0(now_time,0,10,-1000,x_coord,0);
}

//----------------------------------------

