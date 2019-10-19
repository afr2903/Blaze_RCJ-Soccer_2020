#include <Omni.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
sensors_event_t event; 

int pw[]={0,22,14,4,5};
int dr[]={0,20,15,3,7};
int di[]={0,21,16,2,6};
int dir;
float deg;

Omni cbaq(pw,dr,di,1.0,0.5);

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
  if(!bno.begin()){
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(500);
    
  bno.setExtCrystalUse(true);
  
}

void loop(){
  
  if (Serial1.available() > 0) {
    dir = Serial1.read()-51;
    dir+= dir>5? +5: dir<5? -5:0;
    Serial.println(dir);
    //delay(500);
  }
  //else cbaq.move(dir, 0, deg);
  
  bno.getEvent(&event);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  deg= euler.x();
  if(deg>180) deg-=360;
  //Serial.println(deg);
  
  cbaq.move(dir, 150, deg);
  //cbaq.align(deg);
  //cbaq.motor('D', 60, 1);
  //cbaq.test();
  //delay(50);
}
