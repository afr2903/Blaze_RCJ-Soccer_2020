#ifndef OmniDrive_h
#define OmniDrive_h

#include "Arduino.h"

struct motor{
    int rightPin;
    int leftPin;
    int pwmPin=0;
    int angle=0;
    double sp=0;
    motor(int rP, int lP, int pP=0);
    void moveMotor(int speed);
    double omniSpeed(int target, int speed);
};

class OmniDrive{
  public:
    OmniDrive(int _nMot, motor **_mot);
    void test(int speed);
    void setPID(double _kp, double _ki, double _kd);
    double getPID(double error);
    void align(double error);
    void move(int target, int speed, double error);
  private:
    int nMot;
    double kp, ki, kd, integral, derivative, lastError;
    motor **mot;
};

#endif
