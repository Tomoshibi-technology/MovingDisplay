#pragma once
#include <Arduino.h>

class UTILITY{
    private:

    public:
      UTILITY();
      void num_2_array(byte* pt_input_array, int length_of_array, long* num);
      void array_2_num(byte* pt_output_array,  int length_of_array, long* num);
      double calcSin(double rad);
      double calcCos(double rad);
      void init();
      void test();
};