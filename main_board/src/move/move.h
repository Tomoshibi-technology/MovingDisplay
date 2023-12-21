#pragma once
#include <Arduino.h>
#include "../move/move_parts/move_parts.h"

class MOVE{
    private:

        MOVE_PARTS motor_A = MOVE_PARTS(1, 45);//(ID,MOTOR_DEGREE,Serial)
        MOVE_PARTS motor_B = MOVE_PARTS(2, 135);
        MOVE_PARTS motor_C = MOVE_PARTS(3, -135);
        MOVE_PARTS motor_D = MOVE_PARTS(4, -45);

    public:
        MOVE();
        void init();
        void execute0(int now_time, int start_time, int end_time, int goal_x_coord,int x_coord, int y_coord);
        void stop(int now_time, int start_time, int end_time, int goal_x_coord,int x_coord, int y_coord);
};