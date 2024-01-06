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
                led_parts.set_square(px,py,20,20,45,-300,22);
                led_parts.set_square(px,py,20,20,80,-200,12);
                led_parts.set_circle(px,py,18+2*sin(i),-250,24);
                led_parts.set_circle(px,py,18+2*sin(i),-130,6);
                

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        led_parts.show();
        i = i + 1;
    }
}

void LED::off(){
    for (int ipy = 0; ipy < panel_ver; ipy++){
        for (int ipx = 0; ipx < panel_hor; ipx++){
            

            led_parts.set_under(px,py,0,0,0);

        
            led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
            led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
        }
    }
    led_parts.show();
}

void LED::execute2(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time < end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);
                led_parts.set_square(px,py,10,5,45+i,-16,23);
                led_parts.set_square(px,py,15,5,-(45+i),-15,24);

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);

            }
        }
        led_parts.show();
        i = i + 3.5;
        if(i>90){
            i = 90;
        }
    }
}

void LED::execute0(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time < end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);
                led_parts.set_square(px,py,10,5,135,-16,23);
                led_parts.set_square(px,py,15,5,-135,-15,24);
                led_parts.set_square(px,py,10,5,135,-101,23);
                led_parts.set_square(px,py,15,5,-135,-100,24);
                led_parts.set_square(px,py,10,5,135,-201,23);
                led_parts.set_square(px,py,15,5,-135,-200,24);
                

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
                led_parts.set_circle(px,py,18+2*sin(i),-0,24);
                led_parts.set_circle(px,py,18+2*sin(i),-200,24);
                led_parts.set_circle(px,py,18+2*sin(i),-350,24);

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        i = i + 1;
        led_parts.show();
    }
}