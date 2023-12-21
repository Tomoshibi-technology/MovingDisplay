#include "./transmit.h"

TRANSMIT::TRANSMIT(int port_num){
    PN = port_num;
}

void TRANSMIT::init(){
    if(PN==1){port1.begin(115200);}
    if(PN==2){port2.begin(115200);}
    pinMode(PA4,OUTPUT);
    pinMode(PA5,OUTPUT);
    pinMode(PB0,INPUT);

    delay(100);
    digitalWrite(PA4,1);
}

void TRANSMIT::execute(){

    if(PN == 2){
        for(int sub_ID = 1; sub_ID <= 4;sub_ID++){

            transmit_port2.start(sub_ID,1);
            transmit_port2.send(send_array,sizeof(send_array));

            transmit_port2.start(sub_ID,2);
            transmit_port2.recieve(recieve_array);

            if(sub_ID ==5){
                utility.array_2_num(recieve_array, sizeof(recieve_array),&x);
            }

            for(int j = 0; j < sizeof(recieve_array); j++){
                // Serial.print(recieve_array[j]);Serial.print(",");
                recieve_array[j]=0;
            }
            //delay(20);
            // Serial.println("");
        }
    }
    if(PN == 1){
        for(int sub_ID = 1; sub_ID < 2;sub_ID++){

            transmit_port1.start(sub_ID,1);
            transmit_port1.send(send_array,sizeof(send_array));

            transmit_port1.start(sub_ID,2);
            transmit_port1.recieve(recieve_array);

            if(sub_ID ==1){
                utility.array_2_num(recieve_array, sizeof(recieve_array),&x);
                // Serial.println(x);
            }
            if(sub_ID ==2){
                utility.array_2_num(recieve_array, sizeof(recieve_array),&y);
                // Serial.println(x);
            }

            // for(int j = 0; j < sizeof(recieve_array); j++){
            //     // Serial.print(recieve_array[j]);Serial.print(",");
            //     recieve_array[j]=0;
            // }

        }

    }
    //Serial.println("------");

}