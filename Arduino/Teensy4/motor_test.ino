#include <Omni.h>

motor m1(21,22,3);
motor m2(5,4,6);
motor m3(7,8,9);
motor m4(11,10,12);
motor *motors[]= {&m1,&m2,&m3,&m4};
double kp=3.3, ki=0, kd=80;
Omni cbaq(4, motors);

void setup() {
  cbaq.setPID(kp,ki,kd);
}

void loop(){
  //cbaq.move(90, 100, 0);
  //cbaq.motor('D', 60, 1);
  cbaq.test(100);
}
