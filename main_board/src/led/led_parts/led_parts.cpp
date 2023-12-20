# include "./led_parts.h"

LED_PARTS::LED_PARTS(){
}

void LED_PARTS::init(){
    pixels_A.begin();
    pixels_B.begin();
    pixels_C.begin();
}



void LED_PARTS::set_id(int x, int y, int* panel_a_id, int* panel_b_id, int* panel_c_id, int* panel_n){
    int return_id = 0;
	//y = 47 - y;//ここも書き換えること！

    //panel番号付与/xを16*48に対応化
    if(x <= 15){
        x = x;
        *panel_n = 0;
    }
    else if(x > 15 and x <= 31){
        x -= 16;
        *panel_n = 1;
    }
    else if(x > 31 and x <=47){
        x -= 32;
        *panel_n = 2;
    }
    else{}

    //ID生成
    if(y%2 == 0){
        return_id = y*16 + x;
    }
    else{
        return_id = y*16 + 15 - x;
    }

    //基板LED対応化
    if(return_id > 255 and return_id <= 511){
        return_id += 1;
    }
    if(return_id >511 and return_id <= 767){
        return_id += 2;
    }

    //return
    if(*panel_n == 0){
        *panel_a_id = return_id;
    }
    else if(*panel_n == 1){
        *panel_b_id = return_id;
    }
    else if(*panel_n == 2){
        *panel_c_id = return_id;
    }
    else{}
}

void LED_PARTS::set_under(double px, double py, int ur, int ug, int ub){
    r = ur;
    g = ug;
    b = ub;
}



void LED_PARTS::set_circle(double px, double py, int ro, int sx, int sy){
    double py_plus_out = sqrt(ro*ro-(px-sx)*(px-sx)) + sy;
    double py_minus_out = -sqrt(ro*ro-(px-sx)*(px-sx)) + sy;
    if(py >= py_minus_out and py <= py_plus_out){
        r = 20; g = 0; b = 0;
    }else{}
}

void LED_PARTS::set_square(double px, double py, double sd1, double sd2, int dg, int sx, int sy){
    double px_out = (px-sx)*cos(-dg*0.017444)- (py-sy)*sin(-dg*0.017444) + sx;
    double py_out = (py-sy)*cos(-dg*0.017444) + (px-sx)*sin(-dg*0.017444) + sy;
    if((px_out >= sx and px_out <= sx + sd1) and (py_out >= sy and py_out <= sy+sd2)){
        r = 0; g = 0; b = 20;
    }else{}
}

void LED_PARTS::set_color(int ipx, int ipy, int panel_a_id, int panel_b_id, int panel_c_id, int panel_n){
    if(panel_n == 0){
        pixels_A.setPixelColor(panel_a_id, pixels_A.Color(r,g,b));
    }
    else if(panel_n == 1){
        pixels_B.setPixelColor(panel_b_id, pixels_B.Color(r,g,b));
    }
    else if(panel_n == 2){
        pixels_C.setPixelColor(panel_c_id, pixels_C.Color(r,g,b));
    }
}

void LED_PARTS::show(){
    pixels_A.show();
    pixels_B.show();
    pixels_C.show();
}

double LED_PARTS::sisin(int degree){
    //degree = degree%360;
    double si[360] = {0.00000, 0.01745, 0.03490, 0.05234, 0.06976, 0.08716, 0.10453, 0.12187, 0.13917, 0.15643, 0.17365, 0.19081, 0.20791, 0.22495, 0.24192, 0.25882, 0.27564, 0.29237, 0.30902, 0.32557, 0.34202, 0.35837, 0.37461, 0.39073, 0.40674, 0.42262, 0.43837, 0.45399, 0.46947, 0.48481, 0.50000, 0.51504, 0.52992, 0.54464, 0.55919, 0.57358, 0.58779, 0.60182, 0.61566, 0.62932, 0.64279, 0.65606, 0.66913, 0.68200, 0.69466, 0.70711, 0.71934, 0.73135, 0.74314, 0.75471, 0.76604, 0.77715, 0.78801, 0.79864, 0.80902, 0.81915, 0.82904, 0.83867, 0.84805, 0.85717, 0.86603, 0.87462, 0.88295, 0.89101, 0.89879, 0.90631, 0.91355, 0.92050, 0.92718, 0.93358, 0.93969, 0.94552, 0.95106, 0.95630, 0.96126, 0.96593, 0.97030, 0.97437, 0.97815, 0.98163, 0.98481, 0.98769, 0.99027, 0.99255, 0.99452, 0.99619, 0.99756, 0.99863, 0.99939, 0.99985, 1.00000, 0.99985, 0.99939, 0.99863, 0.99756, 0.99619, 0.99452, 0.99255, 0.99027, 0.98769, 0.98481, 0.98163, 0.97815, 0.97437, 0.97030, 0.96593, 0.96126, 0.95630, 0.95106, 0.94552, 0.93969, 0.93358, 0.92718, 0.92050, 0.91355, 0.90631, 0.89879, 0.89101, 0.88295, 0.87462, 0.86603, 0.85717, 0.84805, 0.83867, 0.82904, 0.81915, 0.80902, 0.79864, 0.78801, 0.77715, 0.76604, 0.75471, 0.74314, 0.73135, 0.71934, 0.70711, 0.69466, 0.68200, 0.66913, 0.65606, 0.64279, 0.62932, 0.61566, 0.60182, 0.58779, 0.57358, 0.55919, 0.54464, 0.52992, 0.51504, 0.50000, 0.48481, 0.46947, 0.45399, 0.43837, 0.42262, 0.40674, 0.39073, 0.37461, 0.35837, 0.34202, 0.32557, 0.30902, 0.29237, 0.27564, 0.25882, 0.24192, 0.22495, 0.20791, 0.19081, 0.17365, 0.15643, 0.13917, 0.12187, 0.10453, 0.08716, 0.06976, 0.05234, 0.03490, 0.01745};
    return si[degree];
}
