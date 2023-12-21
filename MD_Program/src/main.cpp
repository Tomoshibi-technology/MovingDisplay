#include <Arduino.h>
#include "./encoder/encoder.h"
#include "./motor/motor.h"
#include "./transmit/transmit.h"

// const int RX_PIN = PA10;
// const int TX_PIN = PA9;
// const int ID_SWITCH_PIN[4] = {PA7,PB0,PB1,PB5};
const int LED_PIN[2] = {PA1, PA0};
// const int MD_PWM_PIN[2] = {PA8, PA12};


ENCODER encoder(&Wire, 400000);
MOTOR motor(PA8, PA12, &encoder);

HardwareSerial port1 = HardwareSerial(PA10,PA9);
TRANSMIT transmit_port1 = TRANSMIT(&port1);

void readID_init();
int readID();
void num_2_array(byte* pt_input_array, int length_of_array, long* num);
void array_2_num(byte* pt_output_array,  int length_of_array, long* num);

void setup() {
	Serial.begin(115200);
	Serial.println(155);
	encoder.init();
	motor.init();
	port1.begin(115200);
}

uint32_t roop = 0;
float n = 0.000;

byte send_array[10] = {0,0,0,0,0,0,0,0,0,0};
byte recieve_array[10] = {0,0,0,0,0,0,0,0,0,0};

long receive_speed = 0;

void loop() {
	pinMode(LED_PIN[0], OUTPUT);
	digitalWrite(LED_PIN[0], HIGH);

	//毎ループやらないと詰むやつ
	encoder.read_angle();
	encoder.calc_revolution();
	motor.calc_speed();
	//ここまで


	// int receive_status = 0

	//ここから通信
	int my_ID = readID();
  	int d = port1.read();
	// Serial.println(my_ID);

	long rev = motor.get_rev(); // 回転数取得

  if(d==250){
    num_2_array(send_array, sizeof(send_array),&rev);
    transmit_port1.recieve_send(recieve_array, send_array, my_ID, sizeof(send_array));

	array_2_num(recieve_array, sizeof(recieve_array), &receive_speed);
	// Serial.println(receive_speed);
  }
	// ここまで通信

	// ここから回転
	// 50-100 逆転
	// 100-150 正転
	motor.speed_rotate(receive_speed);
	
	// motor.speed_rotate(20*sin(n));
	// n+=0.0001;
	
	// ここまで回転



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