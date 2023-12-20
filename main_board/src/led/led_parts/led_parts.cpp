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

// void LED_PARTS::set_square(double px, double py, double sd1, double sd2, int dg, int sx, int sy){
//     double px_out = (px-sx)*cos(-dg*0.017444)- (py-sy)*sin(-dg*0.017444) + sx;
//     double py_out = (py-sy)*cos(-dg*0.017444) + (px-sx)*sin(-dg*0.017444) + sy;
//     if((px_out >= sx and px_out <= sx + sd1) and (py_out >= sy and py_out <= sy+sd2)){
//         r = 0; g = 0; b = 20;
//     }else{}
// }

// void LED_PARTS::set_square(double px, double py, double sd1, double sd2, int dg, int sx, int sy){
//     double si[24] = {0.00000, 0.25882, 0.50000, 0.70711, 0.86603, 0.96593, 1.00000, 0.96593, 0.86603, 0.70711, 0.50000, 0.25882, 0.00000, -0.25882, -0.50000, -0.70711, -0.86603, -0.96593, -1.00000, -0.96593, -0.86603, -0.70711, -0.50000, -0.25882};
//     double co[24] = {1.00000, 0.96593, 0.86603, 0.70711, 0.50000, 0.25882, 0.00000, -0.25882, -0.50000, -0.70711, -0.86603, -0.96593, -1.00000, -0.96593, -0.86603, -0.70711, -0.50000, -0.25882, 0.00000, 0.25882, 0.50000, 0.70711, 0.86603};
//     dg = dg%24;
//     double px_out = (px-sx)*co[24-dg]- (py-sy)*si[24-dg] + sx;
//     double py_out = (py-sy)*co[24-dg] + (px-sx)*si[24-dg] + sy;
//     if((px_out >= sx and px_out <= sx + sd1) and (py_out >= sy and py_out <= sy+sd2)){
//         r = 0; g = 0; b = 20;
//     }else{}
// }

void LED_PARTS::set_square(int px, int py, int sd1, int sd2, int dg, int sx, int sy){
    double si[24] = {0.00000, 0.25882, 0.50000, 0.70711, 0.86603, 0.96593, 1.00000, 0.96593, 0.86603, 0.70711, 0.50000, 0.25882, 0.00000, -0.25882, -0.50000, -0.70711, -0.86603, -0.96593, -1.00000, -0.96593, -0.86603, -0.70711, -0.50000, -0.25882};
    double co[24] = {1.00000, 0.96593, 0.86603, 0.70711, 0.50000, 0.25882, 0.00000, -0.25882, -0.50000, -0.70711, -0.86603, -0.96593, -1.00000, -0.96593, -0.86603, -0.70711, -0.50000, -0.25882, 0.00000, 0.25882, 0.50000, 0.70711, 0.86603};
    dg = dg%24;
    int px_out = (px-sx)*co[24-dg]- (py-sy)*si[24-dg] + sx;
    int py_out = (py-sy)*co[24-dg] + (px-sx)*si[24-dg] + sy;
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

// double LED_PARTS::sisin(int degree){
//     //degree = degree%360;
//     double si[24] = {0.00000, 0.25882, 0.50000, 0.70711, 0.86603, 0.96593, 1.00000, 0.96593, 0.86603, 0.70711, 0.50000, 0.25882, 0.00000, -0.25882, -0.50000, -0.70711, -0.86603, -0.96593, -1.00000, -0.96593, -0.86603, -0.70711, -0.50000, -0.25882};
//     return si[degree];
// }

// double LED_PARTS::cocos(int degree){
//     //degree = degree%360;
//     double co[24] = {1.00000, 0.96593, 0.86603, 0.70711, 0.50000, 0.25882, 0.00000, -0.25882, -0.50000, -0.70711, -0.86603, -0.96593, -1.00000, -0.96593, -0.86603, -0.70711, -0.50000, -0.25882, 0.00000, 0.25882, 0.50000, 0.70711, 0.86603};
//     return co[degree];
// }
