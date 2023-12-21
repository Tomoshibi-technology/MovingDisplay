#include "./move.h"

MOVE::MOVE(){}

void MOVE::init(){
    motor_A.init();
}

void MOVE::execute0(int now_time, int start_time, int end_time, int goal_x_coord, int x_coord, int y_coord){
    if(now_time >= start_time && now_time < end_time){
        motor_A.calculate(end_time-now_time, goal_x_coord, x_coord, y_coord);
        // motor_B.calculate(end_time-now_time,goal_x_coord, x_coord, y_coord);
        motor_A.transmit();
    }
}