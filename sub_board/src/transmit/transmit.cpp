#include "./transmit.h"


TRANSMIT::TRANSMIT(HardwareSerial* pt_port){
    PORT = pt_port;
}


void TRANSMIT::start(int id, int send_or_receive){
    PORT -> write(250);
    PORT -> write(id*10 + send_or_receive);
}


void TRANSMIT::send(byte* pt_input_array, int length_of_array){
    int sum = 0;
    for(int i = 0; i < length_of_array; i++){
        PORT -> write(pt_input_array[i]);
        sum = sum + pt_input_array[i];
        // Serial.println(pt_input_array[i]);
    }
    //Serial.println(length_of_array);
    int checksum = 255 - (sum % 256);
    PORT -> write(checksum);
    delay(10);
}


void TRANSMIT::recieve_send(byte* pt_output_array, byte* pt_input_array, int id, int length_of_array){
    int n = 0, sum = 0, i = 0;
    byte receive_data_f[] = {0,0};
    byte receive_data[] = {0,0,0,0,0,0,0,0,0,0};
    long mytime = millis();

    while(n < 1){
        if(PORT->available() > 0){
            receive_data_f[n] = PORT->read();
            // Serial.println( receive_data_f[0]);
            n++;
        }
        if(millis()>mytime+10){
            break;
        }
    }

    mytime = millis();

    if(receive_data_f[0]==id*10+2){
        start(id,2);
        send(pt_input_array,length_of_array);
    }
    else if(receive_data_f[0]==id*10+1){
        Serial.println(receive_data_f[0]);
        while(true){
            if(PORT->available() > 0){
                receive_data[i] =  PORT->read();
                sum = sum + receive_data[i];
                Serial.println(receive_data[i]);
                // delay(1);
                i++;
            }
            if(i>10){
                sum = sum - receive_data[i-1];
                // Serial.println(receive_data[i-1]);
                break;
            }
        }

        if(255 - (sum%256) == receive_data[i-1]){
            for(int j = 0; j < i-1; j++){
                pt_output_array[j] = receive_data[j];
            }
        }
    }else{
    }

    Serial.println("---");
}
