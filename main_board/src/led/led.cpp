#include "./led.h"

LED::LED(){}

void LED::init(){
    led_parts.init();
}

// void LED::execute2(int x_coord){
//     //long mytime = micros();
//     for (int ipy = 0; ipy < panel_ver; ipy++){
// 		for (int ipx = 0; ipx < panel_hor; ipx++){
            
//             px = ipx + x_coord;
//             py = ipy;

//             led_parts.set_under(px,py,0,3,1);
//             led_parts.set_circle(px,py,15,24,24);
//             led_parts.set_circle(px,py,12,56,2);
//             led_parts.set_circle(px,py,8,60,40);
//             led_parts.set_square(px,py,20,20,2,48,20);

//             led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
//             led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
//         }
//         led_parts.show();
//     }
// }

void LED::execute0(int now_time, int start_time, int end_time, int x_coord){
    if(now_time >= start_time && now_time < end_time){
        for (int ipy = 0; ipy < panel_ver; ipy++){
            for (int ipx = 0; ipx < panel_hor; ipx++){
                
                px = ipx + x_coord;
                py = ipy;

                led_parts.set_under(px,py,0,3,1);
                led_parts.set_square(px,py,15,5,45,48,18);
                led_parts.set_square(px,py,10,5,-45,48,18);
                led_parts.set_square(px,py,15,5,45,96,18);
                led_parts.set_square(px,py,10,5,-45,96,18);

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
                led_parts.set_circle(px,py,12+6*sin(i),0,24);

                led_parts.set_id(ipx,ipy,&panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
                led_parts.set_color(ipx,ipy, panel_A_ID, panel_B_ID, panel_C_ID, panel_N);
            }
        }
        i = i + 0.25;
        led_parts.show();
    }
    //Serial.println(micros()-mytime);
    led_parts.show();
    //i = i + 0.2;
}