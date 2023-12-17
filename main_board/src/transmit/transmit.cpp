#include "./transmit.h"

TRANSMIT::TRANSMIT(){}

void TRANSMIT::init(){
    port2.begin(115200);
    pinMode(PA4,OUTPUT);
    pinMode(PA5,OUTPUT);
    pinMode(PB0,INPUT);

    delay(100);
    digitalWrite(PA4,1);
}

void TRANSMIT::execute(){

    for(int sub_ID = 1; sub_ID <= 5;sub_ID++){

        transmit_port2.start(sub_ID,1);
        transmit_port2.send(send_array,sizeof(send_array));

        transmit_port2.start(sub_ID,2);
        transmit_port2.recieve(recieve_array);

        if(sub_ID ==5){
            utility.array_2_num(recieve_array, sizeof(recieve_array),&hoge);
        // Serial.print(sub_ID);Serial.print("/");
        // Serial.println(hoge);
        }

        for(int j = 0; j < sizeof(recieve_array); j++){
            // Serial.print(recieve_array[j]);Serial.print(",");
            recieve_array[j]=0;
        }
        //delay(20);
        // Serial.println("");
    }
    Serial.println("------");

}