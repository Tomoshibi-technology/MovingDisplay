#include <Arduino.h>
#include "./transmit/transmit.h"

// put function declarations here:
HardwareSerial port1 = HardwareSerial(PA10,PA9);

TRANSMIT transmit_port1 = TRANSMIT(&port1);

int readID();

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

int light = 0;

byte send_array[10] = {0,0,0,0,0,0,0,0,0,0};
byte recieve_array[10] = {0,0,0,0,0,0,0,0,0,0};

void loop() {
  int my_ID = readID();
  int i = 0;

  while(port1.available()>0){
    recieve_array[i] = port1.read();

    if(recieve_array[i]==my_ID*10+2){
      send_array[0]=my_ID*10+7;
      send_array[1]=my_ID*10+8;
      send_array[2]=my_ID*10+9;

      transmit_port1.start(my_ID,2);
      transmit_port1.send(send_array,sizeof(send_array));
    }
    i++;
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