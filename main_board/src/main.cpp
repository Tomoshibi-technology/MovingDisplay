#include <Arduino.h>
#include "./transmit/transmit.h"
#include <Adafruit_NeoPixel.h>

int NUMPIXELS = 771;
int LED_PIN_A = PB7;
int LED_PIN_B = PB6;
int LED_PIN_C = PB5;

Adafruit_NeoPixel pixels_A = Adafruit_NeoPixel(NUMPIXELS, LED_PIN_A, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_B = Adafruit_NeoPixel(NUMPIXELS, LED_PIN_B, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_C = Adafruit_NeoPixel(NUMPIXELS, LED_PIN_C, NEO_GRB + NEO_KHZ800);

TRANSMIT transmit = TRANSMIT();
void make_id3(int x, int y, int* panel_a_id, int* panel_b_id, int* panel_c_id, int* panel_n);

void setup() {
  Serial.begin(115200);
  transmit.init();
  pixels_A.begin();
  pixels_B.begin();
  pixels_C.begin();
}

int panel_A_ID = 1000; int panel_B_ID = 1000; int panel_C_ID = 1000; int panel_N = 1000;
int panel_ver = 48; int panel_hor = 48; //RGBのマックス,パネルの縦横LED数
int r,g,b; int x_coord = 0;
int sx = 24; int sy = 24;
float i = 0;

void loop() {
  transmit.execute();

  pixels_A.clear();
  pixels_B.clear();
  pixels_C.clear();

  sx = 24;

	for (int ipy = 0; ipy < panel_ver; ipy++){
		for (int ipx = 0; ipx < panel_hor; ipx++){

      float px = ipx + x_coord;
      int py = ipy;
      float py_plus_out = sqrt(289+289*sin(i)-(px-sx)*(px-sx)) + sy;
      float py_minus_out = -sqrt(289+289*sin(i)-(px-sx)*(px-sx)) + sy;
      // int px2 = px;

	    if(py >= py_minus_out and py <= py_plus_out){
				r = 10 + 10*sin(i); b = 10 + 10*cos(i); g = 0;
      }else{
        r = 5; g = 5; b = 5;
      }
			
			make_id3(ipx, ipy, &panel_A_ID, &panel_B_ID, &panel_C_ID, &panel_N);
    
      if(panel_N == 0){
        pixels_A.setPixelColor(panel_A_ID, pixels_A.Color(r,g,b));
      }
      else if(panel_N == 1){
        pixels_B.setPixelColor(panel_B_ID, pixels_B.Color(r,g,b));
      }
      else if(panel_N == 2){
        pixels_C.setPixelColor(panel_C_ID, pixels_C.Color(r,g,b));
      }
		}
	}

	pixels_A.show();
  pixels_B.show();
  pixels_C.show();
  i=i+0.1;

  //delay(10);
}

//----------------------------------------

void make_id3(int x, int y, int* panel_a_id, int* panel_b_id, int* panel_c_id, int* panel_n){
  //memoに重要なコメントを書いたからみてね

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