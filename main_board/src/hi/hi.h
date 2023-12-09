#pragma once
#include <Arduino.h>
#include "../transmit/transmit.h"

class HI{
  private:
    TRANSMIT* TR_PORT;
  public:
    HI(TRANSMIT* pt_tr_port);
    void go();
    void array_2_num(byte* pt_output_array,  int length_of_array, long* num){
        *num = 0;
        int hyaku = 1;
        for(int i = 0; i<length_of_array; i++){
            *num = *num + ((pt_output_array[i]-50)*hyaku);
            hyaku = hyaku * 100;
        }
        *num -= 1000000;
    }
};

//byte* send_array,byte* recieve_array