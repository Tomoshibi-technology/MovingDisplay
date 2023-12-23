#pragma once
#include <Arduino.h>
#include "../move/move_parts/move_parts.h"

class MOVE{
    private:

        Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
        HardwareSerial port2 = HardwareSerial(PC5, PB10);
        TRANSMIT_PARTS transmit_motor = TRANSMIT_PARTS(&port2);

        MOVE_PARTS motor_A = MOVE_PARTS(1, 45, &transmit_motor, &bno);//(ID,MOTOR_DEGREE,Serial)
        MOVE_PARTS motor_B = MOVE_PARTS(2, 135,&transmit_motor, &bno);
        MOVE_PARTS motor_C = MOVE_PARTS(3, -135,&transmit_motor, &bno);
        MOVE_PARTS motor_D = MOVE_PARTS(4, -45,&transmit_motor, &bno);

    public:
        MOVE();
        void init();
        void execute(int now_time, int start_time, int end_time, int goal_x_coord,int x_coord, int y_coord);
        void stop(int now_time, int start_time, int end_time, int x_coord, int y_coord);
};