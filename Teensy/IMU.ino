#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
sensors_event_t event;
double siny_cosp, cosy_cosp;
double deg;
adafruit_bno055_offsets_t calibData;

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  //write8(55, 0x20);
  /* Initialise the sensor */  
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  Serial.println("Calibrating...");
  delay(10000);
    
  bno.setExtCrystalUse(true);
}
 
void loop(void) 
{

  /*imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Serial.print("Euler: ");
  Serial.print(euler.x());

  imu::Quaternion q= bno.getQuat();
  siny_cosp= 2*(q.w()*q.z() + q.x()*q.y());
  cosy_cosp= 1- 2*(q.y()*q.y() + q.z()*q.z());
  deg = -atan2(siny_cosp, cosy_cosp)*180/PI;
  
  Serial.print(" Quaternion: ");
  Serial.println(deg);*/

  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);
 
  /* The data should be ignored until the system calibration is > 0 */
  if (!sys){
    Serial.print("! ");
  }
 
  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(sys, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.print(mag, DEC);
  Serial.print(" ");

  bno.getSensorOffsets(calibData);
  Serial.print(bno.isFullyCalibrated());
  Serial.print(" ");
  Serial.print(calibData.accel_offset_x);
  Serial.print(" ");
  Serial.print(calibData.accel_offset_y);
  Serial.print(" ");
  Serial.print(calibData.accel_offset_z);
  Serial.print(" ");
  Serial.print(calibData.mag_offset_x);
  Serial.print(" ");
  Serial.print(calibData.mag_offset_y);
  Serial.print(" ");
  Serial.print(calibData.mag_offset_z);
  Serial.print(" ");
  Serial.print(calibData.gyro_offset_x);
  Serial.print(" ");
  Serial.print(calibData.gyro_offset_y);
  Serial.print(" ");
  Serial.print(calibData.gyro_offset_z);
  Serial.print(" ");
  Serial.print(calibData.accel_radius);
  Serial.print(" ");
  Serial.println(calibData.mag_radius);

  //-28 5 -62 164 93 -56 1 -1 0 1000 696
  //1 4 8 -46 97 123 -42 1 -2 -1 1000 652
}
