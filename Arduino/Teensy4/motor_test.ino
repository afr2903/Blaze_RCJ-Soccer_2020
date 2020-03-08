#include <Drive.h>

motor m1(2,4,3);
motor m2(23,21,22);
motor m3(10,8,9);
motor m4(7,5,6);
motor *motors[]= {&m1,&m2,&m3,&m4};
double kp=3.3, ki=0, kd=80;
Drive ness(4, motors);

void setup() {
  Serial.begin(19200);
  ness.setPID(kp,ki,kd);
}

void loop(){
  ness.test(0.5);
  //m2.moveMotor(1.0);
  //Serial.println(digitalRead(12));
  //delay(100);
}
