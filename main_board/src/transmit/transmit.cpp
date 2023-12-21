#include "./transmit.h"

TRANSMIT::TRANSMIT(int port_num){
    PN = port_num;
}

void TRANSMIT::init(){
    port1.begin(115200);
    port2.begin(115200);
    pinMode(PA4,OUTPUT);
    pinMode(PA5,OUTPUT);
    pinMode(PB0,INPUT);

    delay(100);
    digitalWrite(PA4,1);
}

void TRANSMIT::execute(){

    if(PN == 2){
        for(int sub_ID = 1; sub_ID <= 5;sub_ID++){

            transmit_port2.start(sub_ID,1);
            transmit_port2.send(send_array,sizeof(send_array));

            transmit_port2.start(sub_ID,2);
            transmit_port2.recieve(recieve_array);

            for(int j = 0; j < sizeof(recieve_array); j++){
                // Serial.print(recieve_array[j]);Serial.print(",");
                recieve_array[j]=0;
            }

            if(sub_ID ==5){
                utility.array_2_num(recieve_array, sizeof(recieve_array),&hoge);
            }
            // Serial.println("");
        }
    }else if(PN == 1){
        for(int sub_ID = 5; sub_ID <= 6;sub_ID++){

            transmit_port1.start(sub_ID,1);
            transmit_port1.send(send_array,sizeof(send_array));

            transmit_port1.start(sub_ID,2);
            transmit_port1.recieve(recieve_array);

            if(sub_ID ==5){
                utility.array_2_num(recieve_array, sizeof(recieve_array),&hoge);
            }

            for(int j = 0; j < sizeof(recieve_array); j++){
                recieve_array[j]=0;
            }
        }

    }

}