#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);
sensors_event_t event;
double error;
adafruit_bno055_offsets_t calibData;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  Serial.println("Calibrating...");
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  while (mag != 3) {
    bno.getCalibration(&sys, &gyro, &accel, &mag);
  }
  Serial.println(mag, DEC);
  delay(1000);

  bno.setExtCrystalUse(true);
}

void loop(void){

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Serial.print("Euler: ");
  Serial.print(euler.x());

  error= bno.getError();
  Serial.print(" Quaternion: ");
  Serial.print(error);

  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);
  Serial.print(" ");
  Serial.println(sys, DEC);

  /*uint8_t sys, gyro, accel, mag;
    sys = gyro = accel = mag = 0;
    bno.getCalibration(&sys, &gyro, &accel, &mag);

    if (!sys) {
    Serial.print("! ");
    }

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
    Serial.println(calibData.mag_radius);*/

  //-28 5 -62 164 93 -56 1 -1 0 1000 696
  //1 4 8 -46 97 123 -42 1 -2 -1 1000 652
}
