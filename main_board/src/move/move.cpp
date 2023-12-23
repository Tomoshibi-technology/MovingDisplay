#include "./move.h"

MOVE::MOVE(){}

void MOVE::init(){
    //ここではtransmit_motor.init()にするとよくなるかも　その中でport2.begin???
    port2.begin(115200);
    // motor_A.init();
    bno.begin();
}

void MOVE::execute(int now_time, int start_time, int end_time, int goal_x_coord, int x_coord, int y_coord){
    if(now_time >= start_time && now_time < end_time){
        motor_A.calculate(end_time-now_time, goal_x_coord, x_coord, y_coord);
        motor_B.calculate(end_time-now_time, goal_x_coord, x_coord, y_coord);
        motor_C.calculate(end_time-now_time, goal_x_coord, x_coord, y_coord);
        motor_D.calculate(end_time-now_time,goal_x_coord, x_coord, y_coord);
        motor_A.transmit();
        motor_B.transmit();
        motor_C.transmit();
        motor_D.transmit();
    }
}

void MOVE::stop(int now_time, int start_time, int end_time, int x_coord, int y_coord){
    if(now_time >= start_time && now_time < end_time){
        motor_A.calculate(end_time-now_time, x_coord, x_coord, y_coord);
        motor_B.calculate(end_time-now_time, x_coord, x_coord, y_coord);
        motor_C.calculate(end_time-now_time, x_coord, x_coord, y_coord);
        motor_D.calculate(end_time-now_time,x_coord, x_coord, y_coord);
        motor_A.transmit();
        motor_B.transmit();
        motor_C.transmit();
        motor_D.transmit();
    }
}

