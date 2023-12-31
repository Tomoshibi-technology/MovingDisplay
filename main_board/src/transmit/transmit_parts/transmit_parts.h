#pragma once
#include <Arduino.h>

class TRANSMIT_PARTS{
    private:
      HardwareSerial* PORT;

    public:
      TRANSMIT_PARTS(HardwareSerial* pt_port);
      void start(int id, int send_or_receive);
      void send(byte* pt_input_array, int length_of_array);
      void recieve(byte* pt_output_array);
      void init();
      void test();
};

