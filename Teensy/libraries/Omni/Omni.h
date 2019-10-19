#ifndef Omni_h
#define Omni_h

#include "Arduino.h"

class Omni
{
  public:
    Omni(int _pw[], int _dr[], int _di[], float _kp);
    void motor(int n, int sp, bool dir);
    void test();
    void align(float error);
    void move(int deg, int sp, float error);
  private:
    int pw[5], dr[5], di[5];
    int ang[5]={0,45,135,225,315};
    bool aux;
    float kp;
};

#endif
