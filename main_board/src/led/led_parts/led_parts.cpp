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
    else if(x > 15 && x <= 31){
        x -= 16;
        *panel_n = 1;
    }
    else if(x > 31 && x <=47){
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
    if(return_id > 255 && return_id <= 511){
        return_id += 1;
    }
    if(return_id >511 && return_id <= 767){
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

void LED_PARTS::set_under(int px, int py, int ur, int ug, int ub){
    r = ur;
    g = ug;
    b = ub;
}


void LED_PARTS::set_circle(int px, int py, int ro, int sx, int sy){
    sx = -sx;
    int py_plus_out = sqrt(ro*ro-(px-sx)*(px-sx)) + sy;
    int py_minus_out = -sqrt(ro*ro-(px-sx)*(px-sx)) + sy;
    if(py >= py_minus_out && py < py_plus_out){
        r = 20; g = 0; b = 0;
    }else{}
}


void LED_PARTS::set_square(int px, int py, int sd1, int sd2, int dg, int sx, int sy){
    sx = -sx;
    int px_out = (px-sx)*cos(-dg*0.017444)- (py-sy)*sin(-dg*0.017444) + sx;
    int py_out = (py-sy)*cos(-dg*0.017444) + (px-sx)*sin(-dg*0.017444) + sy;
    if((px_out >= sx && px_out <= sx + sd1) && (py_out >= sy && py_out <= sy+sd2)){
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
