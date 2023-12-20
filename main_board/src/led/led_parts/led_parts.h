#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "./utility/utility.h"
#include <math.h>

class LED_PARTS{
    private:
        int NUMPIXELS = 771;
        int LED_PIN_A = PB7;
        int LED_PIN_B = PB6;
        int LED_PIN_C = PB5;

        Adafruit_NeoPixel pixels_A = Adafruit_NeoPixel(NUMPIXELS, LED_PIN_A, NEO_GRB + NEO_KHZ800);
        Adafruit_NeoPixel pixels_B = Adafruit_NeoPixel(NUMPIXELS, LED_PIN_B, NEO_GRB + NEO_KHZ800);
        Adafruit_NeoPixel pixels_C = Adafruit_NeoPixel(NUMPIXELS, LED_PIN_C, NEO_GRB + NEO_KHZ800);

        UTILITY utility = UTILITY();

        int r,g,b; 
        int x_coord = 0;
        double i = 0;

    public:
        LED_PARTS();
        void init();
        void set_id(int x, int y, int* panel_a_id, int* panel_b_id, int* panel_c_id, int* panel_n);
        void set_circle(double px, double py, int ro, int sx, int sy);
        void set_square(double px, double py, double sd1, double sd2, int dg, int sx, int sy);
        void set_under(double px, double py, int ur, int ug, int ub);
        void set_color(int ipx, int ipy, int panel_a_id, int panel_b_id, int panel_c_id, int panel_n);
        void show();
        double sisin(int degree);
};