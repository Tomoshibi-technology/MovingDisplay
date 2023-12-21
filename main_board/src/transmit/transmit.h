#pragma once
#include <Arduino.h>
#include "./utility/utility.h"
#include "./transmit_parts/transmit_parts.h"


class TRANSMIT{
    private:
        HardwareSerial port1 = HardwareSerial(PA10, PA9);
        HardwareSerial port2 = HardwareSerial(PC5, PB10);

        TRANSMIT_PARTS transmit_port1 = TRANSMIT_PARTS(&port1);
        TRANSMIT_PARTS transmit_port2 = TRANSMIT_PARTS(&port2);

        UTILITY utility = UTILITY();

        int PN;

        byte send_array[10]={50,60,70,80,90,100,110,0,0,0};
        byte recieve_array[10]={0,0,0,0,0,0,0,0,0,0};

        //long hoge = 0;//この変数に送られてきた数字が入るよ

    public:
        TRANSMIT(int port_num);
        void execute();
        void init();
        void test();
        long x;
        long y = 0;
};