#ifndef Drive_h
#define Drive_h

#include "Arduino.h"

struct motor{
    int rightPin;
    int leftPin;
    int pwmPin=0;
    int angle=0;
    double sp=0;
    double current_speed = 0;
    double target_speed = 0;
    double ramp_rate = 0.000001;
    bool ramp_active = false;
    motor(int rP, int lP, int pP=0);
    void moveMotor(double speed);
    double ramp(double speed);
    double omniSpeed(int target, double speed);
};

class Drive{
  public:
    Drive(int _nMot, motor **_mot);
    void test(double speed);
    void setPID(double _kp, double _ki, double _kd);
    double getPID(double error);
    void align(double error);
    void move(int target, double speed, double error);
  private:
    int nMot;
    double kp, ki, kd, integral, derivative, lastError;
    motor **mot;
};

#endif
