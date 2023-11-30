#include <Arduino.h>
#include "./transmit/transmit.h"

HardwareSerial port1 = HardwareSerial(PA10, PA9);

TRANSMIT tranmit_port1(&port1);

byte testarray[]={100,150,200};

void setup() {
  // put your setup code here, to run once:
  port1.begin(115200);
  delay(500);
  tranmit_port1.start(2,1);
  tranmit_port1.send(testarray);
}

void loop() {
  // put your main code here, to run repeatedly:
}