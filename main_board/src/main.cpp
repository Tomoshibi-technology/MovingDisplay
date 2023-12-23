#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./led/led.h"
#include "./move/move.h"
#include <Adafruit_NeoPixel.h>


TRANSMIT transmit1 = TRANSMIT(1);
HardwareSerial TWE = HardwareSerial(PC7,PC6);

MOVE move = MOVE();
LED led = LED();

void read_TWE(byte* pt_twe_array, int array_num);
byte TWE_array[4]={0,0,0,0};

void setup() {
  Serial.begin(115200);
  // TWE.begin(115200);
  led.init();
  move.init();
  transmit1.init();
  pinMode(PA7,INPUT);
}

int now_time = 0;
int mi_now = 0;
int sn = 0;

void loop() {
  // read_TWE(TWE_array,sizeof(TWE_array));
  if(digitalRead(PA7)==1){
    if(sn==0){
      now_time = 0;
      mi_now = (int)millis()/100;
      sn= sn+1;
    }
    now_time = (int)millis()/100 - mi_now;

    transmit1.execute();
    int x_coord = transmit1.x;
    x_coord = int(x_coord*0.00445);
    int y_coord = transmit1.y;
    y_coord = int(y_coord*0.00445);

    int led_x_coord = -x_coord;
    
    led.execute0(now_time,0,100,led_x_coord);
    led.execute1(now_time,100,270,led_x_coord);
    led.execute3(now_time,270,500,led_x_coord);

    // move.execute(now_time,0,100,150,x_coord,y_coord);
    // move.stop(now_time,100,110,x_coord,y_coord);
    // move.execute(now_time,110,160,200,x_coord,y_coord);
    // move.stop(now_time,160,170,x_coord,y_coord);
    // move.execute(now_time,170,200,100,x_coord,y_coord);
    // move.stop(now_time,200,210,x_coord,y_coord);
    // move.execute(now_time,210,240,200,x_coord,y_coord);
    // move.stop(now_time,240,250,x_coord,y_coord);
    // move.execute(now_time,250,260,150,x_coord,y_coord);
    // move.stop(now_time,260,270,x_coord,y_coord);

    // move.execute(now_time,270,300,250,x_coord,y_coord);
    // move.stop(now_time,300,310,x_coord,y_coord);
    // move.execute(now_time,310,360,50,x_coord,y_coord);
    // move.stop(now_time,360,370,x_coord,y_coord);

    move.fullstop(now_time,370,400);
  }
}

//----------------------------------------

void read_TWE(byte* pt_input_array, int array_num){
  while(true){
    if(TWE.available()>0){
      int data = TWE.read();
      if(data==250){break;}
    }
  }
  int TWEtime = millis();
  int k = 0;
  while(k<array_num){
    if(TWE.available()>0){
      pt_input_array[k]=TWE.read();
      k++;
    }
    if(millis()>TWEtime+2){
      break;
    }
  }
}

    // Serial.println("");
    // Serial.print("time: ");
    // Serial.print(now_time);
    // Serial.print(" x_coord: ");
    // Serial.print(x_coord);
    // Serial.print(" y_coord: ");
    // Serial.println(y_coord);