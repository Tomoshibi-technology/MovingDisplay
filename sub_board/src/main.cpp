#include <Arduino.h>

// put function declarations here:
HardwareSerial serial_m = HardwareSerial(PA10,PA9);
int id = 0;

int readID();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  serial_m.begin(115200);
  pinMode(PA0,OUTPUT);
  pinMode(PA1,OUTPUT);

  pinMode(PA7,INPUT);
  pinMode(PB0,INPUT);
  pinMode(PB1,INPUT);
  pinMode(PB5,INPUT);

  digitalWrite(PA1,1);
}

int light = 0;

void loop() {
  int ID = readID();
  int i = 0;
  byte data[] = {0,0,0,0,0,0,0,0,0,0};

  while(serial_m.available()>0){
    data[i] = serial_m.read();
    if(data[i]==ID*10+2){
      serial_m.write(250);
      serial_m.write(ID*10+2);
      serial_m.write(ID*10+6);
      serial_m.write(ID*10+7);
      serial_m.write(ID*10+8);
      int checksum = 255 - ((ID*10+6)+(ID*10+7)+(ID*10+8) % 256);
      serial_m.write(checksum);
    }
    i++;
  }

  for(int n = 0; n < i; n++){
    if(data[n]==ID*10+1){
      light=data[n+1]-99;
      if(light>1){
        light = 1;
      }
      Serial.println(data[n+1]);
      digitalWrite(PA0,light);
    }
  }

  // Serial.print("/");
  // Serial.println(ID);
}

int readID(){
  if(digitalRead(PA7)==1){
    return 1;
  }
  else if(digitalRead(PB0)==1){
    return 2;
  }
  else if(digitalRead(PB1)==1){
    return 3;
  }
  else if(digitalRead(PB5)==1){
    return 4;
  }else{
    return 99;
  }
}