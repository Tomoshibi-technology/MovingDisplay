#include "./motor.h"

MOTOR::MOTOR(uint8_t a_pin, uint8_t b_pin, ENCODER* pt_enc){
	A_PIN = a_pin;
	B_PIN = b_pin;
	ENC = pt_enc;
}

void MOTOR::init(){
	pinMode(A_PIN, OUTPUT);
	pinMode(B_PIN, OUTPUT);
	analogWriteFrequency(FREQUENCY);
}

void MOTOR::angle_rotate(uint16_t goal_angle){ // 0 - 69(gear_ratio)
	// if (ENC->motor_revolution - angle < 0){
	// 	rotate(-100);
	// }else if(ENC->motor_revolution - angle > 0){
	// 	rotate(100);
	// }else{
	// 	rotate(0);
	// }
	uint16_t x = ENC->motor_revolution;
	uint16_t y = goal_angle;

}

void MOTOR::speed_rotate(int16_t goal_speed){ //-50から50 → 100 - 200
	// if(goal_speed<0){goal_speed = goal_speed - 80;}
	// else if(goal_speed > 0){goal_speed = goal_speed + 80;}
	
	if(goal_speed>=MAX_SPEED){
		goal_speed = MAX_SPEED;
	}else if(goal_speed <= -1*MAX_SPEED){
		goal_speed = -1* MAX_SPEED;
	}

	if(goal_speed<0){
		goal_speed = map(goal_speed,-MAX_SPEED,-1,-MAX_SPEED,-90);
	}else if(goal_speed > 0){
		goal_speed = map(goal_speed,1,MAX_SPEED,90,MAX_SPEED);
	}

	if(goal_speed>=MAX_SPEED){
		goal_speed = MAX_SPEED;
	}else if(goal_speed <= -1*MAX_SPEED){
		goal_speed = -1* MAX_SPEED;
	}

	rotate(goal_speed);
}

void MOTOR::calc_speed(){
	now_motor_rev = (ENC->gear_revolution*70 + ENC->motor_revolution)*4095 + ENC->RawAngle;
	now_time = micros();

	float lpf = 0.6;
	diff_motor_rev = (now_motor_rev - pre_motor_rev)*lpf + diff_motor_rev*(1.0-lpf);
	diff_time = pre_time - now_time;

	float ensyu = 7823.0; // 1あたりのmm  102.0*3.1419/4096
	lpf = 0.4;
	speed = ((diff_motor_rev * ensyu) / (0.1 * diff_time))*lpf + pre_speed*(1.0-lpf);

	pre_motor_rev = now_motor_rev;
	pre_time = now_time;
	pre_speed = speed;
}

uint16_t MOTOR::test(){
	// rotate(100);
	// delay(1000);
	// rotate(-100);
	// delay(1000);
	// rotate(0);
	printf("%08d %08d %08d %02d %02d %04d\n", speed, now_motor_rev, diff_time, ENC->gear_revolution, ENC->motor_revolution, ENC->RawAngle);
	// printf("%d\n", speed);
	return 0;
}

void MOTOR::rotate(int16_t duty){ //-255 - 255

	// 前回と今回で急に正負が反転したときは0にする。
	if(pre_duty*duty < 0){
		duty = 0;
	}
	if(duty>pre_duty +1){
		duty = pre_duty + 1;
		// Serial.print("aaaaaaaaaaaaa");
	}else if(duty<pre_duty-1){
		// Serial.print("aaaaaaaaaaaaa");
		duty = pre_duty - 1;
	}
	Serial.print("duty ");
	Serial.println(duty);
	// Serial.print("pre_duty ");
	// Serial.println(pre_duty);

	pre_duty = duty;
	if(duty > 0){
		analogWrite(A_PIN,(duty>MAX_SPEED)?MAX_SPEED:duty);
		analogWrite(B_PIN,0);
	}else if(duty < 0){
		analogWrite(A_PIN,0);
		duty = abs(duty);
		analogWrite(B_PIN,(duty>MAX_SPEED)?MAX_SPEED:duty);
	}else if(duty == 0){
		analogWrite(A_PIN,0);
		analogWrite(B_PIN,0);
	}
}