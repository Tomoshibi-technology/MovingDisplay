#include <Arduino.h>

class TRANSMIT{
    private:
      HardwareSerial* PORT;

    public:
      TRANSMIT(HardwareSerial* pt_port);
      void start(int id, int send_or_receive);
      void send(byte* pt_input_array, int length_of_array);
      void recieve_send(byte* pt_output_array, byte* pt_input_array, int id,int length_of_array);
      void init();
      void test();
};