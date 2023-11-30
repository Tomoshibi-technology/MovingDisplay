	#include <stdint.h>
	#include <Wire.h>
	#define AS5600_AS5601_DEV_ADDRESS      0x36
	#define AS5600_AS5601_REG_RAW_ANGLE    0x0C

	int now_amgle();

	void setup() {
		Serial.begin(115200);

		// I2C init
		Wire.begin();
		Wire.setClock(1000000);
	}

	uint8_t GEAR_RATIO = 70; //ギア比
	uint16_t pre_RawAngle = 0;
	int16_t motor_revolution = 0; //回転数(0 - GEARE_RATIO-1)
	int16_t gear_revolution = 0; //回転数

	void loop() {
		uint16_t RawAngle = now_amgle();
		if(3070<pre_RawAngle && RawAngle<1024){
			motor_revolution++;
		}else if(pre_RawAngle<1024 && 3070<RawAngle){
			motor_revolution--;
		}

		if(motor_revolution == GEAR_RATIO){
			motor_revolution -= GEAR_RATIO;
			gear_revolution++;
			printf("%02d %02d %04d\n",gear_revolution, motor_revolution,RawAngle);
		}else if(motor_revolution == -1){
			motor_revolution = GEAR_RATIO-1;
			gear_revolution--;
			printf("%02d %02d %04d\n",gear_revolution, motor_revolution,RawAngle);
		}
		

		pre_RawAngle = RawAngle;

	}

	int now_amgle(){
		// Read RAW_ANGLE value from encoder
		Wire.beginTransmission(AS5600_AS5601_DEV_ADDRESS);
		Wire.write(AS5600_AS5601_REG_RAW_ANGLE);
		Wire.endTransmission(false);
		Wire.requestFrom(AS5600_AS5601_DEV_ADDRESS, 2);
		uint16_t a = 0;
		a  = ((uint16_t)Wire.read() << 8) & 0x0F00;
		a |= (uint16_t)Wire.read();
		// Raw angle value (0 ~ 4095) is stored in RawAngle
		return a;
	}