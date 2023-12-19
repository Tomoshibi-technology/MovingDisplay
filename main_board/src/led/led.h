#pragma once
#include <Arduino.h>
#include "./led_parts/led_parts.h"
#include "../transmit/transmit.h"

class LED{
    private:
        LED_PARTS led_parts = LED_PARTS();
        float i = 0;
        int panel_A_ID = 1000; int panel_B_ID = 1000; int panel_C_ID = 1000; int panel_N = 1000;
        int panel_ver = 48; int panel_hor = 48; //RGBのマックス,パネルの縦横LED数
        float px, py;

    public:
        LED();
        void init();
        void execute(int x_coord);
};