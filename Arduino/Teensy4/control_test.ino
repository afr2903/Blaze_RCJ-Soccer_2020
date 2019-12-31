#include <Omni.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

motor m1(21,22,3);
motor m2(5,4,6);
motor m3(7,8,9);
motor m4(11,10,12);
motor *motors[]= {&m1,&m2,&m3,&m4};
Omni cbaq(4, motors);

double kp=3.3, ki=0, kd=80;
double target, error, strength;

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
  if(!bno.begin()){
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  Serial.println("Calibrating...");
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  while (mag != 3)
    bno.getCalibration(&sys, &gyro, &accel, &mag);
  Serial.println(mag, DEC);
  delay(500);
  bno.setExtCrystalUse(true);

  cbaq.setPID(kp,ki,kd);
}

void loop(){
  
  error= bno.getError();
  Serial.println(error);
  
  cbaq.move(0-error, 200, error);
  //cbaq.align(error);
}
