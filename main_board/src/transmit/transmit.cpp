#include "./transmit.h"


TRANSMIT::TRANSMIT(HardwareSerial* pt_port){
    PORT = pt_port;
}


void TRANSMIT::start(int id, int send_or_receive){
    PORT -> write(250);
    PORT -> write(send_or_receive*10 + id);
}


void TRANSMIT::send(byte* pt_input_array){
    int sum = 0;
    for(int i = 0; i < sizeof(pt_input_array); i++){
        PORT -> write(pt_input_array[i]);
        sum = sum + pt_input_array[i];
    }
    int checksum = 255 - (sum % 256);
    PORT -> write(checksum);
}


void TRANSMIT::recieve(byte* pt_output_array){
    int n = 0, i = 0, sum = 0;
    byte receive_data[] = {};
    long mytime = millis();
    while(n < 2){
        if(PORT->available() > 0){
            PORT->read();
            n++;
        }
        if(millis()>mytime+100){
            break;
        }
    }
    mytime = millis();
    while(true){
        if(PORT->available() > 0){
            receive_data[i] =  PORT->read();
            sum = sum + receive_data[i];
            i++;
        }
        if(millis()>mytime+100){
            sum = sum - receive_data[sizeof(receive_data)-1];
            break;
        }
    }
    if(255 - (sum%256) == receive_data[sizeof(receive_data)-1]){
        for(int j = 0; j < sizeof(receive_data); j++){
            pt_output_array[j] = receive_data[j];
        }
    }
}