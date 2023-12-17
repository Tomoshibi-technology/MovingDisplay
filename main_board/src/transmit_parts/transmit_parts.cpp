#include "./transmit_parts.h"


TRANSMIT_PARTS::TRANSMIT_PARTS(HardwareSerial* pt_port){
    PORT = pt_port;
}


void TRANSMIT_PARTS::start(int id, int send_or_receive){
    PORT -> write(250);
    PORT -> write(id*10 + send_or_receive);
}


void TRANSMIT_PARTS::send(byte* pt_input_array, int length_of_array){
    int sum = 0;
    for(int i = 0; i < length_of_array; i++){
        PORT -> write(pt_input_array[i]);
        sum = sum + pt_input_array[i];
    }
    //Serial.println(length_of_array);
    int checksum = 255 - (sum % 256);
    PORT -> write(checksum);
    delay(10);
}


void TRANSMIT_PARTS::recieve(byte* pt_output_array){
    int n = 0, sum = 0, i = 0;
    byte receive_data[] = {0,0,0,0,0,0,0,0,0,0};
    long mytime = millis();

    while(n < 2){
        if(PORT->available() > 0){
            int d = PORT->read();
            n++;
        }
        if(millis()>mytime+10){
            break;
        }
    }

    mytime = millis();
    i = 0;

    while(true){
        if(PORT->available() > 0){
            receive_data[i] =  PORT->read();
            sum = sum + receive_data[i];
            i++;
        }
        if(millis()>mytime+10){
            sum = sum - receive_data[i-1];
            break;
        }
    }

    if(255 - (sum%256) == receive_data[i-1]){
        for(int j = 0; j < i-1; j++){
            pt_output_array[j] = receive_data[j];
        }
    }
}