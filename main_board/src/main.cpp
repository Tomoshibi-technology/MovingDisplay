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
  pinMode(PA7,INPUT);
}

int now_time = 0;

void loop() {
  if(digitalRead(PA7)==1){
    now_time = (int)millis()/100;

    transmit1.execute();
    int x_coord = transmit1.x;
    x_coord = int(x_coord*0.00445);
    int y_coord = transmit1.y;
    y_coord = int(y_coord*0.00445);
    Serial.print("time: ");
    Serial.print(now_time);
    Serial.print(" x_coord: ");
    Serial.print(x_coord);
    Serial.print(" y_coord: ");
    Serial.println(y_coord);

    int led_x_coord = -x_coord;
    
    led.execute1(now_time,0,10000,led_x_coord);
    move.execute0(now_time,0,100,300,x_coord,y_coord);
    move.stop(now_time,100,150,x_coord,y_coord);
    move.execute0(now_time,150,250,0,x_coord,y_coord);
    move.stop(now_time,250,300,x_coord,y_coord);

  }
}

//----------------------------------------

