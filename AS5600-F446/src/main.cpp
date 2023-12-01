#include <Arduino.h>
#include "./encoder/encoder.h"
#include "./motor/motor.h"

const int RX_PIN = PA10;
const int TX_PIN = PA9;
const int ID_SWITCH_PIN[4] = {PA7,PB0,PB1,PB5};
const int LED_PIN[2] = {PA1, PA0};
const int MD_PWM_PIN[2] = {PA8, PA12};


ENCODER encoder(&Wire, 400000);
MOTOR motor(PA8, PA12, &encoder);


void setup() {
	Serial.begin(115200);
	Serial.println(155);
	encoder.init();
	motor.init();
}

uint32_t roop = 0;
float n = 0.000;

void loop() {
	pinMode(LED_PIN[0], OUTPUT);
	digitalWrite(LED_PIN[0], HIGH);

	//毎ループやらないと詰むやつ
	encoder.read_angle();
	encoder.calc_revolution();
	motor.calc_speed();
	//ここまで

	motor.speed_rotate(0);
	// motor.speed_rotate(20*sin(n));
	n+=0.0001;

	int32_t rev = motor.get_rev();

	
	// if(roop%1000 == 0){
	// 	motor.test();
	// 	roop-=1000;
	// }; roop++;
}
