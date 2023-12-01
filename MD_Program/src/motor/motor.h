#ifndef _H_MOTOR_
#define _H_MOTOR_

#include <Arduino.h>
#include "./encoder/encoder.h"

class MOTOR{
	private:
		ENCODER* ENC;

		uint8_t A_PIN;
		uint8_t B_PIN;

		uint16_t FREQUENCY = 20000;

		uint16_t MAX_SPEED = 200;
		uint16_t MIN_SPEED = 0;

		int32_t now_motor_rev = 0; //現在の回転数(モーター角度)
		int32_t pre_motor_rev = 0; //過去の回転数(モーター角度)
		int32_t diff_motor_rev = 0;

		int32_t now_time = 0;
		int32_t pre_time = 0;
		int32_t diff_time = 0;

		int32_t speed = 0;
		int32_t pre_speed = 0;

		int16_t pre_duty = 0;
		
		void rotate(int16_t duty);//-255 - 255

	public:
		MOTOR(uint8_t a_pin, uint8_t b_pin, ENCODER* pt_enc);
		void init();
		void angle_rotate(uint16_t goal_angle);
		void speed_rotate(int16_t goal_speed);
		void calc_speed();

		int32_t get_rev(){
			return now_motor_rev;
		}

		uint16_t test();
};

#endif
