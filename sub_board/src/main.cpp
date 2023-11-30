#include <Arduino.h>

// put function declarations here:
HardwareSerial serial_m = HardwareSerial(PA10,PA9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  serial_m.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(serial_m.available()>0){
    Serial.println(serial_m.read());
  }
}

