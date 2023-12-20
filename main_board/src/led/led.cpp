#include "./led.h"

LED::LED(){}

void LED::init(){
    led_parts.init();
}

void LED::execute1(int x_coord){
    //long mytime = micros();
    for (int ipy = 0; ipy < panel_ver; ipy++){
		for (int ipx = 0; ipx < panel_hor; ipx++){
            
            px = ipx + x_coord;
            py = ipy;

            led_parts.set_under(px,py,3,0,1);
            led_parts.set_square(px,py,10,10,180+180*sin(i),18+18*sin(i),20);
            // led_parts.set_circle(px,py,15,24,24);
            // led_parts.set_circle(px,py,12,56,2);
            // led_parts.set_circle(px,py,8,60,40);

            led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
            led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
        }
    }
    //Serial.println(micros()-mytime);
    led_parts.show();
    i = i + 0.15;
}