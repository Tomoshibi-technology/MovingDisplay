#include <Arduino.h>
#include "./transmit/transmit.h"
#include "./hi/hi.h"

void num_2_array(byte* pt_input_array, int length_of_array, long* num);
void array_2_num(byte* pt_output_array,  int length_of_array, long* num);

HardwareSerial port1 = HardwareSerial(PA10, PA9);
HardwareSerial port2 = HardwareSerial(PC5, PB10);

TRANSMIT transmit_port2(&port2);

//HI hey(&transmit_port2);

byte send_array[]={50,60,70,80,90,100,110,0,0,0};
byte recieve_array[]={0,0,0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(115200);
  port2.begin(115200);
  pinMode(PA4,OUTPUT);
  pinMode(PA5,OUTPUT);
  pinMode(PB0,INPUT);

  delay(1000);
  digitalWrite(PA4,1);
}

long hoge = 0;//この変数に送られてきた数字が入るよ


void loop() {

  for(int sub_ID = 1; sub_ID <= 5 ;sub_ID++){
    
    transmit_port2.start(sub_ID,1);
    transmit_port2.send(send_array,sizeof(send_array));

    transmit_port2.start(sub_ID,2);
    transmit_port2.recieve(recieve_array);

    array_2_num(recieve_array, sizeof(recieve_array),&hoge);
    Serial.print(sub_ID);Serial.print("/");
    Serial.println(hoge);

    for(int j = 0; j < sizeof(recieve_array); j++){
      recieve_array[j]=0;
    }
    delay(20);
  }
  Serial.println("------");
}

// void loop(){
//   //s_array, r_array
//   hey.go();
// }

//-----------------

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