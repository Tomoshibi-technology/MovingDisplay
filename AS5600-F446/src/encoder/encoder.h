#ifndef _H_ENCODER_
#define _H_ENCODER_

#include <Arduino.h>
#include <Wire.h>

class ENCODER{
		private:
			TwoWire* I2C;
			uint32_t I2C_CLOCK;
			
			uint8_t GEAR_RATIO = 70; //ギア比
			uint8_t AS5600_AS5601_DEV_ADDRESS = 0x36;
			uint8_t AS5600_AS5601_REG_RAW_ANGLE = 0x0C;

			uint16_t pre_RawAngle = 0; //前回の角度(0-4095)

		public:
			ENCODER(TwoWire* pt_i2c, uint32_t i2c_clock);
			void init();
			void read_angle();
			void calc_revolution();
			uint16_t test();


			uint16_t RawAngle = 0; //現在の角度(0-4095)
			int16_t motor_revolution = 0; //モーターの回転数(0 - GEARE_RATIO-1)
			int16_t gear_revolution = 0; //出力の回転数
};

#endif
