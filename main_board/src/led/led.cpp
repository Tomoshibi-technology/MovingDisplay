#include "./led.h"

LED::LED(){}

void LED::init(){
    led_parts.init();
}

void LED::execute(int x_coord){
    for (int ipy = 0; ipy < panel_ver; ipy++){
		for (int ipx = 0; ipx < panel_hor; ipx++){
            
            px = ipx + x_coord;
            py = ipy;

            led_parts.set_under(px,py,2+2*cos(i),4+4*sin(i+3.1419),0);
            led_parts.set_circle(px,py,x_coord,12+8*sin(i),24,24);
            led_parts.set_circle(px,py,x_coord,6+4*cos(i),56,2);
            led_parts.set_circle(px,py,x_coord,7+6*sin(i+3.1419),60,40);

            led_parts.make_id3(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
            led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
        }
    }
    led_parts.show();
    i = i + 0.2;
}