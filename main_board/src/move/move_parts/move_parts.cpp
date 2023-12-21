#include "./move_parts.h"
MOVE_PARTS::MOVE_PARTS(int sub_ID, int motor_degree, Adafruit_BNO055* pt_b){
  SUB_ID = sub_ID;
  MOTER_DEGREE = motor_degree;
  // TR = pt_tr;
  B = pt_b;
}

void MOVE_PARTS::init(){
    port2.begin(115200);
}

void MOVE_PARTS::calculate(int time_length, int goal_x_coord, int x_coord, int y_coord){
  imu::Vector<3> euler = B->getVector(Adafruit_BNO055::VECTOR_EULER);
  int gyro_degree = euler.x();
  Serial.print("bno ");
  Serial.println(gyro_degree);
  float roll = 0;

  if (gyro_degree > 180){gyro_degree -= 360;}else{}

//   Serial.print("rotate ");
//   Serial.println(gyro_degree);

  if (gyro_degree > 0){
    roll = -30 + (-gyro_degree * 1.3);
    if (gyro_degree < 3){
      roll = 0;
    }
    if (roll < -150){
      roll = -150;
    }
  }else if (gyro_degree < 0){
    roll = 30 + (-gyro_degree * 1.3);
    if (gyro_degree > -3){
      roll = 0;
    }
    if (roll > 150){
      roll = 150;
    }
  }else{
    roll = 0;
  }
//   robot_speed = 
  int robot_speed = sqrt((goal_x_coord - x_coord)*(goal_x_coord - x_coord) + y_coord*y_coord) / time_length;
  int direction = atan2(goal_x_coord-x_coord,y_coord)/PI*180;
//   Serial.print("tl ");Serial.println(time_length);
//   Serial.print("rbs ");Serial.println(robot_speed);
//   Serial.print("dir ");Serial.println(direction);
  motor_speed = int(robot_speed*sin((PI/180)*(direction - MOTER_DEGREE)));
  motor_speed = int((motor_speed * motor_rate) + (roll * (1 - motor_rate)));
  // motor_speed=0;
}

void MOVE_PARTS::transmit(){
  transmit_motor.start(SUB_ID,1);
  utility.num_2_array(send_array,sizeof(send_array),&motor_speed);
  transmit_motor.send(send_array,sizeof(send_array));
  // Serial.print("motor_speed ");Serial.println(motor_speed);
  // Serial.print("calc ");
  // for(int i = 0;i<10;i++){
  //   Serial.print(send_array[i]);
  //   Serial.print(" ");
  // }
  // Serial.println("");

}
