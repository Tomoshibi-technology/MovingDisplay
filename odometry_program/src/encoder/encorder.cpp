#include "./encoder.h"

ENCODER::ENCODER(TwoWire* pt_i2c, u_int32_t i2c_clock){
	I2C = pt_i2c;
	I2C_CLOCK = i2c_clock;
}

void ENCODER::init(){
	I2C -> begin();
	I2C -> setClock(I2C_CLOCK);
}

void ENCODER::read_angle(){
		// Read RAW_ANGLE value from encoder
		I2C -> beginTransmission(AS5600_AS5601_DEV_ADDRESS);
		I2C -> write(AS5600_AS5601_REG_RAW_ANGLE);
		I2C -> endTransmission(false);
		I2C -> requestFrom(AS5600_AS5601_DEV_ADDRESS, 2);
		uint16_t a = 0;
		a  = ((uint16_t)Wire.read() << 8) & 0x0F00;
		a |= (uint16_t)Wire.read();
		// Raw angle value (0 ~ 4095) is stored in RawAngle
		RawAngle = a;
}

void ENCODER::calc_revolution(){
	if(3070<pre_RawAngle && RawAngle<1024){
		motor_revolution++;
	}else if(pre_RawAngle<1024 && 3070<RawAngle){
		motor_revolution--;
	}

	if(motor_revolution == GEAR_RATIO){
		motor_revolution -= GEAR_RATIO;
		gear_revolution++;
		// printf("%02d %02d %04d\n",gear_revolution, motor_revolution,RawAngle);
	}else if(motor_revolution == -1){
		motor_revolution = GEAR_RATIO-1;
		gear_revolution--;
		// printf("%02d %02d %04d\n",gear_revolution, motor_revolution,RawAngle);
	}
	pre_RawAngle = RawAngle;
}

uint16_t ENCODER::test(){
	printf("%02d %02d %04d\n",gear_revolution, motor_revolution,RawAngle);
	return gear_revolution;
}