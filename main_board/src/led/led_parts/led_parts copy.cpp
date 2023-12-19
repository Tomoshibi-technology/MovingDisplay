// # include "./led_parts.h"

// LED_PARTS::LED_PARTS(int ur, int ug, int ub){
//     UR = ur;
//     UG = ug;
//     UB = ub;
// }

// void LED_PARTS::init(){
//     pixels_A.begin();
//     pixels_B.begin();
//     pixels_C.begin();
// }



// void LED_PARTS::make_id3(int x, int y, int* panel_a_id, int* panel_b_id, int* panel_c_id, int* panel_n){
//     int return_id = 0;
// 	//y = 47 - y;//ここも書き換えること！

//     //panel番号付与/xを16*48に対応化
//     if(x <= 15){
//         x = x;
//         *panel_n = 0;
//     }
//     else if(x > 15 and x <= 31){
//         x -= 16;
//         *panel_n = 1;
//     }
//     else if(x > 31 and x <=47){
//         x -= 32;
//         *panel_n = 2;
//     }
//     else{}

//     //ID生成
//     if(y%2 == 0){
//         return_id = y*16 + x;
//     }
//     else{
//         return_id = y*16 + 15 - x;
//     }

//     //基板LED対応化
//     if(return_id > 255 and return_id <= 511){
//         return_id += 1;
//     }
//     if(return_id >511 and return_id <= 767){
//         return_id += 2;
//     }

//     //return
//     if(*panel_n == 0){
//         *panel_a_id = return_id;
//     }
//     else if(*panel_n == 1){
//         *panel_b_id = return_id;
//     }
//     else if(*panel_n == 2){
//         *panel_c_id = return_id;
//     }
//     else{}
// }

// void LED_PARTS::show_under(int ur, int ug, int ub){
//     UR = ur;
//     UG = ug;
//     UB = ub;
//     pixels_A.show();
//     pixels_B.show();
//     pixels_C.show();
// }



// void LED_PARTS::show_circle(int f_or_not ,int x_coord, int ro, int sx, int sy){

// 	for (int ipy = 0; ipy < panel_ver; ipy++){
// 		for (int ipx = 0; ipx < panel_hor; ipx++){

//             float px = ipx + x_coord;
//             float py = ipy;

//             float py_plus_out = sqrt(ro*ro-(px-sx)*(px-sx)) + sy;
//             float py_minus_out = -sqrt(ro*ro-(px-sx)*(px-sx)) + sy;
//             if(py >= py_minus_out and py <= py_plus_out){
//                 //r = 10 + 10*sin(i); b = 10 + 10*cos(i); g = 0;
//                 r = 20; g = 0; b = 0;

//                 make_id3(ipx, ipy, &panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
            
//                 if(panel_N == 0){
//                     pixels_A.setPixelColor(panel_A_ID, pixels_A.Color(r,g,b));
//                 }
//                 else if(panel_N == 1){
//                     pixels_B.setPixelColor(panel_B_ID, pixels_B.Color(r,g,b));
//                 }
//                 else if(panel_N == 2){
//                     pixels_C.setPixelColor(panel_C_ID, pixels_C.Color(r,g,b));
//                 }
//             }else{
//                 if(f_or_not==1){
//                     r = UR, b = UB, g = UG;
//                     make_id3(ipx, ipy, &panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
            
//                     if(panel_N == 0){
//                         pixels_A.setPixelColor(panel_A_ID, pixels_A.Color(r,g,b));
//                     }
//                     else if(panel_N == 1){
//                         pixels_B.setPixelColor(panel_B_ID, pixels_B.Color(r,g,b));
//                     }
//                     else if(panel_N == 2){
//                         pixels_C.setPixelColor(panel_C_ID, pixels_C.Color(r,g,b));
//                     }
//                 }
//             }
// 		}
// 	}
// }