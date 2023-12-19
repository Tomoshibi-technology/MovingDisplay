#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./led/led.h"
#include <Adafruit_NeoPixel.h>


TRANSMIT transmit1 = TRANSMIT(1);
TRANSMIT transmit2 = TRANSMIT(2);

LED led1 = LED();

void setup() {
  Serial.begin(115200);
  led1.init();
  transmit1.init();
  transmit2.init();
}

void loop() {
  transmit2.execute();
  int x_coord = transmit2.hoge;
  x_coord = int(x_coord*18.21/4095);
  //Serial.println(x_coord);
  led1.execute(x_coord);

    

  //delay(10);
}

//----------------------------------------

