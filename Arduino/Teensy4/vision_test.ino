#include <Drive.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

motor m1(2,4,3);
motor m2(23,21,22);
motor m3(10,8,9);
motor m4(7,5,6);
motor *motors[]= {&m1,&m2,&m3,&m4};
Drive ness(4, motors);

double kp=3.3, ki=0, kd=80;
double target, error, strength;

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
  if(!bno.begin()){
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  /*Serial.println("Calibrating...");
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  while (mag != 3) {
    bno.getCalibration(&sys, &gyro, &accel, &mag);
  }
  Serial.println(mag, DEC);
  delay(500);*/
  bno.setExtCrystalUse(true);

  ness.setPID(kp,ki,kd);
}

void loop(){
  
  if (Serial1.available() > 0) {
    target = Serial1.read()-120;
    strength= Serial1.read()*1.5;
  }

  //strength = strength/255;
  /*Serial.print(target);
  Serial.print(" ");
  Serial.print(strength);
  Serial.print(" ");*/
  
  error= bno.getError();
  //Serial.println(error);
  
  ness.move(target-error, 100+strength, error);
}
