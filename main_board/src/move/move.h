#pragma once
#include <Arduino.h>

class MOVE{
    private:

    public:
        MOVE();
        void init();
        void execute0(int now_time, int start_time, int end_time, int x_coord, int y_coord);
};