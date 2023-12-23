#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "./transmit/transmit_parts/transmit_parts.h"
#include "./utility/utility.h"

class MOVE_PARTS{
    private:
        int SUB_ID;
        int MOTER_DEGREE;
        long motor_speed = 0;
        float motor_rate = 0.7;
        // HardwareSerial* PO;
        TRANSMIT_PARTS* TR;
        // HardwareSerial port2 = HardwareSerial(PC5, PB10);
        // TRANSMIT_PARTS transmit_motor = TRANSMIT_PARTS(&port2);
        Adafruit_BNO055* B;
        UTILITY utility = UTILITY();
        byte send_array[10] = {0,0,0,0,0,0,0,0,0,0};
    public:
        MOVE_PARTS(int sub_ID, int motor_degree, TRANSMIT_PARTS* pt_trAdafruit_BNO055, Adafruit_BNO055* pt_b);
        void init();
        void calculate(int time_length, int goal_x_coord, int x_coord, int y_coord);
        void transmit();
        void calcstop();
};