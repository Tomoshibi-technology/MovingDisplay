#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./led/led.h"
#include "./move/move.h"
#include <Adafruit_NeoPixel.h>


TRANSMIT transmit1 = TRANSMIT(1);
HardwareSerial TWE = HardwareSerial(PC7,PC6);

MOVE move = MOVE();
LED led = LED();

void read_TWE(byte* pt_twe_array, int array_num, int*st, int*nt);
byte TWE_array[4]={0,0,0,0};

int start_detect = 0;
int nstart_detect = 0;
int now_time = 0;
int mi_now = 0;
int sn = 0;
int sn2 = 0;
int x_coord = 0;
int y_coord = 0;

int error1 = 0, error2 = 0;

int time = 0;
int pre_time = 0;

void setup() {
  Serial.begin(115200);
  TWE.begin(115200);
  led.init();
  move.init();
  transmit1.init();
  pinMode(PA7,INPUT);
  mi_now = (int)millis()/100;
}

void loop() {
  read_TWE(TWE_array,sizeof(TWE_array),&error1,&error2);
  // now_time = (TWE_array[0]-5)+((TWE_array[1]-5)*250);
  // if(now_time>pre_time + 1000 or error1 == 1 or error2 == 1){
  //   now_time = pre_time;
  // }
  // pre_time = now_time;
  
  now_time = (int)millis()/100 - mi_now;

  transmit1.execute(x_coord);

  x_coord = transmit1.x;
  x_coord = int(x_coord*0.00445);
  y_coord = transmit1.y;
  y_coord = int(y_coord*0.00445);

  Serial.print("time ");
  Serial.print(now_time);
  Serial.print(" x_coord: ");
  Serial.print(x_coord);
  Serial.print(" y_coord: ");
  Serial.println(y_coord);

  int led_x_coord = -x_coord;

  led.execute1(now_time,0,500,led_x_coord);

  // time = 0;

  move.execute(now_time,0,80,350,x_coord,y_coord);
  move.stop(now_time,80,90,x_coord,y_coord);
  move.execute(now_time,90,170,0,x_coord,y_coord);
  move.stop(now_time,170,180,x_coord,y_coord);

  // if(start_detect>=10){
  //   if(sn==0){
  //     now_time = 0;
  //     mi_now = (int)millis()/100;
  //     sn= sn+1;
  //   }
  //   now_time = (int)millis()/100 - mi_now;

  //   transmit1.execute(x_coord);

  //   x_coord = transmit1.x;
  //   x_coord = int(x_coord*0.00445);
  //   y_coord = transmit1.y;
  //   y_coord = int(y_coord*0.00445);

  //   int led_x_coord = -x_coord;

  //   // Serial.println("");
  //   // Serial.print("time: ");
  //   // Serial.print(now_time);
  //   // Serial.print(" x_coord: ");
  //   // Serial.print(x_coord);
  //   // Serial.print(" y_coord: ");
  //   // Serial.println(y_coord);
    
  //   led.execute2(now_time,0,50,led_x_coord);
  //   led.execute0(now_time,50,150,led_x_coord);
  //   led.execute1(now_time,150,390,led_x_coord);
  //   if(nstart_detect<7){led.execute3(now_time,390,550,led_x_coord);}

  //   move.stop(now_time,0,50,x_coord,y_coord);

  //   move.execute(now_time,50,150,-250,x_coord,y_coord);
  //   move.stop(now_time,150,160,x_coord,y_coord);

  //   move.execute(now_time,160,180,-350,x_coord,y_coord);
  //   move.stop(now_time,180,190,x_coord,y_coord);
  //   move.execute(now_time,190,230,-150,x_coord,y_coord);
  //   move.stop(now_time,230,240,x_coord,y_coord);
  //   move.execute(now_time,240,280,-350,x_coord,y_coord);
  //   move.stop(now_time,280,290,x_coord,y_coord);
  //   move.execute(now_time,290,330,-150,x_coord,y_coord);
  //   move.stop(now_time,330,340,x_coord,y_coord);
  //   move.execute(now_time,340,380,-350,x_coord,y_coord);
  //   move.stop(now_time,380,390,x_coord,y_coord);

  //   move.execute(now_time,390,510,-50,x_coord,y_coord);
  //   move.stop(now_time,510,520,x_coord,y_coord);

  //   move.fullstop(now_time,520,550);
  // }
  // if(nstart_detect>=10){
  //   if(sn2==0){
  //     now_time = 0;
  //     mi_now = (int)millis()/100;
  //     sn2= sn2+1;
  //   }
  //   now_time = (int)millis()/100 - mi_now;

  //   transmit1.execute(x_coord);

  //   x_coord = transmit1.x;
  //   x_coord = int(x_coord*0.00445);
  //   y_coord = transmit1.y;
  //   y_coord = int(y_coord*0.00445);

  //   int led_x_coord = -x_coord;

  //   led.execute1(now_time,0,1000,led_x_coord);

  //   move.execute(now_time,0,100,-350,x_coord,y_coord);
  //   move.stop(now_time,100,110,x_coord,y_coord);
  //   move.execute(now_time,110,220,-150,x_coord,y_coord);
  //   move.stop(now_time,220,230,x_coord,y_coord);
  //   move.execute(now_time,230,300,-350,x_coord,y_coord);
  //   move.stop(now_time,300,310,x_coord,y_coord);
  //   move.execute(now_time,310,390,-150,x_coord,y_coord);
  //   move.stop(now_time,390,400,x_coord,y_coord);
  //   move.fullstop(now_time,400,450);
  // }
}

//----------------------------------------

void read_TWE(byte* pt_input_array, int array_num, int* st, int* nt){
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
      if(pt_input_array[0]==0){*st = 1;}
      else{*st = 0;}
      if(pt_input_array[1]==0){*nt = 1;}
      else{*nt = 0;}
      k++;
    }
    if(millis()>TWEtime+1){
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