#include "./led.h"

LED::LED(){}

void LED::init(){
    led_parts.init();
}

void LED::execute3(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time < end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);
                led_parts.set_square(px,py,20,20,180+180*sin(i),200,22);
                led_parts.set_square(px,py,20,20,180+180*cos(i),100,22);
                led_parts.set_circle(px,py,18+2*sin(i),150,24);
                

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        led_parts.show();
        i = i + 1;
    }
}

void LED::execute2(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time < end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        led_parts.show();
    }
}

void LED::execute0(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time < end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);
                led_parts.set_square(px,py,15,5,45,-10,18);
                led_parts.set_square(px,py,10,5,-45,-10,18);
                led_parts.set_square(px,py,15,5,45,40,18);
                led_parts.set_square(px,py,10,5,-45,40,18);
                led_parts.set_square(px,py,15,5,45,90,18);
                led_parts.set_square(px,py,10,5,-45,90,18);
                led_parts.set_square(px,py,15,5,45,130,18);
                led_parts.set_square(px,py,10,5,-45,130,18);

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        led_parts.show();
    }
}

void LED::execute1(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time <end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);
                led_parts.set_circle(px,py,18+2*sin(i),0,24);
                led_parts.set_circle(px,py,18+2*sin(i),150,24);
                led_parts.set_circle(px,py,18+2*sin(i),250,24);

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        i = i + 1;
        led_parts.show();
    }
}