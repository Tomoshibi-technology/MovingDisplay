#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./led/led.h"
#include "./move/move.h"
#include <Adafruit_NeoPixel.h>


TRANSMIT transmit1 = TRANSMIT(1);
HardwareSerial TWE = HardwareSerial(PC7,PC6);

MOVE move = MOVE();
LED led = LED();

void read_TWE(byte* pt_twe_array, int array_num, int*md);
bool read(void);
byte TWE_array[4]={0,0,0,0};

int now_time = 0;
int mi_now = 0;
int pre_time = 0;

int x_coord = 0;
int y_coord = 0;

int mode = 0;
int pre_mode = 0;
int n1 = 0, n2 = 0;

int mytime = 0;


void setup() {
  Serial.begin(115200);
  TWE.begin(115200);
  led.init();
  move.init();
  transmit1.init();

  pinMode(PA7,INPUT);
  pinMode(PA6,INPUT);

  mi_now = (int)millis()/100;
}

void loop() {
  // if(read()){
    // Serial.println("");Serial.print("------------------mode ");Serial.println(mode);
  read();
  // }

  transmit1.execute(x_coord);

  x_coord = transmit1.x;
  x_coord = int(x_coord*0.00445);
  y_coord = transmit1.y;
  y_coord = int(y_coord*0.00445);

  // Serial.println("");
  // Serial.print("time ");
  // Serial.print(now_time);
  // Serial.print(" x_coord: ");
  // Serial.print(x_coord);
  // Serial.print(" y_coord: ");
  // Serial.println(y_coord);

  int led_x_coord = -x_coord;

  /*
  if(digitalRead(PA7)==1){
    led.execute1(now_time,0,270,led_x_coord);
  }
  else if(digitalRead(PA6)==1){
    if(n1==0){
      mi_now = (int)millis()/100;
      n1 = n1 + 1;
    }
    now_time = (int)millis()/100 - mi_now;
    led.execute1(now_time,0,300,led_x_coord);

    move.execute(now_time,0,40,-150,x_coord,y_coord);
    move.stop(now_time,40,50,x_coord,y_coord);
    move.execute(now_time,50,130,150,x_coord,y_coord);
    move.stop(now_time,130,140,x_coord,y_coord);
  }
  */

  
  if(mode==2){

    if(pre_mode == 1 and mode == 2){
      mi_now = (int)millis()/100;
      // Serial.println("reset!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
    now_time = (int)millis()/100 - mi_now;
    led.execute2(now_time,0,50,led_x_coord);
    led.execute0(now_time,50,110,led_x_coord);
    led.execute1(now_time,110,270,led_x_coord);

    move.stop(now_time,0,50,x_coord,y_coord);
    move.execute(now_time,50,110,-300,x_coord,y_coord);
    move.stop(now_time,110,120,x_coord,y_coord);
    move.execute(now_time,120,150,-150,x_coord,y_coord);
    move.stop(now_time,150,160,x_coord,y_coord);
    move.execute(now_time,160,190,-300,x_coord,y_coord);
    move.stop(now_time,190,200,x_coord,y_coord);
    move.execute(now_time,200,230,-150,x_coord,y_coord);
    move.stop(now_time,230,270,x_coord,y_coord);

  }else if(mode==4){

    if(pre_mode == 3 and mode==4){
      mi_now = (int)millis()/100;
      // Serial.println("reset!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
    now_time = (int)millis()/100 - mi_now;
    led.execute1(now_time,0,220,led_x_coord);
    led.execute3(now_time,220,450,led_x_coord);

    move.execute(now_time,0,70,-300,x_coord,y_coord);
    move.stop(now_time,70,80,x_coord,y_coord);
    move.execute(now_time,120,160,-100,x_coord,y_coord);
    move.stop(now_time,160,170,x_coord,y_coord);
    move.execute(now_time,170,210,-300,x_coord,y_coord);
    move.stop(now_time,210,220,x_coord,y_coord);
    move.execute(now_time,220,270,-100,x_coord,y_coord);
    move.stop(now_time,270,280,x_coord,y_coord);
    move.execute(now_time,280,350,-300,x_coord,y_coord);
    move.stop(now_time,350,360,x_coord,y_coord);
    move.execute(now_time,360,400,-200,x_coord,y_coord);
    move.stop(now_time,400,450,x_coord,y_coord);

  }else if(mode==5){

    if(pre_mode == 4 and mode==5){
      mi_now = (int)millis()/100;
      // Serial.println("reset!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
    now_time = (int)millis()/100 - mi_now;
    led.execute3(now_time,0,220,led_x_coord);
    led.execute1(now_time,220,900,led_x_coord);

    move.execute(now_time,0,70,-300,x_coord,y_coord);
    move.stop(now_time,70,80,x_coord,y_coord);
    move.execute(now_time,120,160,-100,x_coord,y_coord);
    move.stop(now_time,160,170,x_coord,y_coord);
    move.execute(now_time,170,210,-300,x_coord,y_coord);
    move.stop(now_time,210,220,x_coord,y_coord);
    move.execute(now_time,220,270,-100,x_coord,y_coord);
    move.stop(now_time,270,280,x_coord,y_coord);
    move.execute(now_time,280,350,-300,x_coord,y_coord);
    move.stop(now_time,350,360,x_coord,y_coord);
    move.execute(now_time,360,420,-100,x_coord,y_coord);
    move.stop(now_time,420,430,x_coord,y_coord);
    move.execute(now_time,430,470,-200,x_coord,y_coord);
    move.stop(now_time,470,570,x_coord,y_coord);

  }else if(mode==6){
    led.off();
    move.fullstop(now_time,-9000000,9000000);
  }else{
    // mi_now = (int)millis()/100;
    move.stop(now_time,-9000000,9000000,x_coord,y_coord);
    move.fullstop(now_time,-9000000,9000000);
  }

  pre_mode = mode;
  
}

//----------------------------------------


bool read(void){ //受信成功したら1を返す
	if(TWE.available()>10){
		byte data = TWE.read();
		if(data == 250){
			byte raw_receive_data[4] = {0, 0, 0, 0};
			bool receive_bad_flg = 0; //受信失敗フラグ
			for(int i=0; i<4; i++){
				if(TWE.available()>0){
					raw_receive_data[i] = TWE.read();
					if(raw_receive_data[i] == 250){receive_bad_flg = 1; break;} //受信失敗フラグを立てる(250が来たら
				}else{
					receive_bad_flg = 1; break;
				}
			}
			if(!receive_bad_flg){
				for(int i=0; i<4; i++){
					TWE_array[i] = raw_receive_data[i];
          if(i==3){mode = TWE_array[i]-5;}
				}
				return 1;
			}
		}
	}
	return 0;
}
