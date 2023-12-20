#pragma once
#include <Arduino.h>
#include "./led_parts/led_parts.h"
#include "../transmit/transmit.h"
#include "./utility/utility.h"

class LED{
    private:
        LED_PARTS led_parts = LED_PARTS();
        UTILITY utility = UTILITY();

        double i = 0;
        int panel_A_ID = 1000; int panel_B_ID = 1000; int panel_C_ID = 1000; int panel_N = 1000;
        int panel_ver = 48; int panel_hor = 48; //RGBのマックス,パネルの縦横LED数
        double px, py;

    public:
        LED();
        void init();
        void execute1(int x_coord);
};