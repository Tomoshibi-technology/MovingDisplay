#include "./transmit.h"


TRANSMIT::TRANSMIT(HardwareSerial* pt_port){
    PORT = pt_port;
}


void TRANSMIT::start(int id, int send_or_receive){
    PORT -> write(250);
    PORT -> write(send_or_receive*10 + id);
}


void TRANSMIT::send(byte* pt_array, int max_array){
    int sum = 0;
    for(int i = 0; i < max_array; i++){
        PORT -> write(pt_array[i]);
        sum = sum + pt_array[i];
    }
    int checksum = 255 - (sum % 256);
    PORT -> write(checksum);
}


void TRANSMIT::recieve(byte* pt_output_array){
    int i = 0, sum = 0;
    byte receive_data[] = {};
    long mytime = millis();
    while(true){
        if(PORT->available() > 0){
            receive_data[i] =  PORT->read();
            sum = sum + receive_data[i];
            i++;
        }
        if(millis()>mytime+10){
            sum = sum - (receive_data[0] + receive_data[1] + receive_data[i-1]);
            break;
        }
    }
    if(255 - (sum%256) == receive_data[i-1]){
        for(int n = 2; n < i-1; n++){
            pt_output_array[n-2] = receive_data[n];
        }
    }
}