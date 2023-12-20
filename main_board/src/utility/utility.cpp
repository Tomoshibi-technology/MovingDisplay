#include "./utility.h"

UTILITY::UTILITY(){

}

void UTILITY::num_2_array(byte* pt_input_array, int length_of_array, long* num){
  long n = *num;
  n += 1000000;
  for(int i = 0; i<length_of_array; i++){
    pt_input_array[i]=(n%100)+50;
    n = int(n / 100);
  }
}

void UTILITY::array_2_num(byte* pt_output_array,  int length_of_array, long* num){
  *num = 0;
  int hyaku = 1;
  for(int i = 0; i<length_of_array; i++){
    *num = *num + ((pt_output_array[i]-50)*hyaku);
    hyaku = hyaku * 100;
  }
  *num -= 1000000;
}

double UTILITY::calcSin(double rad) {

    while (rad >= 2 * PI) {
        rad -= 2 * PI;
    }

    if (rad >= 0 and rad < HALF_PI) {
        // Do nothing, rad is already in the correct range
    } else if (rad >= HALF_PI and rad < PI) {
        rad = PI - rad;
    } else if (rad >= PI and rad < 3 * HALF_PI) {
        rad = -(rad - PI);
    } else if (rad>= 3 * HALF_PI and rad < 2 * PI){
        rad = -(2 * PI - rad);
    }

    return rad + (rad * rad * rad) * (rad * rad - 20) * 0.0083;
}


double UTILITY::calcCos(double rad) {
    rad = rad + HALF_PI;

    while (rad >= 2 * PI) {
        rad -= 2 * PI;
    }

    if (rad >= 0 and rad < HALF_PI) {
        // Do nothing, rad is already in the correct range
    } else if (rad >= HALF_PI and rad < PI) {
        rad = PI - rad;
    } else if (rad >= PI and rad < 3 * HALF_PI) {
        rad = -(rad - PI);
    } else if (rad>= 3 * HALF_PI and rad < 2 * PI){
        rad = -(2 * PI - rad);
    }

    return rad + (rad * rad * rad) * (rad * rad - 20) * 0.0083;
}

