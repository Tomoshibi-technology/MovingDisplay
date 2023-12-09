#include "../HI/hi.h"

HI::HI(TRANSMIT* pt_tr_port){
  TR_PORT = pt_tr_port;
}

//byte* send_array,byte* recieve_array

void HI::go(){
    long hoge = 0;
    byte send_array[]={50,60,70,80,90,100,110,0,0,0};
    byte recieve_array[]={0,0,0,0,0,0,0,0,0,0};

    for(int sub_ID = 1; sub_ID <= 5 ;sub_ID++){
        
        TR_PORT->start(sub_ID,1);
        TR_PORT->send(send_array,sizeof(send_array));

        TR_PORT->start(sub_ID,2);
        TR_PORT->recieve(recieve_array);

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