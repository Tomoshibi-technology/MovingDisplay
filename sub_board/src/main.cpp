#include <Arduino.h>
#include "./transmit/transmit.h"

// put function declarations here:
HardwareSerial port1 = HardwareSerial(PA10,PA9);

TRANSMIT transmit_port1 = TRANSMIT(&port1);

int readID();
void num_2_array(byte* pt_input_array, int length_of_array, long* num);
void array_2_num(byte* pt_output_array,  int length_of_array, long* num);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  port1.begin(115200);
  pinMode(PA0,OUTPUT);
  pinMode(PA1,OUTPUT);

  pinMode(PA7,INPUT);
  pinMode(PB0,INPUT);
  pinMode(PB1,INPUT);
  pinMode(PB5,INPUT);

  digitalWrite(PA1,1);
  digitalWrite(PA0,1);
}

long hoge = 102003;//好きな数字をこの変数にいれればおくれるよ

byte send_array[10] = {0,0,0,0,0,0,0,0,0,0};
byte recieve_array[10] = {0,0,0,0,0,0,0,0,0,0};

void loop() {
  int my_ID = readID();
  int d = port1.read();
  if(d==250){
    num_2_array(send_array, sizeof(send_array),&hoge);
    transmit_port1.recieve_send(recieve_array, send_array, my_ID, sizeof(send_array));
  }
  delay(1);
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