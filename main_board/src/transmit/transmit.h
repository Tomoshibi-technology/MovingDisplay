#include <Arduino.h>

class TRANSMIT{
    private:
      HardwareSerial* PORT;

    public:
      TRANSMIT(HardwareSerial* pt_port);
      void start(int id, int send_or_receive);
      void send(byte* pt_array, int max_array);
      void recieve(byte* pt_output_array);
      void init();
      void test();
};

