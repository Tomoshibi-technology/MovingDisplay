#include <Arduino.h>
#include "./encoder/encoder.h"
#include "./motor/motor.h"
#include "./transmit/transmit.h"


ENCODER encoder(&Wire, 400000);
MOTOR motor(PB5, PB4, &encoder);

HardwareSerial port1 = HardwareSerial(PA10,PA9);
TRANSMIT transmit_port1 = TRANSMIT(&port1);

void readID_init();
int readID();
void num_2_array(byte* pt_input_array, int length_of_array, long* num);
void array_2_num(byte* pt_output_array,  int length_of_array, long* num);

void setup() {
	Serial.begin(115200);
	Serial.println(155);
	port1.begin(115200);
	encoder.init();
	motor.init();
}

uint32_t roop = 0;
float n = 0.000;

byte send_array[10] = {0,0,0,0,0,0,0,0,0,0};
byte recieve_array[10] = {0,0,0,0,0,0,0,0,0,0};

void loop() {
	//毎ループやらないと詰むやつ
	encoder.read_angle();
	encoder.calc_revolution();
	motor.calc_speed();
	//ここまで


	// int receive_status = 0;
	int receive_speed = 0;

	//ここから通信
	int my_ID = 5;
  int d = port1.read();

	long rev = motor.get_rev(); // 回転数取得
	// Serial.println(rev);

  if(d==250){
    num_2_array(send_array, sizeof(send_array),&rev);
    transmit_port1.recieve_send(recieve_array, send_array, my_ID, sizeof(send_array));
		// for(int i = 0; i<sizeof(recieve_array); i++){
		// 	Serial.print(recieve_array[i]);
		// 	Serial.print(" ");
		// }
		receive_speed = recieve_array[0] - 100;
  }
	// ここまで通信


	// ここからデバッグ用
	// if(roop%1000 == 0){
	// 	motor.test();
	// 	roop-=1000;
	// }; roop++;

}

void readID_init(){
  pinMode(PA7,INPUT);
  pinMode(PB0,INPUT);
  pinMode(PB1,INPUT);
  pinMode(PB5,INPUT);
}


int readID(){

	return 5;

  if(digitalRead(PA7)==1){return 1;}
  else if(digitalRead(PB0)==1){return 2;}
  else if(digitalRead(PB1)==1){return 3;}
  else if(digitalRead(PB5)==1){return 4;}
  else{return 99;}
}

void num_2_array(byte* pt_input_array, int length_of_array, long* num){
  long n = *num;
  n += 1000000;
  for(int i = 0; i<length_of_array; i++){
    pt_input_array[i]=(n%100)+50;
    n = int(n / 100);
  }
}

void array_2_num(byte* pt_output_array,  int length_of_array, long* num){
  *num = 0;
  int hyaku = 1;
  for(int i = 0; i<length_of_array; i++){
    *num = *num + ((pt_output_array[i]-50)*hyaku);
    hyaku = hyaku * 100;
  }
  *num -= 1000000;
}