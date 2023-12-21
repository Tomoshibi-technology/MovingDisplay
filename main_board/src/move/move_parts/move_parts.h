#pragma once
#include <Arduino.h>
#include "./transmit/transmit.h"

class MOVE_PARTS{
    private:
        TRANSMIT transmit2 = TRANSMIT(2);
    public:
        MOVE_PARTS();
        void init();
        void run(int now_time, int start_time, int end_time, int in_start_time, int in_end_time, int goal_x_coord, int x_coord, int y_coord);
};