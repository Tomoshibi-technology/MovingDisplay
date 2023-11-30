#include <Arduino.h>
#include "./transmit/transmit.h"

HardwareSerial port1 = HardwareSerial(PA10, PA9);
HardwareSerial port2 = HardwareSerial(PC5, PB10);

TRANSMIT transmit_port2(&port2);

byte test_input_array[]={100};
byte test_output_array[]={0,0,0,0,0,0,0,0,0,0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  port2.begin(115200);
  pinMode(PA4,OUTPUT);
  pinMode(PA5,OUTPUT);

  delay(1000);
  digitalWrite(PA4,1);
}

void loop() {
  if(digitalRead(PB0)==1){
    test_input_array[0]=99;
  }else{
    test_input_array[0]=100;
  }

  for(int i = 1; i < 5 ;i++){
    Serial.print("input ");
    Serial.println(test_input_array[0]);
    Serial.print(String(i) + "_ ");
    transmit_port2.start(i,1);
    transmit_port2.recieve(test_input_array);

    transmit_port2.start(i,2);
    transmit_port2.recieve(test_output_array);

    for(int j = 0; j < sizeof(test_output_array); j++){
      Serial.print(test_output_array[j]);
      Serial.print(",");
      test_output_array[j]=0;
    }

    Serial.println("");
    delay(50);
  }
  Serial.println("---");
}